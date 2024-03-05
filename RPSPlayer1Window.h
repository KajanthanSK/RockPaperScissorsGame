#ifndef RPSPLAYER1WINDOW_H
#define RPSPLAYER1WINDOW_H

#include "Player1Controller.h"

//QT
#include <QWidget>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class RPSPlayer1Window;
}

class RPSPlayer1Window : public QWidget
{
    Q_OBJECT

public:
    explicit RPSPlayer1Window(int noOfPlays,QWidget *parent = nullptr);
    ~RPSPlayer1Window();
    QString clickedMessage;
    QString player2Selected;

    void rockButtonClickUpdates(bool button,bool player2);
    void paperButtonClickUpdates(bool button,bool player2);
    void scissorButtonClickUpdates(bool button,bool player2);
    void changeButtonStates();

private slots:
    void onButtonConnectClicked();
    void newClinetConnected();
    void clientDisconnected();
    void clientDataReceived(QString message);
    void onButtonRockClicked();
    void onButtonPaperClicked();
    void onButtonScissorClicked();

    void onButtonQuitClicked();

private:
    Ui::RPSPlayer1Window *ui;
    Player1Controller* player1Controller;
    bool button=false;
    bool player2=false;
    int noOfPlays;
    int round=1;
    int yourScore=0;
    int friendScore=0;

    QString winMessage = "Congratulations!!, You win this round.\n Wait for next Round";
    QString drawMessage = "The round has resulted in a Draw!! \n Wait for next Round";
    QString loseMessage = "Better luck next time, Your Friend wins this round. \n Wait for next Round";
    QString imageRock = "border-image: url(:/Image/Rock.gif);";
    QString imagePaper = "border-image: url(:/Image/Paper.gif)";
    QString imageScissor = "border-image: url(:/Image/Scissor.gif);";
    QString imageEmpty = "border-image: url(:/Image/Output.gif);";
};

#endif // RPSPLAYER1WINDOW_H
