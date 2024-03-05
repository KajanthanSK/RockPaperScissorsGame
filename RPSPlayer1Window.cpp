#include "RPSPlayer1Window.h"
#include "ui_RPSPlayer1Window.h"



RPSPlayer1Window::RPSPlayer1Window(int noOfPlays,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RPSPlayer1Window), noOfPlays(noOfPlays)
{
    ui->setupUi(this);
    player1Controller=nullptr;

    ui->labelScoreYou->setText(QString::number(yourScore));
    ui->labelScoreFriend->setText(QString::number(friendScore));

    QObject::connect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(onButtonConnectClicked()));
    QObject::connect(ui->buttonRock, SIGNAL(clicked()), this, SLOT(onButtonRockClicked()));
    QObject::connect(ui->buttonPaper, SIGNAL(clicked()), this, SLOT(onButtonPaperClicked()));
    QObject::connect(ui->buttonScissor, SIGNAL(clicked()), this, SLOT(onButtonScissorClicked()));
    QObject::connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(onButtonQuitClicked()));


}

RPSPlayer1Window::~RPSPlayer1Window()
{
    delete ui;
}

void RPSPlayer1Window::onButtonConnectClicked()
{
    if (player1Controller == nullptr)
    {
        auto port =ui->spinBoxPort->value();
        player1Controller = new Player1Controller(port);
        ui->labelMessage->setText("You are connected! \n Wait for your friend connections.");
        connect(player1Controller, &Player1Controller::newClientConnected, this, &RPSPlayer1Window::newClinetConnected);
        connect(player1Controller, &Player1Controller::dataReceived, this, &RPSPlayer1Window::clientDataReceived);
        connect(player1Controller, &Player1Controller::clientDisconnect, this, &RPSPlayer1Window::clientDisconnected);
    }
}

void RPSPlayer1Window::newClinetConnected()
{
    ui->labelMessage->setText("You can play now.");
    ui->labelRound->setText(QString::number(round));
}

void RPSPlayer1Window::clientDisconnected()
{
    ui->labelMessage->setText("Your Friend left the game!!");
    ui->groupBoxButton->setEnabled(false);
}

void RPSPlayer1Window::clientDataReceived(QString message)
{
    player2Selected=message;
    player2=true;
    if(clickedMessage.compare("Rock", Qt::CaseInsensitive) == 0)
        rockButtonClickUpdates(button,player2);
    if(clickedMessage.compare("Paper", Qt::CaseInsensitive) == 0)
        paperButtonClickUpdates(button,player2);
    if(clickedMessage.compare("Scissor", Qt::CaseInsensitive) == 0)
        scissorButtonClickUpdates(button,player2);
}

void RPSPlayer1Window::onButtonRockClicked()
{
    ui->labelMessage->setText("You chose rock.");
    ui->labelYourOutput->setStyleSheet(imageRock);
    clickedMessage="Rock";
    player1Controller->sendToAll(clickedMessage);
    button=true;
    rockButtonClickUpdates(button,player2);
}

void RPSPlayer1Window::onButtonPaperClicked()
{
    ui->labelMessage->setText("You chose paper.");
    ui->labelYourOutput->setStyleSheet(imagePaper);
    clickedMessage="Paper";
    player1Controller->sendToAll(clickedMessage);
    button=true;
    paperButtonClickUpdates(button,player2);
}

void RPSPlayer1Window::onButtonScissorClicked()
{
    ui->labelMessage->setText("You chose scissor.");
    ui->labelYourOutput->setStyleSheet(imageScissor);
    clickedMessage="Scissor";
    player1Controller->sendToAll(clickedMessage);
    button=true;
    scissorButtonClickUpdates(button,player2);
}

