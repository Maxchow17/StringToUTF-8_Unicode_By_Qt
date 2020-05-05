#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLineEdit *m_chineseEdit;

    QLineEdit *m_unicodeEdit;

    QLineEdit *m_utf8Edit;

    QLineEdit *m_gbkEdit;

    QPushButton *m_chineseToCodeButton;

    QPushButton *m_codeToChineseButton;

    QPushButton *m_clearButton;

private slots:
    void onClickedChineseToCodeButton();

    void onClickedClearButton();
};

#endif // MAINWINDOW_H
