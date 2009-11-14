/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

#include "findreplacedialog.h"

/**
  * A find dialog
  */
class FindDialog : public FindReplaceDialog {
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();
};

#endif // FINDDIALOG_H
