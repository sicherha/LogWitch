/*
 * ActionRemoveRow.h
 *
 *  Created on: Jun 5, 2011
 *      Author: sven
 */

#ifndef ACTIONREMOVEROW_H_
#define ACTIONREMOVEROW_H_
#include "ActionRules/Action.h"

class ActionDiscardRow
    : public Action
{
public:
    QVariant toDisplay(int role) const override;
};


typedef std::shared_ptr<ActionDiscardRow> TSharedActionDiscardRow;
typedef std::shared_ptr<const ActionDiscardRow> TconstSharedActionDiscardRow;

#endif /* ACTIONREMOVEROW_H_ */
