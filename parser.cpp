#include "parser.h"

#include <QDebug>
#include <QRegularExpression>
#include <QStringList>

Parser::Parser(QString textToParse)
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
    QString formattedText;
    QStringList stringLines = this->sourceText.split("\n", QString::SkipEmptyParts);

    for (const auto& line: stringLines) {
        if (QRegExp("#{1,5} (.*)").indexIn(line) == 0) {
            QRegExp rxHeader("# (.*)");
            rxHeader.indexIn(line);
            int headerLevel = line.indexOf("# ") + 1;

            formattedText += QString("<h%1>%2</h%1>").arg(headerLevel).arg(rxHeader.cap(1));
        } else if (QRegExp("\*(.*)\*|\*\*(.*)\*\*|_(.*)_|__(.*)__").indexIn(line) >= 0) {

        } else {
            formattedText += QString("<p>%1</p>").arg(line);
        }
    }

    this->formattedText = formattedText;
}
