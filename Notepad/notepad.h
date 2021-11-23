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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } // declare Notepad class in Ui namespace, generated from .ui files by uic tool
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT // declares this class as a QObject, must inherit from QObject (directly or indirectly)

public:
    explicit Notepad(QWidget *parent = nullptr); // Notepad cannot be implicitly instantiated
    ~Notepad();

private slots:  // used to prepare event handler
    void newDocument();

    void open();

    void save();

    void saveAs();

    void print();

    void copy();

    void exit();

    void cut();

    void paste();

    void redo();

    void undo();

//    void selectFont();

//    void setFontBold(bool bold);

//    void setFontUnderline(bool underline);

//    void setFontItalic(bool italic);

//    void about();

private:
    Ui::MainWindow *ui;
    QString currentFile;
};

