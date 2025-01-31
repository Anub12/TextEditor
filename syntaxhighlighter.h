#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class QTextDocument;

class SyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument * parent = nullptr);
protected:
    void highlightBlock(const QString &text) override;
private:
    void setupHighlightingRules();

    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // SYNTAXHIGHLIGHTER_H
