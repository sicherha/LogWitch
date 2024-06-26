/*
 * LogEntryTableFilter.h
 *
 *  Created on: May 18, 2011
 *      Author: sven
 */

#ifndef LOGENTRYTABLEFILTER_H_
#define LOGENTRYTABLEFILTER_H_

#include <QSortFilterProxyModel>

#include "ExportableIfc.h"
#include "LogEntryFilterChain.h"

#include "ActionRules/RuleTable.h"

class LogEntryTableModel;

class LogEntryTableFilter
	: public QSortFilterProxyModel
	, public ExportableIfc
{
	Q_OBJECT
public:
	LogEntryTableFilter( QObject *parent );

	void setSourceModel(QAbstractItemModel *model) override;

	LogEntryTableModel *getSourceModel() const;

	QVariant data(const QModelIndex &index, int role) const override;

	void addFilter( std::shared_ptr<LogEntryFilter> );

	TSharedRuleTable getRuleTable();

	void generateExportList( std::vector<TconstSharedLogEntry>& ls
	    , QModelIndex first, QModelIndex last
	    , const ExportParameters& param) const override;

public slots:
	void updateChanges();

	void slotRowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end );

	void slotInvalidateIfNeeded();

	void slotModelAboutToBeReset();

public:
	/**
	 * This enables the show surrounding entries around index and with +/-
	 * valuesToShow.
	 */
	void showSurroundingLogEntries( const QModelIndex &index, uint valuesToShow );

	/**
	 * Disables surrounding entries.
	 */
	void hideSurroundingLogEntries();


protected:
	bool filterAcceptsRow (int source_row, const QModelIndex & source_parent) const override;

	/**
	 * This method implements filtering only, it returns the filtering from the
	 * filterCahin and the ruleTable. It does not handle surrounding.
	 */
	bool filterAcceptInt ( TconstSharedLogEntry entry ) const;

private:
	LogEntryTableModel *m_model = nullptr;

	LogEntryFilterChain m_filterChain;

	TSharedRuleTable m_ruleTable;

	typedef std::vector<TconstSharedExpression> TExpressionVector;

	TExpressionVector m_discardExpressions;

	int m_surroundingRowStart = -1;

  int m_surroundingRowEnd = -1;

  bool m_resetFilterNeeded = false;

  ExportableIfc *m_exportOfSourceModel = nullptr;
};

#endif /* LOGENTRYTABLEFILTER_H_ */
