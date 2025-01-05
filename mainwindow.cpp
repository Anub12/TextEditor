#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Create editor widget
    editor = new QTextEdit(this);
    setCentralWidget(editor);

    // Add syntax highlighting
    highlighter = new SyntaxHighlighter(editor->document());
}

MainWindow::~MainWindow() {
    delete ui;
}
