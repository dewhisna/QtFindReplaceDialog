/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include <QtGui>
#include <QTextEdit>
#if QT_VERSION >= 0x050000
#include <QRegularExpression>
#else
#include <QRegExp>
#endif
#include <QSettings>
#include <QShowEvent>

#include "findreplaceform.h"
#include "ui_findreplaceform.h"

#define TEXT_TO_FIND "textToFind"
#define TEXT_TO_REPLACE "textToReplace"
#define DOWN_RADIO "downRadio"
#define UP_RADIO "upRadio"
#define CASE_CHECK "caseCheck"
#define WHOLE_CHECK "wholeCheck"
#define REGEXP_CHECK "regexpCheck"

#define DEBUG_FIND 0    // Set to '1' to enable debugging of 'find'

FindReplaceForm::FindReplaceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceForm), textEdit(0)
{
    ui->setupUi(this);

    ui->errorLabel->setText("");

    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(validateRegExp(QString)));

    connect(ui->regexCheckBox, SIGNAL(toggled(bool)), this, SLOT(regexpSelected(bool)));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find()));
    connect(ui->closeButton, SIGNAL(clicked()), parent, SLOT(close()));

    connect(ui->replaceButton, SIGNAL(clicked()), this, SLOT(replace()));
    connect(ui->replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));
}

FindReplaceForm::~FindReplaceForm()
{
    delete ui;
}

void FindReplaceForm::hideReplaceWidgets() {
    ui->replaceLabel->setVisible(false);
    ui->textToReplace->setVisible(false);
    ui->replaceButton->setVisible(false);
    ui->replaceAllButton->setVisible(false);
}

void FindReplaceForm::enableRegExpControls(bool enable)
{
    if (!enable) ui->regexCheckBox->setChecked(false);
    ui->regexCheckBox->setEnabled(enable);
}

void FindReplaceForm::setTextEdit(QTextEdit *textEdit_) {
    if (textEdit) {
        // Disconnect old control:
        disconnect(textEdit, 0, ui->replaceButton, 0);
        disconnect(textEdit, 0, ui->replaceAllButton, 0);
    }
    textEdit = textEdit_;
    if (!textEdit) return;
    connect(textEdit, SIGNAL(copyAvailable(bool)), ui->replaceButton, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), ui->replaceAllButton, SLOT(setEnabled(bool)));
}

void FindReplaceForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FindReplaceForm::showEvent(QShowEvent *event)
{
    showError(QString());
    showMessage(QString());
    QWidget::showEvent(event);
}

void FindReplaceForm::textToFindChanged() {
    ui->findButton->setEnabled(ui->textToFind->text().size() > 0);
}

void FindReplaceForm::regexpSelected(bool sel) {
    if (sel)
        validateRegExp(ui->textToFind->text());
    else
        validateRegExp("");
}

void FindReplaceForm::validateRegExp(const QString &text) {
    if (!ui->regexCheckBox->isChecked() || text.size() == 0) {
        ui->errorLabel->setText("");
        return; // nothing to validate
    }

#if QT_VERSION >= 0x050000
    QRegularExpression reg(text,
                (ui->caseCheckBox->isChecked() ? QRegularExpression::NoPatternOption : QRegularExpression::CaseInsensitiveOption));
#else
    QRegExp reg(text,
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
#endif

    if (reg.isValid()) {
        showError("");
    } else {
        showError(reg.errorString());
    }
}

void FindReplaceForm::showError(const QString &error) {
    if (error.isEmpty()) {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:#ff0000;\">" +
                                error +
                                "</span>");
    }
}

void FindReplaceForm::showMessage(const QString &message) {
    if (message.isEmpty()) {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:green;\">" +
                                message +
                                "</span>");
    }
}

