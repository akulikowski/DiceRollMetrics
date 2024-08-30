#ifndef DICEROLLMETRICS_H
#define DICEROLLMETRICS_H

#include <QMainWindow>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class DiceRollMetrics; }
QT_END_NAMESPACE

class DiceRollMetrics : public QMainWindow
{
    Q_OBJECT

public:
    DiceRollMetrics(QWidget *parent = nullptr);
    ~DiceRollMetrics();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_100_clicked();

    void on_pushButton_1k_clicked();

    void on_pushButton_100k_clicked();

    void on_pushButton_1m_clicked();

    void on_pushButton_2m_clicked();

    void on_pushButton_reset_clicked();

private:
    Ui::DiceRollMetrics *ui;
    int counts[6];
    int totalRolls;
    void rollDice(int rolls);
    void updateStatistics();
    void updateDiceImage(int roll);

};
#endif // DICEROLLMETRICS_H
