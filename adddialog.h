#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QVector>

class QLineEdit;
class QPushButton;

class AddDialog : public QDialog
{
    Q_OBJECT
private:
    QVector<QString> russianDictionary;
    QVector<QString> englishDictionary;
    QLineEdit *russianLine;
    QLineEdit *englishLine;
    QPushButton *addButton;
    bool flag;
public:
    AddDialog(const QVector<QString> &englishWords, const QVector<QString> &russianWords, QWidget *parent = 0);
    QVector<QString> getRussianDictionary()const;
    QVector<QString> getEnglishDictionary()const;
protected:
    virtual void closeEvent(QCloseEvent *);
public slots:
    void addWords();
};

#endif // ADDDIALOG_H
