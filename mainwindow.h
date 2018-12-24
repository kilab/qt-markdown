#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

const QString APP_NAME = "Qt Markdown";
const QString APP_VENDOR = "Kilab";
const QString APP_VERSION = "0.0.0";
const QString APP_HOMEPAGE_URL = "https://github.com/kilab/qt-markdown";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSave_HTML_triggered();
    void on_actionSave_PDF_triggered();
    void on_actionHelp_triggered();
    void on_sourceTextarea_textChanged();

private:
    Ui::MainWindow *ui;
    QString getSaveFilePath(QString path);
    void updateStatusBar(int chars, int words);
};

#endif // MAINWINDOW_H
