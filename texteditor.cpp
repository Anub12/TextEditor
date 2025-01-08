#include "texteditor.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

TextEditor::TextEditor(QWidget *parent) : QMainWindow(parent) {
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    highlighter = new SyntaxHighlighter(textEdit->document());

    createMenus();
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
}
