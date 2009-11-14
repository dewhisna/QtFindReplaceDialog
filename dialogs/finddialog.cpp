/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include "finddialog.h"
#include "ui_findreplacedialog.h"

FindDialog::FindDialog(QWidget *parent) :
    FindReplaceDialog(parent)
{
    ui->findReplaceForm->hideReplaceWidgets();
    setWindowTitle(tr("Find"));
}

FindDialog::~FindDialog()
{
}

