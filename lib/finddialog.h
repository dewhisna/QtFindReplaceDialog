#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
    class FindDialog;
}

class QTextEdit;

class FindDialog : public QDialog {
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();

    /**
      * Associates the text editor where to perform the search
      * @param textEdit_
      */
    void setTextEdit(QTextEdit *textEdit);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
