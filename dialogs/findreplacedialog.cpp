/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
    ui(new Ui::FindReplaceDialog)
{
    ui->setupUi(this);
    connect(ui->findReplaceForm, SIGNAL(en_findNext()), this, SIGNAL(en_findNext()));
    connect(ui->findReplaceForm, SIGNAL(en_findPrev()), this, SIGNAL(en_findPrev()));
    connect(ui->findReplaceForm, SIGNAL(en_replace()), this, SIGNAL(en_replace()));
    connect(ui->findReplaceForm, SIGNAL(en_replaceAll()), this, SIGNAL(en_replaceAll()));
}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}

void FindReplaceDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FindReplaceDialog::setTextEdit(QTextEdit *textEdit) {
    ui->findReplaceForm->setTextEdit(textEdit);
}

void FindReplaceDialog::enableRegExpControls(bool enable)
{
    ui->findReplaceForm->enableRegExpControls(enable);
}

void FindReplaceDialog::writeSettings(QSettings &settings, const QString &prefix) {
    ui->findReplaceForm->writeSettings(settings, prefix);
}

void FindReplaceDialog::readSettings(QSettings &settings, const QString &prefix) {
    ui->findReplaceForm->readSettings(settings, prefix);
}

QTextDocument::FindFlags FindReplaceDialog::findFlags(bool down) const
{
    return ui->findReplaceForm->findFlags(down);
}

bool FindReplaceDialog::regExpMode() const
{
    return ui->findReplaceForm->regExpMode();
}

QString FindReplaceDialog::textToFind() const
{
    return ui->findReplaceForm->textToFind();
}

void FindReplaceDialog::setTextToFind(const QString &strText)
{
    ui->findReplaceForm->setTextToFind(strText);
}

void FindReplaceDialog::find()
{
    ui->findReplaceForm->find();
}

void FindReplaceDialog::findNext() {
    ui->findReplaceForm->findNext();
}

void FindReplaceDialog::findPrev() {
    ui->findReplaceForm->findPrev();
}
