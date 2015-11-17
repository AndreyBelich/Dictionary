#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QVector>

class QLineEdit;
class QPushButton;

class EditDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *findLine;
    QLineEdit *englishLine;
    QLineEdit *russianLine;
    QPushButton *findButton;
    QPushButton *replaceButton;
    QVector<QString> englishDictionary;
    QVector<QString> russianDictionary;
    int findIndex;
    bool replaceFlag;
public:
    EditDialog(const QVector<QString> &english, const QVector<QString> &russian,QWidget *parent = 0);
    QVector<QString> getEnglishDictionary()const;
    QVector<QString> getRussianDictionary()const;
protected:
    virtual void closeEvent(QCloseEvent *);
private slots:
    void findSlot();
    void replaceSlot();
};

#endif // EDITDIALOG_H
