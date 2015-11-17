#include <QtWidgets>
#include "adddialog.h"
#include "testdialog.h"
#include "editdialog.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    readFile("newRussianWords.txt", newRussianWords);
    readFile("newEnglishWords.txt", newEnglishWords);
    readFile("russianDictionary.txt", russianDictionary);
    readFile("englishDictionary.txt", englishDictionary);
    readFile("newEnglishSentences.txt", newEnglishSentences);
    readFile("newRussianSentences.txt", newRussianSentences);
    readFile("russianSentences.txt", russianSentences);
    readFile("englishSentences.txt", englishSentences);


    addWordButton = new QPushButton(tr("&Добавить новые слова"));
    addWordButton->setFixedSize(250,200);

    testWordButton = new QPushButton(tr("&Тест слов"));
    testWordButton->setFixedSize(250,200);

    importWordButton = new QPushButton(tr("&Импортировать слова"));
    importWordButton->setFixedSize(250,200);

    editWordButton = new QPushButton(tr("&Правка слов"));
    editWordButton->setFixedSize(250,200);

    addSentencesButton = new QPushButton(tr("Добавить предложения"));
    addSentencesButton->setFixedSize(250,200);

    testSentencesButton = new QPushButton(tr("Тест предложений"));
    testSentencesButton->setFixedSize(250,200);

    editSentencesButton = new QPushButton(tr("Правка предложений"));
    editSentencesButton->setFixedSize(250,200);

    importSentencesButton = new QPushButton(tr("Импорт предложений"));
    importSentencesButton->setFixedSize(250,200);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(testWordButton,0,0);
    mainLayout->addWidget(addWordButton,0,1);
    mainLayout->addWidget(importWordButton,0,2);
    mainLayout->addWidget(editWordButton,0,3);
    mainLayout->addWidget(testSentencesButton,1,0);
    mainLayout->addWidget(addSentencesButton,1,1);
    mainLayout->addWidget(importSentencesButton,1,2);
    mainLayout->addWidget(editSentencesButton,1,3);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
    resize(1000,400);
    setWindowTitle(tr("Словарь"));

    setStyleSheet("QPushButton{background:green;font-size:20px;};");

    connect(addWordButton, SIGNAL(clicked()), this, SLOT(createAddWordsDialog()));
    connect(testWordButton, SIGNAL(clicked()), this, SLOT(createTestWordsDialog()));
    connect(importWordButton, SIGNAL(clicked()),this, SLOT(importWordsDialog()));
    connect(editWordButton, SIGNAL(clicked()), this, SLOT(createEditWordsDialog()));

    connect(addSentencesButton, SIGNAL(clicked()), this, SLOT(createAddSentencesDialog()));
    connect(testSentencesButton, SIGNAL(clicked()), this, SLOT(createTestSentencesDialog()));
    connect(importSentencesButton, SIGNAL(clicked()), this, SLOT(importSentencesDialog()));
    connect(editSentencesButton, SIGNAL(clicked()), this, SLOT(createEditSentencesDialog()));
}

void MainWindow::readFile(const QString &fileName, QVector<QString> &vector)
{
    QFile myFile(fileName);
    if(!myFile.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream stream(&myFile);
    QString tempString = stream.readLine();
    while(!stream.atEnd())
    {
        tempString = stream.readLine();
        vector.push_back(tempString);
        stream.flush();
    }
    myFile.close();
}

void MainWindow::writeToFile(const QString &fileName, const QVector<QString> &dictionary)
{
    QFile myFile(fileName);
    if(!myFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(0,tr("Сообщение"),tr("Ошибка записи в файл"));
        return;
    }
    QTextStream stream(&myFile);
    for(int i = 0; i < dictionary.size(); i++)
    {
        stream << "\n" << dictionary.at(i);
    }
    myFile.close();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    writeToFile("newRussianWords.txt", newRussianWords);
    writeToFile("newEnglishWords.txt", newEnglishWords);
    writeToFile("russianDictionary.txt", russianDictionary);
    writeToFile("englishDictionary.txt", englishDictionary);

    writeToFile("newEnglishSentences.txt", newEnglishSentences);
    writeToFile("newRussianSentences.txt", newRussianSentences);
    writeToFile("russianSentences.txt", russianSentences);
    writeToFile("englishSentences.txt", englishSentences);
}

void MainWindow::createAddWordsDialog()
{
    addDialog = new AddDialog(newEnglishWords, newRussianWords);
    addDialog->show();
    hide();
    if(addDialog->exec() == QDialog::Accepted)
    {
        newRussianWords = addDialog->getRussianDictionary();
        newEnglishWords = addDialog->getEnglishDictionary();
    }
    delete addDialog;
    show();
}

void MainWindow::createTestWordsDialog()
{
    testDialog = new TestDialog(englishDictionary,russianDictionary, newEnglishWords,newRussianWords);
    testDialog->show();
    hide();
    testDialog->exec();
    delete testDialog;
    show();
}

void MainWindow::importWordsDialog()
{
    if(newEnglishWords.isEmpty())
    {
        QMessageBox::information(0,tr("Message"),tr("У Вас нету новых слов которые можно импортировать!"));
        return;
    }
    for(int i = 0; i < newEnglishWords.size(); i++)
    {
        englishDictionary.push_back(newEnglishWords[i]);
        russianDictionary.push_back(newRussianWords[i]);
    }
    newEnglishWords.clear();
    newRussianWords.clear();
    QMessageBox::information(0,tr("Message"),tr("Слова успешно импортированы!"));
}

void MainWindow::createEditWordsDialog()
{
    editDialog = new EditDialog(englishDictionary, russianDictionary);
    editDialog->show();
    hide();
    if(editDialog->exec() == QDialog::Accepted)
    {
        englishDictionary = editDialog->getEnglishDictionary();
        russianDictionary = editDialog->getRussianDictionary();
    }
    delete editDialog;
    show();
}

void MainWindow::createAddSentencesDialog()
{
    addDialog = new AddDialog(newEnglishSentences, newRussianSentences);
    addDialog->show();
    hide();
    if(addDialog->exec() == QDialog::Accepted)
    {
        newEnglishSentences = addDialog->getEnglishDictionary();
        newRussianSentences = addDialog->getRussianDictionary();
    }
    delete addDialog;
    show();
}

void MainWindow::createTestSentencesDialog()
{
    testDialog = new TestDialog(englishSentences, russianSentences, newEnglishSentences, newRussianSentences);
    testDialog->show();
    hide();
    testDialog->exec();
    delete testDialog;
    show();
}

void MainWindow::importSentencesDialog()
{
    if(newEnglishSentences.isEmpty())
    {
        QMessageBox::information(0,tr("Message"),tr("В словаре нету новых предложений. Импорт невозможен."));
        return;
    }
    for(int i = 0; i < newEnglishSentences.size(); i++)
    {
        englishSentences.push_back(newEnglishSentences[i]);
        russianSentences.push_back(newRussianSentences[i]);
    }
    newEnglishSentences.clear();
    newRussianSentences.clear();
    QMessageBox::information(0,tr("Message"),tr("Предложения успешно импортированы."));
}

void MainWindow::createEditSentencesDialog()
{
    editDialog = new EditDialog(englishSentences, russianSentences);
    editDialog->show();
    hide();
    if(editDialog->exec() == QDialog::Accepted)
    {
        englishSentences = editDialog->getEnglishDictionary();
        russianSentences = editDialog->getRussianDictionary();
    }
    delete editDialog;
    show();
}
