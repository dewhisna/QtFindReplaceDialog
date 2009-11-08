#include <QtGui>
#include <QTextEdit>
#include <QRegExp>

#include "findform.h"
#include "ui_findform.h"

FindForm::FindForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindForm), textEdit(0)
{
    ui->setupUi(this);

    ui->errorLabel->setText("");

    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(validateRegExp(QString)));

    connect(ui->regexCheckBox, SIGNAL(toggled(bool)), this, SLOT(regexpSelected(bool)));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find()));
    connect(ui->closeButton, SIGNAL(clicked()), parent, SLOT(close()));
}

FindForm::~FindForm()
{
    delete ui;
}

void FindForm::changeEvent(QEvent *e)
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

void FindForm::textToFindChanged() {
    ui->findButton->setEnabled(ui->textToFind->text().size() > 0);
}

void FindForm::regexpSelected(bool sel) {
    if (sel)
        validateRegExp(ui->textToFind->text());
    else
        validateRegExp("");
}

void FindForm::validateRegExp(const QString &text) {
    if (!ui->regexCheckBox->isChecked() || text.size() == 0) {
        ui->errorLabel->setText("");
        return; // nothing to validate
    }

    QRegExp reg(text,
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

    if (reg.isValid()) {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:#ff0000;\">" +
                                reg.errorString() +
                                "</spam>");
    }
}

void FindForm::find() {
    if (!textEdit)
        return; // TODO: show some warning?

    // backward search
    bool back = ui->upRadioButton->isChecked();

    const QString &toSearch = ui->textToFind->text();

    if (ui->regexCheckBox->isChecked()) {
        QRegExp reg(toSearch,
                    (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

        qDebug() << "searching for regexp: " << reg.pattern();

        if (back) {
            textCursor = textEdit->document()->find(reg, textCursor, QTextDocument::FindBackward);
        } else {
            textCursor = textEdit->document()->find(reg, textCursor);
        }

        textEdit->setTextCursor(textCursor);
    } else {
        qDebug() << "searching for: " << toSearch;

        QTextDocument::FindFlags flags;

        if (back)
            flags |= QTextDocument::FindBackward;
        if (ui->caseCheckBox)
            flags |= QTextDocument::FindCaseSensitively;

        textEdit->find(toSearch, flags);
    }
}

