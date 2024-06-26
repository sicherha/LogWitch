/*
 * ExpressionRegEx.h
 *
 *  Created on: Jun 25, 2011
 *      Author: sven
 */

#ifndef EXPRESSIONREGEX_H_
#define EXPRESSIONREGEX_H_


#include "ActionRules/Expression.h"
#include <iostream>
#include "ValueGetter.h"
#include <QRegularExpression>

class ExpressionRegEx
    : public Expression
{
public:
    ExpressionRegEx( TconstSharedValueGetter value, const QString &exp);

    bool isValid() const override;

    bool match(TconstSharedLogEntry &entry) const override;

    std::ostream &out(std::ostream &o, bool extended = false) const override;

    QString getPattern() const;
    TconstSharedValueGetter getValueGetter() const;
private:
    TconstSharedValueGetter m_value;

    QRegularExpression m_regex;
};

typedef std::shared_ptr<ExpressionRegEx> TSharedExpressionRegEx;
typedef std::shared_ptr<const ExpressionRegEx> TconstSharedExpressionRegEx;


#endif /* EXPRESSIONREGEX_H_ */
