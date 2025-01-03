#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);

private slots:
    void openFile();
    void saveFile();

private:
    QTextEdit *textEdit;
    void createMenus();
};

#endif // TEXTEDITOR_H
