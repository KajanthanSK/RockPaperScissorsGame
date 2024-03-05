#ifndef RPSMAINWINDOW_H
#define RPSMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class RPSMainWindow;
}
QT_END_NAMESPACE

class RPSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    RPSMainWindow(QWidget *parent = nullptr);
    ~RPSMainWindow();

private slots:
    void onButtonMachineClicked();
    void onButtonFriendClicked();

private:
    Ui::RPSMainWindow *ui;
    int noOfPlays=0;
};
#endif // RPSMAINWINDOW_H