void RPSPlayer1Window::rockButtonClickUpdates(bool buttonClick,bool player2Click)
{
    if(buttonClick && player2Click)
    {
        if(player2Selected.compare("Rock", Qt::CaseInsensitive) == 0)
        {
            ui->labelFriendOutput->setStyleSheet(imageRock);
            ui->labelMessage->setText(drawMessage);
        }
        if(player2Selected.compare("Paper", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imagePaper);
            ui->labelMessage->setText(loseMessage);
            friendScore++;
            ui->labelScoreFriend->setText(QString::number(friendScore));
        }
        if(player2Selected.compare("Scissor", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imageScissor);
            ui->labelMessage->setText(winMessage);
            yourScore++;
            ui->labelScoreYou->setText(QString::number(yourScore));
        }
        changeButtonStates();
        button=false;
        player2=false;
    }
}

void RPSPlayer1Window::paperButtonClickUpdates(bool buttonClick,bool player2Click)
{
    if(buttonClick && player2Click)
    {
        if(player2Selected.compare("Rock", Qt::CaseInsensitive) == 0)
        {
            ui->labelFriendOutput->setStyleSheet(imageRock);
            ui->labelMessage->setText(winMessage);
            yourScore++;
            ui->labelScoreYou->setText(QString::number(yourScore));
        }
        if(player2Selected.compare("Paper", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imagePaper);
            ui->labelMessage->setText(drawMessage);
        }
        if(player2Selected.compare("Scissor", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imageScissor);
            ui->labelMessage->setText(loseMessage);
            friendScore++;
            ui->labelScoreFriend->setText(QString::number(friendScore));
        }
        changeButtonStates();
        button=false;
        player2=false;
    }
}

void RPSPlayer1Window::scissorButtonClickUpdates(bool buttonClick,bool player2Click)
{
    if(buttonClick && player2Click)
    {
        if(player2Selected.compare("Rock", Qt::CaseInsensitive) == 0)
        {
            ui->labelFriendOutput->setStyleSheet(imageRock);
            ui->labelMessage->setText(loseMessage);
            friendScore++;
            ui->labelScoreFriend->setText(QString::number(friendScore));
        }
        if(player2Selected.compare("Paper", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imagePaper);
            ui->labelMessage->setText(winMessage);
            yourScore++;
            ui->labelScoreYou->setText(QString::number(yourScore));
        }
        if(player2Selected.compare("Scissor", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imageScissor);
            ui->labelMessage->setText(drawMessage);
        }
        changeButtonStates();
        button=false;
        player2=false;
    }
}

void RPSPlayer1Window::changeButtonStates()
{
    round++;
    ui->groupBoxButton->setEnabled(false);

    // Enable buttons after 5 seconds
    QTimer::singleShot(5000, [=]()
   {
       ui->groupBoxButton->setEnabled(true);
       ui->labelMessage->setText("Now You Can Select!");
       ui->labelYourOutput->setStyleSheet(imageEmpty);
       ui->labelFriendOutput->setStyleSheet(imageEmpty);

       if(round!=noOfPlays+1)
       {
           ui->labelMessage->setText("Now You Can Select!");
           ui->labelRound->setText(QString::number(round));
       }
       else
       {
           {
               ui->labelRound->setText("0");
               ui->groupBoxButton->setEnabled(false);
               ui->labelMessage->setText("Game Over!");
           }

           if (yourScore > friendScore)
               QMessageBox::information(nullptr, "Player:01", "You win the match!\nYour Score: " + QString::number(yourScore) + "\nFriend's Score: " + QString::number(friendScore));
           else if (yourScore < friendScore)
               QMessageBox::information(nullptr, "Player:01", "Your Friend wins the match!\nYour Score: " + QString::number(yourScore) + "\nFriend's Score: " + QString::number(friendScore));
           else
               QMessageBox::information(nullptr, "Player:01", "The match ends in a tie!\nYour Score: " + QString::number(yourScore) + "\nFriend's Score: " + QString::number(friendScore));

       }

   });
}

void RPSPlayer1Window::onButtonQuitClicked()
{
    this->close();
}

