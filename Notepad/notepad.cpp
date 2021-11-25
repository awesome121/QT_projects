#include "notepad.h"
#include "ui_notepad.h"
#include <iostream>

Notepad::Notepad(QWidget *parent)  // constructor
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle(windowTitle);

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::on_actionNew_triggered);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::on_actionOpen_triggered);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::on_actionSave_triggered);
    connect(ui->actionSaveAs, &QAction::triggered, this, &Notepad::on_actionSaveAs_triggered);
    connect(ui->actionPrint, &QAction::triggered, this, &Notepad::on_actionPrint_triggered);
    connect(ui->actionExit, &QAction::triggered, this, &Notepad::on_actionExit_triggered);
    connect(ui->actionCopy, &QAction::triggered, this, &Notepad::on_actionCopy_triggered);
    connect(ui->actionCut, &QAction::triggered, this, &Notepad::on_actionCut_triggered);
    connect(ui->actionPaste, &QAction::triggered, this, &Notepad::on_actionPaste_triggered);
    connect(ui->actionUndo, &QAction::triggered, this, &Notepad::on_actionUndo_triggered);
    connect(ui->actionRedo, &QAction::triggered, this, &Notepad::on_actionRedo_triggered);
//    connect(ui->actionFont, &QAction::triggered, this, &Notepad::selectFont);
//    connect(ui->actionBold, &QAction::triggered, this, &Notepad::setFontBold);
//    connect(ui->actionUnderline, &QAction::triggered, this, &Notepad::setFontUnderline);
//    connect(ui->actionItalic, &QAction::triggered, this, &Notepad::setFontItalic);
//    connect(ui->actionAbout, &QAction::triggered, this, &Notepad::about);


#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}

Notepad::~Notepad() // destructor
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
    }
    windowTitle = fileName;
    setWindowTitle(windowTitle);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::on_actionSave_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
    }
    windowTitle = fileName;
    setWindowTitle(windowTitle);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

void Notepad::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    std::cout << QFile::Text << std::endl;
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
    }
    currentFile = fileName;
    windowTitle = fileName;
    setWindowTitle(windowTitle);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif
    ui->textEdit->print(&printDev);
#endif
}

void Notepad::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void Notepad::on_actionCopy_triggered()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}

void Notepad::on_actionCut_triggered()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void Notepad::on_actionPaste_triggered()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//void Notepad::selectFont()
//{
//    bool fontSelected;
//    QFont font = QFontDialog::getFont(&fontSelected, this);
//    if (fontSelected)
//        ui->textEdit->setFont(font);
//}



