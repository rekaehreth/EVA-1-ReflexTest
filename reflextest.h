#ifndef REFLEXTEST_H
#define REFLEXTEST_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class ReflexTest; }
QT_END_NAMESPACE

class ReflexTest : public QMainWindow
{
    Q_OBJECT

public:
    ReflexTest(QWidget *parent = nullptr);
    ~ReflexTest();

private slots:
    void on_colorButton_clicked();
    void on_pauseButton_clicked();
    void on_timer_timeout();
    void on_startNewGameButton_clicked();

private:
    Ui::ReflexTest *ui;
    
    int goodAnswers;
    int badAnswers;
    QVector<QString> availableColors = { "Red", "Green", "Blue", "Yellow" };
    QVector<QPushButton*> playGround;
    QTimer timer;

    QString randomColor();
    void reColorPlayGround();
    void nextTest();
    void startNewGame();

};
#endif // REFLEXTEST_H
