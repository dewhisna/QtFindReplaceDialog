#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>

namespace Ui {
    class FindForm;
}

class FindForm : public QWidget {
    Q_OBJECT
public:
    FindForm(QWidget *parent = 0);
    ~FindForm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FindForm *ui;
};

#endif // FINDFORM_H
