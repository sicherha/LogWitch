/*
 * FilterRuleSelectionWindow.cpp
 *
 *  Created on: Jun 10, 2011
 *      Author: sven
 */

#include "FilterRuleSelectionWindow.h"

#include <QtGui>
#include <boost/bind.hpp>

#include "ActionRules/CompiledRulesStateSaver.h"
#include "ActionRules/TableModelRulesCompiled.h"
#include "ActionRules/ToolButtonTrashFilter.h"

#include "GUITools/EventFilterToBoostFunction.h"

#include "Models/LogEntryTableFilter.h"


FilterRuleSelectionWindow::FilterRuleSelectionWindow( QWidget* parent )
: QSplitter( Qt::Vertical, parent )
, m_compiledRules( )
{
    m_ruleView = new RulesTableView( );
    m_ruleView->verticalHeader()->setDefaultSectionSize( 20 );
    m_ruleView->horizontalHeader()->setDefaultSectionSize( 190 );
    m_ruleView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    m_rulesModel = new TableModelRulesCompiled( m_ruleView );
    m_ruleView->setModel( m_rulesModel );
    m_ruleView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ruleView->setSelectionMode( QAbstractItemView::ExtendedSelection );

    m_ruleView->setDragEnabled( true );
    m_ruleView->setDropIndicatorShown(true);
    m_ruleView->setDragDropMode( QAbstractItemView::DragDrop );

    // Filter "Key_Delete" Key and pass it to trashSelectedRules.
    m_ruleView->installEventFilter( new EventFilterToBoostFunction( this,
            boost::bind( &evtFunc::keyPressed, _1, _2, Qt::Key_Delete,
                    boost::function< void(void ) >( boost::bind( &FilterRuleSelectionWindow::trashSelectedRules, this ) ) ) ) );

    QWidget *displayWidget = new QWidget(); //This is the pane
    QVBoxLayout* vbox = new QVBoxLayout(displayWidget);
    displayWidget->setLayout(vbox);

    QToolBar* toolBar = new QToolBar( displayWidget );

    // Add trash selected rule action
    m_trashSelectedRules = new QAction("Trash", this);
    m_trashSelectedRules->setIcon(QIcon(":/icons/trash"));
    toolBar->addWidget( new ToolButtonTrashFilter( m_trashSelectedRules, m_rulesModel ) );
    QObject::connect(m_trashSelectedRules, SIGNAL(triggered()),
            this, SLOT(trashSelectedRules()));

    // Finish toolbar
    toolBar->setIconSize(QSize(16,16));
    vbox->addWidget(toolBar);
    vbox->addWidget(m_ruleView);

    addWidget( displayWidget );
    addWidget( new QLabel ( tr("Context missing - open or select a Logger window to add rules."), this ) );
    //addWidget( generateNewParserWindow() );
    QList<int> he; he << 300 << 500;
    setSizes ( he );
    setStretchFactor ( 0, 10 );
    setStretchFactor ( 1, 10 );

    loadRules();
}

void FilterRuleSelectionWindow::loadRules()
{
    QSettings settings;

    const int size = settings.beginReadArray("Rules");
    for (int i = 0; i < size; ++i)
    {
         settings.setArrayIndex(i);
         m_rulesModel->appendRule( settings.value("rule").toString() );
    }

    settings.endArray();
}

void FilterRuleSelectionWindow::storeRules() const
{
    QSettings settings;
    settings.beginWriteArray("Rules");
    unsigned int arrRow = 0;
    for (unsigned int i = 0; i < m_rulesModel->rowCount(); ++i)
    {
        QString rule = m_rulesModel->getRule(i);
        // We will ignore empty rules, such a rule is for eg. the new insertion rule.
        if( rule.length() )
        {
            settings.setArrayIndex( arrRow++ );
            settings.setValue("rule", rule );
        }
    }
    settings.endArray();
}

void FilterRuleSelectionWindow::setWindow( TSharedCompiledRulesStateSaver state )
{
    if( !state )
    {
        m_compiledRules.reset();

        for( int i = 2; i < count(); i++ )
            widget( i )->hide();
        widget( 1 )->show();
    }
    else
    {
        state->connectActions( this );
        m_compiledRules = state;

        for( int i = 1; i < count(); i++ )
        {
            if( widget(i) != state->m_displayWidget)
                widget( i )->hide();
            else
                widget( i )->show();
        }

        addWidget( state->m_displayWidget );
    }
}

TSharedCompiledRulesStateSaver FilterRuleSelectionWindow::getWindow( )
{
    return m_compiledRules;
}

void FilterRuleSelectionWindow::trashSelectedRules()
{
    qDebug() <<"FilterRuleSelectionWindow::trashSelectedRules()";
    QItemSelectionModel *selMod = m_ruleView->selectionModel();
    QModelIndexList selection = selMod->selectedRows();
    m_rulesModel->removeRules( selection );
}

void FilterRuleSelectionWindow::removeSelectionFromCompiled( )
{
    if( m_compiledRules )
    {
        QItemSelectionModel *selMod = m_compiledRules->m_compiledRuleView->selectionModel();
        QModelIndexList selection = selMod->selectedRows();
        m_compiledRules->m_rulesCompiledModel->removeRules( selection );
    }
}

FilterRuleSelectionWindow::~FilterRuleSelectionWindow()
{
    storeRules();
}