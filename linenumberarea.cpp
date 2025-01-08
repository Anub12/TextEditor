#include "linenumberarea.h"
#include "texteditor.h"

LineNumberArea::LineNumberArea(TextEditor *editor) : QWidget(editor), textEditor(editor) {}

QSize LineNumberArea::sizeHint() const {
    return QSize(textEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    textEditor->lineNumberAreaPaintEvent(event);
}