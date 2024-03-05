#ifndef RPSWITHMACHINE_H
#define RPSWITHMACHINE_H

//QT
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class RPSWithMachine;
}

class RPSWithMachine : public QWidget
{
    Q_OBJECT

public:
    explicit RPSWithMachine(int noOfPlays,QWidget *parent = nullptr);
    ~RPSWithMachine();

private slots:
    void onButtonRockClicked();
    void onButtonPaperClicked();
    void onButtonScissorClicked();
    void onButtonQuitClicked();


private:
    Ui::RPSWithMachine *ui;
    int playerScore = 0; // Assuming player's score is 0 initially
    int machineScore = 0; // Assuming machine's score is 0 initially
    int machineChoice=0;
    int round=1;
    int noOfPlays;
    QString winMessage = "Congratulations!!, You win this round.\n Wait for next Round";
    QString drawMessage = "The round has resulted in a Draw!! \n Wait for next Round";
    QString loseMessage = "Better luck next time, Computer wins this round. \n Wait for next Round";
    QString imageRock = "border-image: url(:/Image/Rock.gif);";
    QString imagePaper = "border-image: url(:/Image/Paper.gif)";
    QString imageScissor = "border-image: url(:/Image/Scissor.gif);";
    QString imageEmpty = "border-image: url(:/Image/Output.gif);";

    //Methods
    int machineChoiceGenerator();
    void setPropertiesOfUi();
};

#endif // RPSWITHMACHINE_H
