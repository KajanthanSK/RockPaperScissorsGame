#include "RPSMainWindow.h"
#include "ui_RPSMainWindow.h"

#include "rpswithmachine.h"
#include "RPSPlayer1Window.h"
#include "RPSPlayer2Window.h"
#include <QMessageBox>
#include<QLineEdit>
#include<QInputDialog>
#include<QApplication>
#include<QVBoxLayout>

RPSMainWindow::RPSMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RPSMainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->buttonMachie, SIGNAL(clicked()), this, SLOT(onButtonMachineClicked()));
    QObject::connect(ui->buttonFriend, SIGNAL(clicked()), this, SLOT(onButtonFriendClicked()));


}

RPSMainWindow::~RPSMainWindow()
{
    delete ui;
}

void RPSMainWindow::onButtonMachineClicked()
{
    QString text;
    bool ok = false;

    while (!ok || text.isEmpty())
    {
        text = QInputDialog::getText(nullptr, "Input", "Number of plays:", QLineEdit::Normal, "", &ok);

        if (ok && text.isEmpty())
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(nullptr, "Warning", "You must enter a valid input!", QMessageBox::Ok | QMessageBox::Cancel);

            if (reply == QMessageBox::Cancel)
                break;
        }
        else
            break;
    }

    if (ok && !text.isEmpty())
    {
        noOfPlays=text.toInt();
        this->close();
        RPSWithMachine* withMachine = new RPSWithMachine(noOfPlays);
        withMachine->show();
    }
}

void RPSMainWindow::onButtonFriendClicked()
{
    QString text;
    bool ok = false;

    while (!ok || text.isEmpty())
    {
        text = QInputDialog::getText(nullptr, "Input", "Number of plays:", QLineEdit::Normal, "", &ok);

        if (ok && text.isEmpty())
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(nullptr, "Warning", "You must enter a valid input!", QMessageBox::Ok | QMessageBox::Cancel);

            if (reply == QMessageBox::Cancel)
                break;
        }
        else
            break;
    }
    if (ok && !text.isEmpty())
    {
        noOfPlays=text.toInt();
        this->close();
        RPSPlayer1Window* player1Window = new RPSPlayer1Window(noOfPlays);
        player1Window->show();
        RPSPlayer2Window* player2Window = new RPSPlayer2Window(noOfPlays);
        player2Window->show();

    }
}

