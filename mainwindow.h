#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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
    void updateStatusBar(int chars, int words);
    void tempNotImplementedDialog(QString actionName);
};

#endif // MAINWINDOW_H
