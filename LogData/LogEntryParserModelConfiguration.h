/*
 * LogEntryParserModelConfiguration.h
 *
 *  Created on: May 18, 2011
 *      Author: sven
 */

#ifndef LOGENTRYPARSERMODELCONFIGURATION_H_
#define LOGENTRYPARSERMODELCONFIGURATION_H_
#include <QtCore/QtCore>
#include <boost/shared_ptr.hpp>


class EntryToTextFormater;
class LogEntryAttributeFactory;
/**
 * This class is responsible for modeling different kinds of behavior for the
 * GUI which is defined by the logfile and its structure.
 */
class LogEntryParserModelConfiguration
{
public:
	LogEntryParserModelConfiguration();
	virtual ~LogEntryParserModelConfiguration();

	/**
	 * Returns if an entry field is a hierarchy and returns the string for a regex to split it.
	 */
	QString getHierarchySplitString( int idx ) const
	{
		if( idx >= 0 && idx < m_hierarchySplitstrings.size() )
			return m_hierarchySplitstrings[idx];
		else
			return "";
	}

	void setHierarchySplitString( int idx, const QString & fmt)
	{
		if( idx >= m_hierarchySplitstrings.size() )
			m_hierarchySplitstrings.resize(idx+1);

		m_hierarchySplitstrings[idx] = fmt;
	}

	/**
	 * Returns an entry to text formater for this types of entries.
	 */
	boost::shared_ptr<EntryToTextFormater> getEntryToTextFormater() const { return m_formater;};

	void setEntryToTextFormater( boost::shared_ptr<EntryToTextFormater> fmt ){ m_formater = fmt;}

	/**
	 * Returns the corresponding factory for creating log entries.
	 */
	boost::shared_ptr<const LogEntryAttributeFactory> getLogEntryAttributeFactory() const { return m_attr;}

	void setLogEntryAttributeFactory( boost::shared_ptr<LogEntryAttributeFactory> factory) { m_attr = factory;}

	int getFieldWidthHint( int idx ) const
	{
		if( idx < (int)m_filedWidthHints.size() )
			return m_filedWidthHints[idx] < 0 ? 150 : m_filedWidthHints[idx];
		else
			return 150;
	}

	void setFieldWidthHint( int idx, int width )
	{
		while( idx >= (int)m_filedWidthHints.size() )
			m_filedWidthHints.push_back(-1);

		m_filedWidthHints[idx] = width;
	}

private:
	QVector<QString> m_hierarchySplitstrings;

	boost::shared_ptr<EntryToTextFormater> m_formater;

	boost::shared_ptr<LogEntryAttributeFactory> m_attr;

	std::vector<int> m_filedWidthHints;
};

#endif /* LOGENTRYPARSERMODELCONFIGURATION_H_ */