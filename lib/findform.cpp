#include "findform.h"
#include "ui_findform.h"

FindForm::FindForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindForm)
{
    ui->setupUi(this);
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
