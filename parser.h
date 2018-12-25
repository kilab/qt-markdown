#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QString>

class Parser : public QObject
{
    Q_OBJECT

public:
    explicit Parser(QString textToParse);
    QString getFormattedText();

private:
    void parseText();
    Q_INVOKABLE void ruleHeaders(QString regexRule);
    Q_INVOKABLE void ruleOl(QString regexRule);
    Q_INVOKABLE void ruleParagraphs(QString regexRule);
    Q_INVOKABLE void ruleUl(QString regexRule);

private:
    QString formattedText;
    QString sourceText;
};

#endif // PARSER_H
