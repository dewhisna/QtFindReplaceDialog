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
    connect(ui->findReplaceForm, SIGNAL(en_findNext()), this, SIGNAL(en_findNext()));
    connect(ui->findReplaceForm, SIGNAL(en_findPrev()), this, SIGNAL(en_findPrev()));
    connect(ui->findReplaceForm, SIGNAL(en_replace()), this, SIGNAL(en_replace()));
    connect(ui->findReplaceForm, SIGNAL(en_replaceAll()), this, SIGNAL(en_replaceAll()));
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
