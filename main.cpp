#include <QApplication>
#include "texteditor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TextEditor editor;
    editor.resize(800, 600);
    editor.show();
    return app.exec();
}
