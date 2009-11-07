#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_findDialog = new FindDialog(this);
    m_findDialog->setModal(false);

    ui->textEdit->setText(
            "Here's some text\nYou can use it to find\n"
            "with the Find/Replace dialog\n"
            "and do some tests. :)"
            );

    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions() {
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(findDialog()));

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::about()
{
      QMessageBox::about(this, tr("About Find/Replace Example"),
            tr("Simple application showing Find/Replace Dialog.<br><br>") +
                + "Author: <a href=\"http://www.lorenzobettini.it\">Lorenzo Bettini</a><br><br>");
}

void MainWindow::findDialog() {
    m_findDialog->show();
}
