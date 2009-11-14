/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>
#include <QTextCursor>

#include "findreplaceform.h"

/**
  * The form for the find dialog (it is basically the same
  * as FindReplaceForm without the replace related widgets)
  */
class FindForm : public FindReplaceForm {
    Q_OBJECT
public:
    FindForm(QWidget *parent = 0);
    ~FindForm();

protected:
    void changeEvent(QEvent *e);

};

#endif // FINDFORM_H
