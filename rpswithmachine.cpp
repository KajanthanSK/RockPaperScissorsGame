#include "rpswithmachine.h"
#include "ui_rpswithmachine.h"
#include "RPSMainWindow.h"

RPSWithMachine::RPSWithMachine(int noOfPlays,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RPSWithMachine), noOfPlays(noOfPlays)
{
    ui->setupUi(this);

    ui->textEditPlayerScore->setText(QString::number(playerScore));
    ui->textEditMachineScore->setText(QString::number(machineScore));
    ui->textEditNoOfPlays->setText(QString::number(round));

    QObject::connect(ui->buttonRock, SIGNAL(clicked()), this, SLOT(onButtonRockClicked()));
    QObject::connect(ui->buttonPaper, SIGNAL(clicked()), this, SLOT(onButtonPaperClicked()));
    QObject::connect(ui->buttonScissor, SIGNAL(clicked()), this, SLOT(onButtonScissorClicked()));
    QObject::connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(onButtonQuitClicked()));
}

RPSWithMachine::~RPSWithMachine()
{
    delete ui;
}

int RPSWithMachine::machineChoiceGenerator()
{
    int computerChoice = (rand() % (3-1+1))+1;
    return computerChoice;
}

void RPSWithMachine::onButtonRockClicked()
{
    round++;
    machineChoice=machineChoiceGenerator();
    ui->labelPlayerOutput->setStyleSheet(imageRock);

    if(machineChoice==1)
    {
        ui->labelMachineOutput->setStyleSheet(imageRock);
        ui->labelResult->setText(drawMessage);
    }
    if(machineChoice==2)
    {
        ui->labelMachineOutput->setStyleSheet(imagePaper);
        machineScore++;
        ui->textEditMachineScore->setText(QString::number(machineScore));
        ui->labelResult->setText(loseMessage);
    }
    if(machineChoice==3)
    {
        ui->labelMachineOutput->setStyleSheet(imageScissor);
        playerScore++;
        ui->textEditPlayerScore->setText(QString::number(playerScore));
        ui->labelResult->setText(winMessage);
    }
    setPropertiesOfUi();
}

void RPSWithMachine::onButtonPaperClicked()
{
    round++;
    machineChoice=machineChoiceGenerator();
    ui->labelPlayerOutput->setStyleSheet(imagePaper);

    if(machineChoice==1)
    {
        ui->labelMachineOutput->setStyleSheet(imageRock);
        playerScore++;
        ui->textEditPlayerScore->setText(QString::number(playerScore));
        ui->labelResult->setText(winMessage);
    }
    if(machineChoice==2)
    {
        ui->labelMachineOutput->setStyleSheet(imagePaper);
        ui->labelResult->setText(drawMessage);
    }
    if(machineChoice==3)
    {
        ui->labelMachineOutput->setStyleSheet(imageScissor);
        machineScore++;
        ui->textEditMachineScore->setText(QString::number(machineScore));
        ui->labelResult->setText(loseMessage);
    }
    setPropertiesOfUi();
}

void RPSWithMachine::onButtonScissorClicked()
{
    round++;
    machineChoice=machineChoiceGenerator();
    ui->labelPlayerOutput->setStyleSheet(imageScissor);

    if(machineChoice==1)
    {
        ui->labelMachineOutput->setStyleSheet(imageRock);
        machineScore++;
        ui->textEditMachineScore->setText(QString::number(machineScore));
        ui->labelResult->setText(loseMessage);
    }
    if(machineChoice==2)
    {
        ui->labelMachineOutput->setStyleSheet(imagePaper);
        playerScore++;
        ui->textEditPlayerScore->setText(QString::number(playerScore));
        ui->labelResult->setText(winMessage);
    }
    if(machineChoice==3)
    {
        ui->labelMachineOutput->setStyleSheet(imageScissor);
        ui->labelResult->setText(drawMessage);
    }
    setPropertiesOfUi();
}

void RPSWithMachine::setPropertiesOfUi()
{
    // Disable buttons
    ui->groupBoxButton->setEnabled(false);

    // Enable buttons after 2 seconds
    QTimer::singleShot(5000, [=]()
    {
        ui->groupBoxButton->setEnabled(true);
        ui->labelPlayerOutput->setStyleSheet(imageEmpty);
        ui->labelMachineOutput->setStyleSheet(imageEmpty);
        if(round!=noOfPlays+1)
        {
            ui->labelResult->setText("Now You Can Select!");
            ui->textEditNoOfPlays->setText(QString::number(round));
        }
        else
        {
            {
            ui->textEditNoOfPlays->setText("0");
            ui->groupBoxButton->setEnabled(false);
            ui->labelResult->setText("Game Over!");
            }

            if (playerScore > machineScore)
                QMessageBox::information(nullptr, "Congratulations!", "Player wins the match!\nPlayer Score: " + QString::number(playerScore) + "\nMachine's Score: " + QString::number(machineScore));
            else if (playerScore < machineScore)
                QMessageBox::information(nullptr, "Result", "Machine wins the match!\nPlayer Score: " + QString::number(playerScore) + "\nMachine's Score: " + QString::number(machineScore));
            else
                QMessageBox::information(nullptr, "Result", "The match ends in a tie!\nPlayer Score: " + QString::number(playerScore) + "\nMachine's Score: " + QString::number(machineScore));
        }

    });
}

void RPSWithMachine::onButtonQuitClicked()
{
    this->close();
}




