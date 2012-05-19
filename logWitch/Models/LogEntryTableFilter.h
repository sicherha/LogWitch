/*
 * LogEntryTableFilter.h
 *
 *  Created on: May 18, 2011
 *      Author: sven
 */

#ifndef LOGENTRYTABLEFILTER_H_
#define LOGENTRYTABLEFILTER_H_

#include <QSortFilterProxyModel>
#include "LogEntryFilterChain.h"
#include "ActionRules/RuleTable.h"

class LogEntryTableModel;

class LogEntryTableFilter
	: public QSortFilterProxyModel
{
	Q_OBJECT
public:
	LogEntryTableFilter( QObject *parent );

	void setSourceModel( QAbstractItemModel *model );

	LogEntryTableModel *getSourceModel() const;

	QVariant data(const QModelIndex &index, int role) const;

	void addFilter( boost::shared_ptr<LogEntryFilter> );

	TSharedRuleTable getRuleTable();

	virtual ~LogEntryTableFilter();

public slots:
	void updateChanges();

	void slotRowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end );

	void slotInvalidateIfNeeded();

	void slotModelAboutToBeReset();

public:
	/**
	 * This enables the show surrounding entries around index and woith +/-
	 * valuesToShow.
	 */
	void showSurroundingLogEntries( const QModelIndex &index, uint valuesToShow );

	/**
	 * Disables surrounding entries.
	 */
	void hideSurroundingLogEntries();


protected:
	bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;

	/**
	 * This method implements filtering only, it returns the filtering from the
	 * filterCahin and the ruleTable. It does not handle surrounding.
	 */
	bool filterAcceptInt ( TconstSharedLogEntry entry ) const;

private:
	LogEntryTableModel *m_model;

	LogEntryFilterChain m_filterChain;

	TSharedRuleTable m_ruleTable;

	typedef std::vector<TconstSharedExpression> TExpressionVector;

	TExpressionVector m_discardExpressions;

	int m_surroundingRowStart;

    int m_surroundingRowEnd;

    bool m_resetFilterNeeded;
};

#endif /* LOGENTRYTABLEFILTER_H_ */
