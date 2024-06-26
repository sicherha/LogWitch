/*
 * FieldDescriptor.h
 *
 *  Created on: Jun 5, 2011
 *      Author: sven
 */

#ifndef VALUEGETTERLOGENTRY_H_
#define VALUEGETTERLOGENTRY_H_

#include <QString>

#include "LogData/LogEntry.h"
#include "Types.h"
#include "ValueGetter.h"
#include "LogData/LogEntryParserModelConfiguration.h"


class ValueGetterLogEntry
    : public ValueGetter
{
public:
    ValueGetterLogEntry() = default;
    ValueGetterLogEntry( QString name, TSharedConstLogEntryParserModelConfiguration configuration  );
    ValueGetterLogEntry( TSharedConstLogEntryParserModelConfiguration configuration  );

    void setName( const QString &name );
    QString getName() const;

    bool isValid() const override;

    int getID( ) const;

    TSharedConstQString getValue(TconstSharedLogEntry &entry) const override;

    std::ostream &out(std::ostream &o, bool extended = false) const override;

private:
    QString m_name;

    TSharedConstLogEntryParserModelConfiguration m_configuration;

    int m_fieldId = -1;
};

typedef std::shared_ptr<ValueGetterLogEntry> TSharedValueGetterLogEntry;
typedef std::shared_ptr<const ValueGetterLogEntry> TconstSharedValueGetterLogEntry;

#endif /* VALUEGETTERLOGENTRY_H_ */
