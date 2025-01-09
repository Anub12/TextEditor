#include "texteditor.h"
#include "linenumberarea.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QAction>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>
#include <QVBoxLayout>

TextEditor::TextEditor(QWidget *parent) : QMainWindow(parent) {
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    // Set tab stop width to 4 spaces
    QFontMetrics metrics(textEdit->font());
    textEdit->setTabStopDistance(4 * metrics.horizontalAdvance(' '));

    highlighter = new SyntaxHighlighter(textEdit->document());

    lineNumberArea = new LineNumberArea(this);

    connect(textEdit->document(), &QTextDocument::blockCountChanged, this, &TextEditor::updateLineNumberAreaWidth);
    connect(textEdit->verticalScrollBar(), &QScrollBar::valueChanged, this, [this]() { updateLineNumberArea(textEdit->rect(), 0); });
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &TextEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    createMenus();
}

int TextEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, textEdit->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + textEdit->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space + 5; // Add 5 pixels gap
}

void TextEditor::updateLineNumberAreaWidth(int /* newBlockCount */) {
    int leftMargin = lineNumberAreaWidth() + 10;
    textEdit->setContentsMargins(leftMargin, 0, 0, 0);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void TextEditor::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(textEdit->viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void TextEditor::resizeEvent(QResizeEvent *e) {
    QMainWindow::resizeEvent(e);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void TextEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!textEdit->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    textEdit->setExtraSelections(extraSelections);
}

void TextEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = textEdit->document()->begin();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(textEdit->viewport()->geometry().top());
    int bottom = top + static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), textEdit->fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void TextEditor::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setText(in.readAll());
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Cannot open file");
        }
    }
}

void TextEditor::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Cannot save file");
        }
    }
}

void TextEditor::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *openAction = fileMenu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile);

    QAction *saveAction = fileMenu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    QMenu *editMenu = menuBar()->addMenu("Edit");

    QAction *cutAction = editMenu->addAction("Cut");
    connect(cutAction, &QAction::triggered, textEdit, &QTextEdit::cut);

    QAction *copyAction = editMenu->addAction("Copy");
    connect(copyAction, &QAction::triggered, textEdit, &QTextEdit::copy);

    QAction *pasteAction = editMenu->addAction("Paste");
    connect(pasteAction, &QAction::triggered, textEdit, &QTextEdit::paste);

    QAction *undoAction = editMenu->addAction("Undo");
    connect(undoAction, &QAction::triggered, textEdit, &QTextEdit::undo);

    QAction *redoAction = editMenu->addAction("Redo");
    connect(redoAction, &QAction::triggered, textEdit, &QTextEdit::redo);
}