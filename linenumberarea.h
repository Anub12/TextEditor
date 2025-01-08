#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "texteditor.h"

class TextEditor;

class LineNumberArea : public QWidget {
public:
    LineNumberArea(TextEditor *editor);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TextEditor *textEditor;
};

#endif // LINENUMBERAREA_H