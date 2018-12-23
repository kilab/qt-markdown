#ifndef PARSER_H
#define PARSER_H

#include <QString>

class Parser
{
public:
    Parser(QString textToParse);
    QString getFormattedText();

private:
    void parseText();

private:
    QString formattedText;
    QString sourceText;
};

#endif // PARSER_H
