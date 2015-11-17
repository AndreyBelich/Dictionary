#include <QtWidgets>
#include "editdialog.h"

EditDialog::EditDialog(const QVector<QString> &english, const QVector<QString> &russian, QWidget *parent)
    : QDialog(parent), findIndex(-1),replaceFlag(false)
{
    englishDictionary = english;
    russianDictionary = russian;

    QLabel *findText = new QLabel(tr("Введите искомый текст:"));
    findLine = new QLineEdit();
    findText->setBuddy(findLine);

    QLabel *englishText = new QLabel(tr("Найденный английский текст"));
    englishLine = new QLineEdit();

    QLabel *russianText = new QLabel(tr("Найденный русский текст"));
    russianLine = new QLineEdit();

    findButton = new QPushButton(tr("&Find"));
    replaceButton = new QPushButton(tr("&Replace"));

    QHBoxLayout *findLayout = new QHBoxLayout();
    findLayout->addWidget(findText);
    findLayout->addWidget(findLine);
    findLayout->addWidget(findButton);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(englishText,2,0);
    gridLayout->addWidget(englishLine,2,1);
    gridLayout->addWidget(russianText,3,0);
    gridLayout->addWidget(russianLine,3,1);
    gridLayout->addWidget(replaceButton,4,1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(findLayout);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);
    resize(450,300);
    setWindowTitle(tr("Edit window"));

    connect(findButton, SIGNAL(clicked()),this,SLOT(findSlot()));
    connect(replaceButton, SIGNAL(clicked()),this, SLOT(replaceSlot()));
}

void EditDialog::findSlot()
{
    if(findLine->text().isEmpty())
    {
        QMessageBox::information(0,tr("Message"),tr("Введите слово для поиска"));
        return;
    }
    QString findWord = findLine->text();
    for(int i = 0; i < englishDictionary.size(); i++)
    {
        if(findWord == englishDictionary[i])
        {
            findIndex = i;
            englishLine->setText(englishDictionary[i]);
            russianLine->setText(russianDictionary[i]);
            break;
        }
    }
    if(findIndex < 0)
    {
        QMessageBox::information(0,tr("Message"),tr("Поиск не дал результатов!"));
    }
}

void EditDialog::replaceSlot()
{
    if(englishLine->text().isEmpty() || russianLine->text().isEmpty())
    {
        QMessageBox::information(0,tr("Message"),tr("Одна или несколько строк пустые!\nЗамена недопустима."));
        return;
    }
    englishDictionary[findIndex] = englishLine->text();
    russianDictionary[findIndex] = russianLine->text();
    QMessageBox::information(0,tr("Message"),tr("Замена успешно проведена!"));
    findLine->clear();
    englishLine->clear();
    russianLine->clear();
    replaceFlag = true;
}

QVector<QString> EditDialog::getEnglishDictionary()const
{
    return englishDictionary;
}

QVector<QString> EditDialog::getRussianDictionary()const
{
    return russianDictionary;
}

void EditDialog::closeEvent(QCloseEvent *)
{
    if(replaceFlag)
    {
        accept();
    }
    else
    {
        reject();
    }
}
