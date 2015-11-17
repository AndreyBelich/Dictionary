#include <QtWidgets>
#include <cstdlib>
#include <ctime>
#include "testdialog.h"

TestDialog::TestDialog(const QVector<QString> &engWords, const QVector<QString> &rusWords,
                       const QVector<QString> &newEngWords, const QVector<QString> &newRusWords, QWidget *parent)
    :QDialog(parent),currentIndex(0),questVector(0)
{
    srand((size_t)time(NULL));
    englishWords = engWords;
    russianWords = rusWords;
    newEnglishWords = newEngWords;
    newRussianWords = newRusWords;

    oldEnglishWordsButton = new QRadioButton(tr("Тренировка английских слов"));
    oldRussianWordsButton = new QRadioButton(tr("Тренировка русских слов"));
    newEnglishWordsButton = new QRadioButton(tr("Тренировка новых английских слов"));
    newRussianWordsButton = new QRadioButton(tr("Тренировка новых русских слов"));

    oldEnglishWordsButton->setChecked(true);

    choiceButton = new QPushButton(tr("Выбор..."));

    choiceBox = new QGroupBox(tr("Выберите режим тренировки"));

    QGridLayout *choiceLayout = new QGridLayout;
    choiceLayout->addWidget(oldEnglishWordsButton,0,0);
    choiceLayout->addWidget(oldRussianWordsButton,0,1);
    choiceLayout->addWidget(newEnglishWordsButton,1,0);
    choiceLayout->addWidget(newRussianWordsButton,1,1);
    choiceLayout->addWidget(choiceButton,2,1);

    choiceBox->setLayout(choiceLayout);

    QLabel *quest = new QLabel(tr("Задание"));
    QLabel *answer = new QLabel(tr("Ответ"));
    QLabel *result = new QLabel(tr("Результат"));

    questionLine = new QLineEdit;
    questionLine->setReadOnly(true);

    answerLine = new QLineEdit;

    resultLine = new QLineEdit;
    resultLine->setReadOnly(true);

    answerButton = new QPushButton(tr("Ответить"));
    answerButton->setDefault(true);
    nextButton = new QPushButton(tr("Следующий вопрос"));
    endTest = new QPushButton(tr("Завершить тест"));

    QGridLayout *testLayout = new QGridLayout;
    testLayout->addWidget(quest,0,0);
    testLayout->addWidget(questionLine,0,1);
    testLayout->addWidget(answer,1,0);
    testLayout->addWidget(answerLine,1,1);
    testLayout->addWidget(result,2,0);
    testLayout->addWidget(resultLine,2,1);
    testLayout->addWidget(answerButton,3,0);
    testLayout->addWidget(nextButton,3,1);

    testLayout->addWidget(endTest,4,0,1,2);

    testBox = new QGroupBox(tr("Тест"));
    testBox->setLayout(testLayout);
    testBox->setEnabled(false);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(choiceBox);
    mainLayout->addWidget(testBox);

    setLayout(mainLayout);
    testBox->setVisible(false);

    connect(choiceButton, SIGNAL(clicked()),this,SLOT(startTest()));
    connect(endTest,SIGNAL(clicked()),this,SLOT(finishTest()));
    connect(choiceButton, SIGNAL(clicked()),this,SLOT(userChoice()));
    connect(answerButton,SIGNAL(clicked()),this,SLOT(compareAnswer()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(nextQuestion()));
}

void TestDialog::startTest()
{
    choiceBox->setEnabled(false);
    choiceBox->setVisible(false);
    testBox->setEnabled(true);
    testBox->setVisible(true);
    resize(250,125);
}

void TestDialog::finishTest()
{
    choiceBox->setEnabled(true);
    choiceBox->setVisible(true);
    testBox->setEnabled(false);
    testBox->setVisible(false);
    answerLine->clear();
    questionLine->clear();
    resultLine->clear();
    resize(250,125);
}

void TestDialog::userChoice()
{
    if(oldEnglishWordsButton->isChecked())
    {
        if(englishWords.isEmpty())
        {
            QMessageBox::information(0,tr("Message"),tr("Вектор пуст"));
            finishTest();
        }
        else
        {
            currentIndex = rand() % englishWords.size();
            questionLine->setText(englishWords[currentIndex]);
            questVector = FIRST;
        }
    }
    else if(oldRussianWordsButton->isChecked())
    {
        if(russianWords.isEmpty())
        {
            QMessageBox::information(0,tr("Message"),tr("Вектор пуст"));
            finishTest();
        }
        else
        {
            currentIndex = rand() % russianWords.size();
            questionLine->setText(russianWords[currentIndex]);
            questVector = SECOND;
        }
    }
    else if(newEnglishWordsButton->isChecked())
    {
        if(newEnglishWords.isEmpty())
        {
            QMessageBox::information(0,tr("Message"),tr("Вектор пуст"));
            finishTest();
        }
        else
        {
            currentIndex = rand() % newEnglishWords.size();
            questionLine->setText(newEnglishWords[currentIndex]);
            questVector = THIRD;
        }
    }
    else if(newRussianWordsButton->isChecked())
    {
        if(newRussianWords.isEmpty())
        {
            QMessageBox::information(0,tr("Message"),tr("Вектор пуст"));
            finishTest();
        }
        else
        {
            currentIndex = rand() % newRussianWords.size();
            questionLine->setText(newRussianWords[currentIndex]);
            questVector = FOURTH;
        }
    }
}

void TestDialog::compareAnswer()
{
    if(questVector == FIRST)
    {
        if(answerLine->text() == russianWords[currentIndex])
        {
            resultLine->setText(tr("Правильно!"));
        }
        else
        {
            resultLine->setText(russianWords[currentIndex]);
        }
    }
    else if(questVector == SECOND)
    {
        if(answerLine->text() == englishWords[currentIndex])
        {
            resultLine->setText(tr("Правильно!"));
        }
        else
        {
            resultLine->setText(englishWords[currentIndex]);
        }
    }
    else if(questVector == THIRD)
    {
        if(answerLine->text() == newRussianWords[currentIndex])
        {
            resultLine->setText(tr("Правильно!"));
        }
        else
        {
            resultLine->setText(newRussianWords[currentIndex]);
        }
    }
    else if(questVector == FOURTH)
    {
        if(answerLine->text() == newEnglishWords[currentIndex])
        {
            resultLine->setText(tr("Правильно!"));
        }
        else
        {
            resultLine->setText(newEnglishWords[currentIndex]);
        }
    }
}

void TestDialog::nextQuestion()
{
    answerLine->clear();
    questionLine->clear();
    resultLine->clear();
    if(questVector == FIRST)
    {
        currentIndex = rand() % englishWords.size();
        questionLine->setText(englishWords[currentIndex]);
    }
    else if(questVector == SECOND)
    {
        currentIndex = rand() % russianWords.size();
        questionLine->setText(russianWords[currentIndex]);
    }
    else if(questVector == THIRD)
    {
        currentIndex = rand() % newEnglishWords.size();
        questionLine->setText(newEnglishWords[currentIndex]);
    }
    else if(questVector == FOURTH)
    {
        currentIndex = rand() % newRussianWords.size();
        questionLine->setText(newRussianWords[currentIndex]);
    }
}
