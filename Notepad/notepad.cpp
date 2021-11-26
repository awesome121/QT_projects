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

//    connect(ui->actionNew, &QAction::triggered, this, &Notepad::on_actionNew_triggered);
//    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::on_actionOpen_triggered, Qt::UniqueConnection);
//    connect(ui->actionSave, &QAction::triggered, this, &Notepad::on_actionSave_triggered);
//    connect(ui->actionSaveAs, &QAction::triggered, this, &Notepad::on_actionSaveAs_triggered);
//    connect(ui->actionPrint, &QAction::triggered, this, &Notepad::on_actionPrint_triggered);
//    connect(ui->actionExit, &QAction::triggered, this, &Notepad::on_actionExit_triggered);
//    connect(ui->actionCopy, &QAction::triggered, this, &Notepad::on_actionCopy_triggered);
//    connect(ui->actionCut, &QAction::triggered, this, &Notepad::on_actionCut_triggered);
//    connect(ui->actionPaste, &QAction::triggered, this, &Notepad::on_actionPaste_triggered);
//    connect(ui->actionUndo, &QAction::triggered, this, &Notepad::on_actionUndo_triggered);
//    connect(ui->actionRedo, &QAction::triggered, this, &Notepad::on_actionRedo_triggered);
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

void Notepad::initSettings()
{
    isNewFile = true; // a new file is open, set to false once editing
    isChanged = false; // is the text edited
    isFontBold = false;
    isFontItalic = false;
    isFontUnderline = false;
}

/*
 * Return 1 on saving, 2 on discard, 3 on cancel
 */
int Notepad::showExitConfirmation()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:
        try {
            on_actionSave_triggered();
        } catch (int e) {
            return 0;
        }
        return 1;
    case QMessageBox::Discard:
        return 2;
    case QMessageBox::Cancel:
        return 3;
    default:
        std::cout << "Exit confirmation case error" << std::endl;
        return 0;
    }
}


/*
 * Return 1 on saving, 2 on discard
 */
int Notepad::showExitConfirmationWithoutCancel()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Save:
            try {
                on_actionSave_triggered();
            } catch (int e) {
                return 0;
            }
            return 1;
        case QMessageBox::Discard:
            return 2;
        default:
            std::cout << "Exit confirmation case error" << std::endl;
            return 0;
    }
}

void Notepad::on_actionNew_triggered()
{
    int ret = 0;
    if (isChanged) {
       ret = showExitConfirmation();
    }
    if (ret == 0 || ret == 1 || ret == 2) {
        initSettings();
        currentFile.clear();
        ui->textEdit->setText(QString());
        windowTitle = "New Document";
        setWindowTitle(windowTitle);
    }
}


void Notepad::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QFile::Text)) {
        if (isChanged) {
            showExitConfirmationWithoutCancel();
        }
        initSettings();
        currentFile = fileName;
        windowTitle = fileName;
        setWindowTitle(windowTitle);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
    }


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
    if (file.open(QIODevice::WriteOnly | QFile::Text)) {
        windowTitle = fileName;
        setWindowTitle(windowTitle);
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
        isChanged = false;
    }


}

void Notepad::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    std::cout << QFile::Text << std::endl;
    if (file.open(QIODevice::WriteOnly | QFile::Text)) {
        currentFile = fileName;
        windowTitle = fileName;
        setWindowTitle(windowTitle);
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
        isChanged = false;
    }
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
    int ret = showExitConfirmation();
    if (ret == 3) {
        return ; // ignore
    } else {
        QCoreApplication::quit();
    }
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

void Notepad::on_actionSelect_Font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Notepad::on_textEdit_textChanged()
{
    if (isNewFile) { // not editing
        isNewFile = false;
        isChanged = false;
    } else { // editing
        isChanged = true;
        setWindowTitle(windowTitle + "*");
    }
}


void Notepad::on_actionBold_triggered()
{
    ui->textEdit->setFontWeight(isFontBold ? QFont::Bold : QFont::Normal);
    isFontBold = !isFontBold;

}

void Notepad::on_actionItalic_triggered()
{
    ui->textEdit->setFontItalic(!isFontItalic);
    isFontItalic = !isFontItalic;
}

void Notepad::on_actionUnderline_triggered()
{
    ui->textEdit->setFontUnderline(!isFontUnderline);
    isFontUnderline = !isFontUnderline;
}


void Notepad::on_actionMaximise_triggered()
{
    setWindowState(Qt::WindowMaximized);
}

void Notepad::on_actionMinimise_triggered()
{
    setWindowState(Qt::WindowMinimized);
}

void Notepad::on_actionZoom_in_triggered()
{
    ui->textEdit->zoomIn(1.5);
}

void Notepad::on_actionZoom_out_triggered()
{
    ui->textEdit->zoomOut(1.5);
}

void Notepad::closeEvent(QCloseEvent* event)
{
    int ret = 0;
    ret = showExitConfirmation();
    if (ret == 0 || ret == 3) {
        event->ignore();
    }
}
