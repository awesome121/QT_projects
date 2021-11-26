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
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; } // declare Notepad class in Ui namespace, generated from .ui files by uic tool
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT // declares this class as a QObject, must inherit from QObject (directly or indirectly)

public:
    explicit Notepad(QWidget *parent = nullptr); // Notepad cannot be implicitly instantiated
    ~Notepad();
    void initSettings();


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

    void on_actionSelect_Font_triggered();

    void on_textEdit_textChanged();

    void on_actionBold_triggered();

    void on_actionItalic_triggered();

    void on_actionUnderline_triggered();

    void on_actionMaximise_triggered();

    void on_actionMinimise_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();
//--------
    int showExitConfirmation();

    int showExitConfirmationWithoutCancel();

    void closeEvent(QCloseEvent* event);

public:
    QString windowTitle = "New Document";
    bool isNewFile = true;
    bool isChanged = false;
    bool isFontBold = false;
    bool isFontItalic = false;
    bool isFontUnderline = false;



private:
    Ui::Notepad *ui;
    QString currentFile;

};

