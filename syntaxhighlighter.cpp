#include "syntaxhighlighter.h"

// Constructor
SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {

    // Keyword Formatting
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor(0, 0, 255)); // Blue
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns = {
        "\\bclass\\b", "\\bconst\\b", "\\bvoid\\b", "\\bint\\b", "\\bfloat\\b",
        "\\bdouble\\b", "\\bchar\\b", "\\bbool\\b", "\\bvirtual\\b", "\\bpublic\\b",
        "\\bprivate\\b", "\\bprotected\\b", "\\breturn\\b", "\\bif\\b", "\\belse\\b",
        "\\bwhile\\b", "\\bfor\\b", "\\bbreak\\b", "\\bcontinue\\b"
    };

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Single-line Comment Formatting
    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(QColor(0, 128, 0)); // Green
    HighlightingRule rule;
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    // Multi-line Comment Formatting
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");

    multiLineCommentFormat.setForeground(QColor(0, 128, 0)); // Green

    // String Literal Formatting
    QTextCharFormat stringFormat;
    stringFormat.setForeground(QColor(255, 0, 0)); // Red
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = stringFormat;
    highlightingRules.append(rule);
}

// Highlight Block Implementation
void SyntaxHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Multi-line Comments
    setCurrentBlockState(0);
    int startIndex = 0;

    if (previousBlockState() != 1) {
        startIndex = text.indexOf(commentStartExpression);
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }

        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
