#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class FindDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

    void createActions();

private slots:
    void about();

    void findDialog();

private:
    Ui::MainWindow *ui;

    FindDialog *m_findDialog;
};

#endif // MAINWINDOW_H
