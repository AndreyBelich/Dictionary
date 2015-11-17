#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class QPushButton;
class AddDialog;
class TestDialog;
class EditDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QPushButton *addWordButton;
    QPushButton *testWordButton;
    QPushButton *importWordButton;
    QPushButton *editWordButton;

    QPushButton *addSentencesButton;
    QPushButton *testSentencesButton;
    QPushButton *editSentencesButton;
    QPushButton *importSentencesButton;

    QVector<QString> newRussianWords;
    QVector<QString> newEnglishWords;
    QVector<QString> russianDictionary;
    QVector<QString> englishDictionary;
    QVector<QString> newEnglishSentences;
    QVector<QString> newRussianSentences;
    QVector<QString> englishSentences;
    QVector<QString> russianSentences;
    AddDialog *addDialog;
    TestDialog *testDialog;
    EditDialog *editDialog;
    void readFile(const QString &fileName, QVector<QString> &dictionary);
    void writeToFile(const QString &fileName, const QVector<QString> &dictionary);
public:
    explicit MainWindow(QWidget *parent = 0);
protected:
    virtual void closeEvent(QCloseEvent *);
public slots:
    void createAddWordsDialog();
    void createTestWordsDialog();
    void importWordsDialog();
    void createEditWordsDialog();

    void createAddSentencesDialog();
    void createTestSentencesDialog();
    void importSentencesDialog();
    void createEditSentencesDialog();
};

#endif // MAINWINDOW_H
