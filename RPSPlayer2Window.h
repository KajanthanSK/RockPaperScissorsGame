#ifndef RPSPLAYER2WINDOW_H
#define RPSPLAYER2WINDOW_H

#include "Player2Controller.h"

//QT
#include <QWidget>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class RPSPlayer2Window;
}

class RPSPlayer2Window : public QWidget
{
    Q_OBJECT

public:
    explicit RPSPlayer2Window(int noOfPlays,QWidget *parent = nullptr);
    ~RPSPlayer2Window();
    void setPlayer2Controller();

    QString player1SelectedItem;
    void rockButtonClickUpdates(bool button,bool player2);
    void paperButtonClickUpdates(bool button,bool player2);
    void scissorButtonClickUpdates(bool button,bool player2);
    void changeButtonStates();

private:
    Ui::RPSPlayer2Window *ui;
    Player2Controller player2Controller;
    QString clickedMessage;
    bool button=false;
    bool player1=false;
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



private slots:
    void receiveMessage(QString message);
    void deviceConnect();
    void deviceDisconnected();
    void onButtonConnectClicked();
    void onButtonRockClicked();
    void onButtonPaperClicked();
    void onButtonScissorClicked();
    void onButtonQuitClicked();
};

#endif // RPSPLAYER2WINDOW_H
