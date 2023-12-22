/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>
#include <QTextDocument>

#include "findreplace_global.h"

namespace Ui {
    class FindReplaceDialog;
}

class QTextEdit;
class QSettings;

/**
  * A find/replace dialog.
  *
  * It relies on a FindReplaceForm object (see that class for the functionalities provided).
  */
class FINDREPLACESHARED_EXPORT FindReplaceDialog : public QDialog {
    Q_OBJECT
public:
    FindReplaceDialog(QWidget *parent = 0);
    virtual ~FindReplaceDialog();

    /**
      * Associates the text editor where to perform the search
      * @param textEdit
      */
    void setTextEdit(QTextEdit *textEdit);

    /**
      * enableRegExpControls
      * @param enable - enable/disable RegExp Controls
      */
    virtual void enableRegExpControls(bool enable);

    /**
      * Writes the state of the form to the passed settings.
      * @param settings
      * @param prefix the prefix to insert in the settings
      */
    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    /**
      * Reads the state of the form from the passed settings.
      * @param settings
      * @param prefix the prefix to look for in the settings
      */
    virtual void readSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    /**
      * Returns the current find settings from the form.
      */
    virtual QTextDocument::FindFlags findFlags(bool down) const;

    /**
      * regExpMode - Returns true if regExp mode is selected
      */
    virtual bool regExpMode() const;

    /**
      * Returns the text to find
      */
    virtual QString textToFind() const;

signals:
    /**
      * en_findNext - emitted for find(true) when QTextEdit is nullptr
      */
    void en_findNext();

    /**
      * en_findPrev - emitted for find(false) when QTextEdit is nullptr
      */
    void en_findPrev();

    /**
      * en_replace - emitted for replace when QTextEdit is nullptr
      */
    void en_replace();

    /**
      * en_replaceAll - emitted for replaceAll when QTextEdit is nullptr
      */
    void en_replaceAll();

public slots:
    /**
     * Sets the current textToFind (used to set it from specialized current selection, etc)
     */
    void setTextToFind(const QString &strText);

    /**
     * Finds the next or previous occurrence:
     */
    void find();

    /**
     * Finds the next occurrence
     */
    void findNext();

    /**
     * Finds the previous occurrence
     */
    void findPrev();

protected:
    virtual void changeEvent(QEvent *e) override;

    Ui::FindReplaceDialog *ui;
};

#endif // FINDREPLACEDIALOG_H
