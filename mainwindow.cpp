#include "helpdialog.h"
#include "mainwindow.h"
#include "parser.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(APP_NAME);

    QFont editorsFont("Consolas, 'Fira Mono', 'Source Code Pro', Monospace", 10);
    ui->sourceTextarea->setFont(editorsFont);
    ui->targetTextarea->setFont(editorsFont);

    ui->targetTextarea->setOpenExternalLinks(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHelp_triggered()
{
    HelpDialog *helpDialog = new HelpDialog(this);
    helpDialog->show();
    helpDialog->raise();
    helpDialog->activateWindow();
}

void MainWindow::on_actionSave_HTML_triggered()
{
    QString filePath = this->getSaveFilePath("html");

    if (filePath == nullptr) {
        return;
    }

    QFile fileToSave(filePath);
    fileToSave.open(QIODevice::WriteOnly);
    fileToSave.write(ui->targetTextarea->toHtml().toLocal8Bit());
    fileToSave.close();

    ui->statusBar->showMessage(tr("Parsed content saved to: %1").arg(filePath));
}

void MainWindow::on_actionSave_PDF_triggered()
{
    QString filePath = this->getSaveFilePath("pdf");

    if (filePath == nullptr) {
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFileName(filePath);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);
    printer.setPaperSize(QPrinter::A4);

    QTextDocument doc;
    doc.setHtml(ui->targetTextarea->toHtml());
    doc.print(&printer);

    ui->statusBar->showMessage(tr("Parsed content saved to: %1").arg(filePath));
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

    QTextCursor cursor = ui->targetTextarea->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->targetTextarea->setTextCursor(cursor);
}

QString MainWindow::getSaveFilePath(QString ext)
{
    QFileDialog saveDialog(this, tr("Choose location to save %1 file...").arg(ext.toUpper()));
    saveDialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    saveDialog.setDefaultSuffix(ext);
    saveDialog.setDirectory(QDir::home());
    saveDialog.setNameFilter(tr("%1 file (*.%2)").arg(ext.toUpper()).arg(ext));

    if (saveDialog.exec()) {
        return saveDialog.selectedFiles().first();
    } else {
        return nullptr;
    }
}

void MainWindow::updateStatusBar(int chars, int words)
{
    ui->statusBar->showMessage(tr("Characters: %1 | Words: %2").arg(chars).arg(words));
}
