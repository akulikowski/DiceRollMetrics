#include "dicerollmetrics.h"
#include "ui_dicerollmetrics.h"
#include <random>
#include <QPixmap>

DiceRollMetrics::DiceRollMetrics(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DiceRollMetrics)
{
    ui->setupUi(this);

    totalRolls = 0;
    // Reset the counts array to zero before starting a new set of dice rolls
    // Each element in the array represents the count of dice rolls for faces 1 through 6.
    // This ensures that we start with a clean slate for accurate statistical analysis.
    for (int i = 0; i < 6; ++i) {
        counts[i] = 0;
    }
}

DiceRollMetrics::~DiceRollMetrics()
{
    delete ui;
}


void DiceRollMetrics::on_pushButton_1_clicked()
{
    rollDice(1);
}


void DiceRollMetrics::on_pushButton_100_clicked()
{
    rollDice(100);
}


void DiceRollMetrics::on_pushButton_1k_clicked()
{
    rollDice(1000);
}


void DiceRollMetrics::on_pushButton_100k_clicked()
{
    rollDice(100000);
}


void DiceRollMetrics::on_pushButton_1m_clicked()
{
    rollDice(1000000);
}


void DiceRollMetrics::on_pushButton_2m_clicked()
{
    rollDice(2000000);
}

void DiceRollMetrics::rollDice(int rolls)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    for (int i = 0; i < rolls; ++i)
    {
        int roll = dis(gen);
        counts[roll - 1]++;

        // Updating the image on the label
        updateDiceImage(roll);

        // Refresh the user interface after every 100th throw
        if (i % 100 == 0)
        {
            ui->label_diceImage->repaint();
            QApplication::processEvents();
        }
    }
    totalRolls += rolls;

    // Debugging
 //   qDebug() << "Total rolls: " << totalRolls;

    updateStatistics();
}


void DiceRollMetrics::updateStatistics()
{
    QString stats;
    QTextStream stream(&stats);
    stream.setRealNumberPrecision(3);
    stream.setFieldWidth(5);

    for (int i = 0; i < 6; ++i)
    {
        double percentage = (static_cast<double>(counts[i]) / static_cast<double>(totalRolls)) * 100.0;
        stream << i + 1 << "  " << counts[i] << " time(s) " << percentage << " %\n";
    }

    ui->label_result->setText(stats);
}

void DiceRollMetrics::on_pushButton_reset_clicked()
{

    for (int i = 0; i < 6; ++i)
    {
        counts[i] = 0;
    }
    totalRolls = 0;

    updateStatistics();
}

void DiceRollMetrics::updateDiceImage(int roll)
{
    QString imagePath;
    switch (roll)
    {
        case 1:
            imagePath = ":/Dice_images/one.bmp";
            break;
        case 2:
            imagePath = ":/Dice_images/two.bmp";
            break;
        case 3:
            imagePath = ":/Dice_images/three.bmp";
            break;
        case 4:
            imagePath = ":/Dice_images/four.bmp";
            break;
        case 5:
            imagePath = ":/Dice_images/five.bmp";
            break;
        case 6:
            imagePath = ":/Dice_images/six.bmp";
            break;
    }

    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        ui->label_diceImage->setPixmap(pixmap.scaled(77, 77, Qt::KeepAspectRatio));
    } else {
        QString errorMessage = QString("Error loading image from path: %1").arg(imagePath);
        qDebug() << errorMessage;
        ui->label_diceImage->setText(errorMessage);
    }
}
