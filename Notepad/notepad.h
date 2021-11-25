#pragma once

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; } // declare Notepad class in Ui namespace, generated from .ui files by uic tool
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT // declares this class as a QObject, must inherit from QObject (directly or indirectly)

public:
    explicit Notepad(QWidget *parent = nullptr); // Notepad cannot be implicitly instantiated
    ~Notepad();


private slots:  // used to prepare event handler
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionPrint_triggered();

    void on_actionCopy_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

//    void selectFont();

//    void setFontBold(bool bold);

//    void setFontUnderline(bool underline);

//    void setFontItalic(bool italic);

//    void about();

public:
    QString windowTitle = "New Document*";

private:
    Ui::Notepad *ui;
    QString currentFile;

};

