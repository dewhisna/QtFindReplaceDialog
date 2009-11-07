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

    ui->errorTextEdit->setVisible(false);

    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(validateRegExp(QString)));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find()));
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

void FindForm::validateRegExp(const QString &text) {
    if (!ui->regexCheckBox->isChecked() || ui->textToFind->text().size() == 0) {
        ui->errorTextEdit->setVisible(false);
        return; // nothing to validate
    }

    QRegExp reg(ui->textToFind->text(),
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

    if (reg.isValid()) {
        ui->errorTextEdit->setVisible(false);
    } else {
        ui->errorTextEdit->setText("error in regular expression:\n");
        ui->errorTextEdit->append(reg.errorString());
        ui->errorTextEdit->setVisible(true);
    }
}

void FindForm::find() {
    if (!textEdit)
        return; // TODO: show some warning?

    // backward search
    bool back = ui->upRadioButton->isChecked();

    const QString &toSearch = ui->textToFind->text();

    /*
    if (back)
            textCursor = textEdit->document()->find(toSearch,textCursor,QTextDocument::FindBackward);
    else
            textCursor = textEdit->document()->find(toSearch,textCursor);
    */

    qDebug() << "searching for: " << toSearch;

    if (back)
            textEdit->find(toSearch,QTextDocument::FindBackward);
    else
            textEdit->find(toSearch);
}

