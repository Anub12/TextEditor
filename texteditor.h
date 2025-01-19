#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QCompleter>
#include <QStringListModel>
#include "syntaxhighlighter.h"
#include "linenumberarea.h"

class TextEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
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
    void insertComplete(const QString &completion);

private:
    QPlainTextEdit *textEdit;
    SyntaxHighlighter *highlighter;
    QWidget *lineNumberArea;
    QCompleter *completer;
    QStringListModel *model;
    void createMenus();
};

#endif // TEXTEDITOR_H