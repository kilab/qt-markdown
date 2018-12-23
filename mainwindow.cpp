#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"

#include <QDebug>
#include <QMessageBox>

const QString APP_NAME = "Qt Markdown";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(APP_NAME);

    QFont editorsFont("Consolas, 'Fira Mono', 'Source Code Pro', Monospace", 10);
    ui->sourceTextarea->setFont(editorsFont);
    ui->targetTextarea->setFont(editorsFont);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHelp_triggered()
{
    this->tempNotImplementedDialog("Help");
}

void MainWindow::on_actionSave_HTML_triggered()
{
    this->tempNotImplementedDialog("Save HTML");
}

void MainWindow::on_actionSave_PDF_triggered()
{
    this->tempNotImplementedDialog("Save PDF");
}

void MainWindow::on_sourceTextarea_textChanged()
{
    // update status bar
    QString editorText = ui->sourceTextarea->toPlainText();
    QRegExp separator("( |\n)");
    QStringList words = editorText.split(separator);
    words.removeAll("");

    this->updateStatusBar(editorText.count(), words.count());

    // update target editor text
    Parser *parser = new Parser(editorText);

    ui->targetTextarea->setHtml(parser->getFormattedText());
}

void MainWindow::updateStatusBar(int chars, int words)
{
    ui->statusBar->showMessage(QString("Characters: %1 | Words: %2").arg(chars).arg(words));
}

void MainWindow::tempNotImplementedDialog(QString actionName)
{
    QMessageBox::information(this, APP_NAME, QString("Action <b>'%1'</b> is not implemented yet.").arg(actionName), QMessageBox::Ok);
}

