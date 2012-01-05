/*
 * RuleTable.cpp
 *
 *  Created on: Jun 5, 2011
 *      Author: sven
 */

#include "RuleTable.h"

RuleTable::RuleTable()
:m_onChange ( false )
{
}

RuleTable::~RuleTable()
{
}

void RuleTable::addRule( const char *tableName, TSharedRule &rule )
{
    qDebug() << "RuleTable::addRule";

    std::string tableNameAsString( tableName );
    TRuleTableMap::iterator it = m_rulesFromSource.find( tableNameAsString );
    if( it == m_rulesFromSource.end() )
    {
        it = m_rulesFromSource.insert( TRuleTableMap::value_type(tableNameAsString,TRuleSet()) ).first;
    }

    it->second.insert( rule );
    m_rules.insert( rule );

    dataChanged();
}

void RuleTable::clear( const char *tableName )
{
    std::string tableNameAsString( tableName );
    TRuleTableMap::iterator it = m_rulesFromSource.find( tableNameAsString );
    if( it == m_rulesFromSource.end() )
        return;

    m_rulesFromSource.erase( it );

    // rebuild table
    m_rules.clear();
    for( it = m_rulesFromSource.begin(); it != m_rulesFromSource.end(); ++it )
    {
        m_rules.insert( it->second.begin(), it->second.end() );
    }

    dataChanged();
}

void RuleTable::beginChange()
{
    m_onChange = true;
}

void RuleTable::endChange()
{
    m_onChange = false;
    emit changed();
}

void RuleTable::dataChanged()
{
    if( !m_onChange )
        emit changed();
}