#include "mainwindow.h"
#include <QTextCodec>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout *vbox = new QVBoxLayout;
    widget->setLayout(vbox);

    // Chinese String Input
    QHBoxLayout *chineseHbox = new QHBoxLayout;
    vbox->addLayout(chineseHbox);
    m_chineseEdit = new QLineEdit;
    QLabel *chineseLabel = new QLabel("Chinese: ");
    chineseHbox->addWidget(chineseLabel);
    chineseHbox->addWidget(m_chineseEdit);

    // Convert Button
    QHBoxLayout *buttonHbox = new QHBoxLayout;
    vbox->addLayout(buttonHbox);
    m_chineseToCodeButton = new QPushButton("convert");
    buttonHbox->addWidget(m_chineseToCodeButton);
    m_clearButton = new QPushButton("clear");
    buttonHbox->addWidget(m_clearButton);

    // code output
    // unicode
    QHBoxLayout *unicodeHbox = new QHBoxLayout;
    vbox->addLayout(unicodeHbox);
    QLabel *unicodeLabel = new QLabel("Unicode: ");
    unicodeHbox->addWidget(unicodeLabel);
    m_unicodeEdit = new QLineEdit;
    unicodeHbox->addWidget(m_unicodeEdit);

    // utf-8
    QHBoxLayout *utf8Hbox = new QHBoxLayout;
    vbox->addLayout(utf8Hbox);
    QLabel *utf8Label = new QLabel("UTF-8: ");
    utf8Hbox->addWidget(utf8Label);
    m_utf8Edit = new QLineEdit;
    utf8Hbox->addWidget(m_utf8Edit);

    // GBK
    QHBoxLayout *gbkHbox = new QHBoxLayout;
    vbox->addLayout(gbkHbox);
    QLabel *gbkLabel = new QLabel("GBK: ");
    gbkHbox->addWidget(gbkLabel);
    m_gbkEdit = new QLineEdit;
    gbkHbox->addWidget(m_gbkEdit);

    connect(m_chineseToCodeButton, &QPushButton::clicked, this, &MainWindow::onClickedChineseToCodeButton);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::onClickedClearButton);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onClickedChineseToCodeButton()
{
    QString text = m_chineseEdit->text();


    QString strUnicode;
    QString strUtf8;
    QString strGBK;

    for (int i = 0; i < text.length(); i++) {
        QChar chr = text.at(i);
        QString strChr;
        strChr.append(chr);

        // unicode
        uint16_t unicode = 0;
        memcpy(&unicode, strChr.utf16(), 2);
        strUnicode.append(QString::number(unicode, 16).toUpper());
        strUnicode.append(' ');

        // utf-8
        QString utf8Hex = QString(strChr.toUtf8().toHex()).toUpper();
        strUtf8.append(utf8Hex);
        strUtf8.append(' ');

        // GB18030
        QTextCodec *gb18030Codec = QTextCodec::codecForName("GB18030");
        QByteArray gb18030Data = gb18030Codec->fromUnicode(strChr);
        QString gb18030Hex = QString(gb18030Data.toHex()).toUpper();
        strGBK.append(gb18030Hex);
        strGBK.append(' ');
    }
    m_unicodeEdit->setText(strUnicode);
    m_utf8Edit->setText(strUtf8);
    m_gbkEdit->setText(strGBK);
}

void MainWindow::onClickedClearButton()
{
    m_chineseEdit->clear();
    m_utf8Edit->clear();
    m_gbkEdit->clear();
}
