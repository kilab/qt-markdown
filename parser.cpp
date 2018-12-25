#include "parser.h"

#include <QDebug>
#include <QMetaObject>
#include <QRegularExpression>
#include <QStringList>

Parser::Parser(QString textToParse) : QObject ()
{
    this->sourceText = textToParse;
}

QString Parser::getFormattedText()
{
    if (this->formattedText == "") {
        this->parseText();
    }

    return this->formattedText;
}

void Parser::parseText()
{
    this->formattedText = this->sourceText;

    // Thanks for regex rules to: Johnny Broadway <johnny@johnnybroadway.com>
    // https://gist.github.com/jbroadway/2836900
    QList<QPair<QString, QString> > regexRules;

    // TODO: more simple array
    regexRules.append(QPair<QString, QString>("(#+)\\s(.*)", "ruleHeaders")); // headers
    regexRules.append(QPair<QString, QString>("\\*\\*(.*)\\*\\*", "<b>\\1</b>")); // bold
    regexRules.append(QPair<QString, QString>("__(.*)__", "<b>\\1</b>")); // bold
    regexRules.append(QPair<QString, QString>("\\*(.*)\\*", "<i>\\1</i>")); // italic / emphasis
    regexRules.append(QPair<QString, QString>("_(.*)_", "<i>\\1</i>")); // italic / emphasis
    regexRules.append(QPair<QString, QString>("`(.*?)`", "<code>\\1</code>")); // strike / deleted
    regexRules.append(QPair<QString, QString>("\\~\\~(.*)\\~\\~", "<s>\\1</s>")); // strike / deleted
    regexRules.append(QPair<QString, QString>("\\[([^\\[]+)\\]\\(([^\\)]+)\\)", "<a href=\"\\2\">\\1</a>")); // link
    regexRules.append(QPair<QString, QString>("\n-{3,}", "\n<hr />")); // horizontal rule
    regexRules.append(QPair<QString, QString>("\n\\*(.*)", "ruleUl")); // ul lists
    regexRules.append(QPair<QString, QString>("\n[0-9]+\\.(.*)", "ruleOl")); // ol lists
    regexRules.append(QPair<QString, QString>("\n([^\n]+)\n", "ruleParagraphs")); // paragraph

    for (int i = 0; i < regexRules.count(); i++) {
        const QMetaObject *metaObject = this->metaObject();
        QString rule  = regexRules[i].first;
        QString toReplace = regexRules[i].second;
        QByteArray callbackName = QString("%1(QString)").arg(toReplace).toLocal8Bit();

        if (metaObject->indexOfMethod(callbackName) > -1) {
            metaObject->invokeMethod(this, toReplace.toLocal8Bit(), Q_ARG(QString, rule));
        } else {
            QRegularExpression regex(rule);
            regex.setPatternOptions(QRegularExpression::InvertedGreedinessOption);

            this->formattedText.replace(regex, toReplace);
        }
    }
}

void Parser::ruleHeaders(QString regexRule)
{
    QRegularExpression regex(regexRule);
    QRegularExpressionMatchIterator iterator(regex.globalMatch(this->formattedText));

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString toReplace = QString("<h%1>%2</h%1>").arg(match.captured(1).count()).arg(match.captured(2));

        if (match.captured(1).count() > 5) {
            return;
        }

        this->formattedText.replace(match.captured(0), toReplace);
    }
}

void Parser::ruleOl(QString regexRule)
{
    QRegularExpression regex(regexRule);
    QRegularExpressionMatchIterator iterator(regex.globalMatch(this->formattedText));
    QString contentToReplace = QString("<ol>\n");

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        contentToReplace += QString("<li>%1</li>").arg(match.captured(1));
    }

    contentToReplace += "</ol>\n";
    this->formattedText.replace(regex, contentToReplace);
}

void Parser::ruleParagraphs(QString regexRule)
{

}

void Parser::ruleUl(QString regexRule)
{

}
