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
    setWindowTitle(tr("Find", "FindDialog"));
    // Note: Don't connect findNext/findPrev/replace/replaceAll here.  We inherit from FindReplaceDialog which does them.
}

FindDialog::~FindDialog()
{
}

void FindDialog::writeSettings(QSettings &settings, const QString &prefix) {
    FindReplaceDialog::writeSettings(settings, prefix);
}

void FindDialog::readSettings(QSettings &settings, const QString &prefix) {
    FindReplaceDialog::readSettings(settings, prefix);
}
