#include "mygrid.h"
#include <iostream>
#include <QTimer>
#include <QMessageBox>

MyGrid::MyGrid(): QGridLayout(){
    this->tryCount = 5;
    try_count_label = new QLabel("Try count: 5");
    new_game_button = new QPushButton("New Game");
    this->current_flipped_card = nullptr;
}