QTextDocument::FindFlags FindReplaceForm::findFlags(bool down) const
{
    QTextDocument::FindFlags flags = { };

    if (!down)
        flags |= QTextDocument::FindBackward;
    if (ui->caseCheckBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (ui->wholeCheckBox->isChecked())
        flags |= QTextDocument::FindWholeWords;

    return flags;
}

bool FindReplaceForm::regExpMode() const
{
    return ui->regexCheckBox->isChecked();
}

QString FindReplaceForm::textToFind() const
{
    return ui->textToFind->text();
}

void FindReplaceForm::setTextToFind(const QString &strText)
{
    ui->textToFind->setText(strText);
}

void FindReplaceForm::find() {
    find(ui->downRadioButton->isChecked());
}

void FindReplaceForm::find(bool next) {
    if (!textEdit) {
        if (next) {
            emit en_findNext();
        } else {
            emit en_findPrev();
        }
        return;
    }

    // backward search
    bool back = !next;

    const QString &toSearch = ui->textToFind->text();

    bool result = false;

    // Check the cursor for wrap:
    textCursor = textEdit->textCursor();
    if (next && textCursor.atEnd()) {
        textCursor.movePosition(QTextCursor::Start);
    } else if (back && textCursor.atStart()) {
        textCursor.movePosition(QTextCursor::End);
    }
    textEdit->setTextCursor(textCursor);

    QTextDocument::FindFlags flags = findFlags(next);

    if (ui->regexCheckBox->isChecked()) {
#if QT_VERSION >= 0x050500			// Needs to be >=5.5 since QTextDocument::find QRegularExpression is in >=5.5 below
        QRegularExpression reg(toSearch,
                    (ui->caseCheckBox->isChecked() ? QRegularExpression::NoPatternOption : QRegularExpression::CaseInsensitiveOption));
#else
        QRegExp reg(toSearch,
                    (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
#endif

#if (DEBUG_FIND)
        qDebug() << "searching for regexp: " << reg.pattern();
#endif

        textCursor = textEdit->document()->find(reg, textCursor, flags);
        if (!textCursor.isNull()) textEdit->setTextCursor(textCursor);
        result = (!textCursor.isNull());
    } else {
#if (DEBUG_FIND)
        qDebug() << "searching for: " << toSearch;
#endif

        result = textEdit->find(toSearch, flags);
    }

    if (result) {
        showError("");
    } else {
        showError(tr("no match found", "FindDialog"));
        // move to the end of the document (if searching down)
        //	or the beginning of the document (if searching up)
        //	for the next find.  The next find will wrap the
        //	cursor and this logic will work if the user switches
        //	the direction of the search:
        textCursor = textEdit->textCursor();
        if (next) {
            textCursor.movePosition(QTextCursor::End);
        } else {
            textCursor.movePosition(QTextCursor::Start);
        }
        textEdit->setTextCursor(textCursor);
    }
}

void FindReplaceForm::replace() {
    if (!textEdit) {
        emit en_replace();
        return;
    }
    if (!textEdit->textCursor().hasSelection()) {
        find();
    } else {
        textEdit->textCursor().insertText(ui->textToReplace->text());
        find();
    }
}

void FindReplaceForm::replaceAll() {
    if (!textEdit) {
        emit en_replaceAll();
        return;
    }
    int i=0;
    while (textEdit->textCursor().hasSelection()){
        textEdit->textCursor().insertText(ui->textToReplace->text());
        find();
        i++;
    }
    showMessage(tr("Replaced %1 occurrence(s)", "FindDialog").arg(i));
}

void FindReplaceForm::writeSettings(QSettings &settings, const QString &prefix) {
    settings.beginGroup(prefix);
    settings.setValue(TEXT_TO_FIND, ui->textToFind->text());
    settings.setValue(TEXT_TO_REPLACE, ui->textToReplace->text());
    settings.setValue(DOWN_RADIO, ui->downRadioButton->isChecked());
    settings.setValue(UP_RADIO, ui->upRadioButton->isChecked());
    settings.setValue(CASE_CHECK, ui->caseCheckBox->isChecked());
    settings.setValue(WHOLE_CHECK, ui->wholeCheckBox->isChecked());
    settings.setValue(REGEXP_CHECK, ui->regexCheckBox->isChecked());
    settings.endGroup();
}

void FindReplaceForm::readSettings(QSettings &settings, const QString &prefix) {
    settings.beginGroup(prefix);
    ui->textToFind->setText(settings.value(TEXT_TO_FIND, "").toString());
    ui->textToReplace->setText(settings.value(TEXT_TO_REPLACE, "").toString());
    ui->downRadioButton->setChecked(settings.value(DOWN_RADIO, true).toBool());
    ui->upRadioButton->setChecked(settings.value(UP_RADIO, false).toBool());
    ui->caseCheckBox->setChecked(settings.value(CASE_CHECK, false).toBool());
    ui->wholeCheckBox->setChecked(settings.value(WHOLE_CHECK, false).toBool());
    ui->regexCheckBox->setChecked(settings.value(REGEXP_CHECK, false).toBool());
    settings.endGroup();
}
