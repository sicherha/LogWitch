/*
 * LogEntry.h
 *
 *  Created on: May 13, 2011
 *      Author: sven
 */

#ifndef LOGENTRY_H_
#define LOGENTRY_H_

#include <QDateTime>
#include <QString>
#include <QMetaType>

#include <boost/shared_ptr.hpp>

class LogEntryAttributes;

class LogEntry {
public:
	LogEntry(const QDateTime &date, boost::shared_ptr<LogEntryAttributes> attr,  const QString &message );

	const LogEntryAttributes &getAttributes() const;

	LogEntryAttributes &getAttributes();

	const QDateTime &getTimestamp() const;

	const QString &getMessage() const;

	void setMessage(const QString &str) {message = str; };

private:
	QDateTime timestamp;

	boost::shared_ptr<LogEntryAttributes> indexedLogEntries;

	QString message;
};

typedef boost::shared_ptr<LogEntry> TSharedLogEntry;

Q_DECLARE_METATYPE ( TSharedLogEntry );

#endif /* LOGENTRY_H_ */
