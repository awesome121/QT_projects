#include "notepad.h"
#include <QApplication> // Handles widget specific initialization, finalization

int main(int argc, char *argv[])
{
    QApplication EditorApp(argc, argv);  // manages application-wide resources for any QT widgets
    Notepad Editor; // the object for which the wizard created the class and UI file
    Editor.show(); // make widgets visible
    return EditorApp.exec(); // enter event loop, events are generated and sent to widgets (e.g. mouse click)
}
