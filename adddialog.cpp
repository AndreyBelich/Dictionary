#include <QtWidgets>
#include "adddialog.h"

AddDialog::AddDialog(const QVector<QString> &englishWords, const QVector<QString> &russianWords, QWidget *parent)
    :QDialog(parent),flag(false)
{
    russianDictionary = russianWords;
    englishDictionary = englishWords;

    QLabel *englishLabel = new QLabel(tr("Введите &английское слово"));
    QLabel *russianLabel = new QLabel(tr("Введите &русское слово"));

    russianLine = new QLineEdit;
    russianLabel->setBuddy(russianLine);

    englishLine = new QLineEdit;
    englishLabel->setBuddy(englishLine);

    addButton = new QPushButton(tr("Добавить..."));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(englishLabel,0,0);
    mainLayout->addWidget(englishLine,0,1);
    mainLayout->addWidget(russianLabel,1,0);
    mainLayout->addWidget(russianLine,1,1);
    mainLayout->addWidget(addButton,2,1);

    setLayout(mainLayout);

    connect(addButton, SIGNAL(clicked()),this, SLOT(addWords()));
}

void AddDialog::addWords()
{
    if(englishLine->text().isEmpty() || russianLine->text().isEmpty())
    {
        QMessageBox::information(0,tr("Message"),tr("Заполните строки"));
        return;
    }
    if(englishDictionary.contains(englishLine->text()))
    {
        QMessageBox::information(0,tr("Message"),tr("Данное слово уже присутствует в словаре."));
        return;
    }
    russianDictionary.push_back(russianLine->text());
    englishDictionary.push_back(englishLine->text());
    QMessageBox::information(0,tr("Message"),tr("Слова успешно добавлены в словарь"));
    flag = true;
    englishLine->clear();
    russianLine->clear();
}

void AddDialog::closeEvent(QCloseEvent *)
{
    if(flag)
    {
        accept();
    }
    else
    {
        reject();
    }
}

QVector<QString> AddDialog::getRussianDictionary()const
{
    return russianDictionary;
}

QVector<QString> AddDialog::getEnglishDictionary()const
{
    return englishDictionary;
}
