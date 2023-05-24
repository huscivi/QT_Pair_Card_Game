#ifndef MYGRID_H
#define MYGRID_H
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <cardbutton.h>

class MyGrid: public QGridLayout
{
    Q_OBJECT
public:
    MyGrid();
    int tryCount;
    int score;
    QLabel* score_label;
    QLabel* try_count_label;
    QPushButton* new_game_button;
    CardButton* current_flipped_card;
    bool isAnyCardFlipped;
};

#endif // MYGRID_H
