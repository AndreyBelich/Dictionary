#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include <QVector>

class QRadioButton;
class QGroupBox;
class QPushButton;
class QLabel;
class QLineEdit;

class TestDialog : public QDialog
{
    Q_OBJECT
private:
    enum {FIRST = 1, SECOND, THIRD, FOURTH};
    QVector<QString> englishWords;
    QVector<QString> russianWords;
    QVector<QString> newEnglishWords;
    QVector<QString> newRussianWords;
    QRadioButton *oldEnglishWordsButton;
    QRadioButton *oldRussianWordsButton;
    QRadioButton *newEnglishWordsButton;
    QRadioButton *newRussianWordsButton;
    QGroupBox *choiceBox;
    QGroupBox *testBox;
    QPushButton *choiceButton;
    QPushButton *answerButton;
    QPushButton *nextButton;
    QPushButton *endTest;
    QLineEdit *answerLine;
    QLineEdit *questionLine;
    QLineEdit *resultLine;
    int currentIndex;
    int questVector;
public:
    TestDialog(const QVector<QString> &engWords, const QVector<QString> &rusWords,
               const QVector<QString> &newEngWords, const QVector<QString> &newRusWords, QWidget *parent = 0);
private slots:
    void startTest();
    void finishTest();
    void userChoice();
    void compareAnswer();
    void nextQuestion();
};

#endif // TESTDIALOG_H
