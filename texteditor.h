#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include "syntaxhighlighter.h"
#include "linenumberarea.h"

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void openFile();
    void saveFile();
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QTextEdit *textEdit;
    SyntaxHighlighter *highlighter;
    QWidget *lineNumberArea;
    void createMenus();
};

#endif // TEXTEDITOR_H
