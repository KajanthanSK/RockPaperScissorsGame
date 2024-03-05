#include "RPSPlayer2Window.h"
#include "ui_RPSPlayer2Window.h"

RPSPlayer2Window::RPSPlayer2Window(int noOfPlays,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RPSPlayer2Window), noOfPlays(noOfPlays)
{
    ui->setupUi(this);
    setPlayer2Controller();

    ui->labelScoreYou->setText(QString::number(yourScore));
    ui->labelScoreFriend->setText(QString::number(friendScore));

    QObject::connect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(onButtonConnectClicked()));
    QObject::connect(ui->buttonRock, SIGNAL(clicked()), this, SLOT(onButtonRockClicked()));
    QObject::connect(ui->buttonPaper, SIGNAL(clicked()), this, SLOT(onButtonPaperClicked()));
    QObject::connect(ui->buttonScissor, SIGNAL(clicked()), this, SLOT(onButtonScissorClicked()));
    QObject::connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(onButtonQuitClicked()));

}

RPSPlayer2Window::~RPSPlayer2Window()
{
    delete ui;
}

void RPSPlayer2Window::setPlayer2Controller()
{
    connect(&player2Controller, &Player2Controller::connected, this, &RPSPlayer2Window::deviceConnect);
    connect(&player2Controller, &Player2Controller::dataReady, this, &RPSPlayer2Window::receiveMessage);
    connect(&player2Controller, &Player2Controller::disconnected, this, &RPSPlayer2Window::deviceDisconnected);
}

void RPSPlayer2Window::receiveMessage(QString message)
{
    player1SelectedItem=message;
    player1=true;
    if(clickedMessage.compare("Rock", Qt::CaseInsensitive) == 0)
        rockButtonClickUpdates(button,player1);
    if(clickedMessage.compare("Paper", Qt::CaseInsensitive) == 0)
        paperButtonClickUpdates(button,player1);
    if(clickedMessage.compare("Scissor", Qt::CaseInsensitive) == 0)
        scissorButtonClickUpdates(button,player1);
}

void RPSPlayer2Window::deviceConnect()
{
    ui->labelMessage->setText("You can play now.");
    ui->labelRound->setText(QString::number(round));
    ui->buttonConnect->setText("Disconnect");
    ui->buttonConnect->setEnabled(true);
}

void RPSPlayer2Window::deviceDisconnected()
{
    ui->labelMessage->setText("You left the game!!");
    ui->buttonConnect->setText("Connect");
    ui->buttonConnect->setEnabled(false);
    ui->groupBoxButton->setEnabled(false);
}

void RPSPlayer2Window::onButtonConnectClicked()
{
    if (player2Controller.isConnected())
    {
        player2Controller.disconnect();
    }
    else
    {
        auto ip = ui->textEditIPAddress->toPlainText();
        auto port = ui->spinBoxPort->value();
        player2Controller.connectToDevice(ip, port);
    }
}


void RPSPlayer2Window::onButtonRockClicked()
{
    ui->labelMessage->setText("You chose rock.");
    clickedMessage="Rock";
    player2Controller.send(clickedMessage);
    ui->labelYourOutput->setStyleSheet(imageRock);
    button=true;
    rockButtonClickUpdates(button,player1);
}


void RPSPlayer2Window::onButtonPaperClicked()
{
    ui->labelMessage->setText("You chose paper.");
    clickedMessage="Paper";
    player2Controller.send(clickedMessage);
    ui->labelYourOutput->setStyleSheet(imagePaper);
    button=true;
    paperButtonClickUpdates(button,player1);
}


void RPSPlayer2Window::onButtonScissorClicked()
{
    ui->labelMessage->setText("You chose scissor.");
    clickedMessage="Scissor";
    player2Controller.send(clickedMessage);
    ui->labelYourOutput->setStyleSheet(imageScissor);
    button=true;
    scissorButtonClickUpdates(button,player1);
}

void RPSPlayer2Window::rockButtonClickUpdates(bool buttonClick,bool player1Click)
{
    if(buttonClick && player1Click)
    {
        if(player1SelectedItem.compare("Rock", Qt::CaseInsensitive) == 0)
        {
            ui->labelFriendOutput->setStyleSheet(imageRock);
            ui->labelMessage->setText(drawMessage);
        }
        if(player1SelectedItem.compare("Paper", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imagePaper);
            ui->labelMessage->setText(loseMessage);
            friendScore++;
            ui->labelScoreFriend->setText(QString::number(friendScore));
        }
        if(player1SelectedItem.compare("Scissor", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imageScissor);
            ui->labelMessage->setText(winMessage);
            yourScore++;
            ui->labelScoreYou->setText(QString::number(yourScore));
        }
        changeButtonStates();
        button=false;
        player1=false;
    }
}

void RPSPlayer2Window::paperButtonClickUpdates(bool buttonClick,bool player1Click)
{
    if(buttonClick && player1Click)
    {
        if(player1SelectedItem.compare("Rock", Qt::CaseInsensitive) == 0)
        {
            ui->labelFriendOutput->setStyleSheet(imageRock);
            ui->labelMessage->setText(winMessage);
            yourScore++;
            ui->labelScoreYou->setText(QString::number(yourScore));
        }
        if(player1SelectedItem.compare("Paper", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imagePaper);
            ui->labelMessage->setText(drawMessage);
        }
        if(player1SelectedItem.compare("Scissor", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imageScissor);
            ui->labelMessage->setText(loseMessage);
            friendScore++;
            ui->labelScoreFriend->setText(QString::number(friendScore));
        }
        changeButtonStates();
        button=false;
        player1=false;
    }
}

void RPSPlayer2Window::scissorButtonClickUpdates(bool buttonClick,bool player1Click)
{
    if(buttonClick && player1Click)
    {
        if(player1SelectedItem.compare("Rock", Qt::CaseInsensitive) == 0)
        {
            ui->labelFriendOutput->setStyleSheet(imageRock);
            ui->labelMessage->setText(loseMessage);
            friendScore++;
            ui->labelScoreFriend->setText(QString::number(friendScore));
        }
        if(player1SelectedItem.compare("Paper", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imagePaper);
            ui->labelMessage->setText(winMessage);
            yourScore++;
            ui->labelScoreYou->setText(QString::number(yourScore));
        }
        if(player1SelectedItem.compare("Scissor", Qt::CaseInsensitive)==0)
        {
            ui->labelFriendOutput->setStyleSheet(imageScissor);
            ui->labelMessage->setText(drawMessage);
        }
        changeButtonStates();
        button=false;
        player1=false;
    }
}

void RPSPlayer2Window::changeButtonStates()
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
               QMessageBox::information(nullptr, "Player:02", "You win the match!\nYour Score: " + QString::number(yourScore) + "\nFriend's Score: " + QString::number(friendScore));
           else if (yourScore < friendScore)
               QMessageBox::information(nullptr, "Player:02", "Your Friend wins the match!\nYour Score: " + QString::number(yourScore) + "\nFriend's Score: " + QString::number(friendScore));
           else
               QMessageBox::information(nullptr, "Player:02", "The match ends in a tie!\nYour Score: " + QString::number(yourScore) + "\nFriend's Score: " + QString::number(friendScore));

       }

   });
}

void RPSPlayer2Window::onButtonQuitClicked()
{
    this->close();
}

