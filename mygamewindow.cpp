#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "cardbutton.h"
#include "mygrid.h"
#include <iostream>
#include <QPushButton>
#include <QProcess>
#include <QTimer>

class MyGameWindow : public QWidget {
public:
    MyGameWindow(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *vb = new QVBoxLayout(this); // timer, grid and spaceritem
        QPushButton *new_game_button = new QPushButton("New Game");
        this->gl = new MyGrid();
        this->score = 0;
        this->try_count = 5;
        score_label = new QLabel("Score : 0");
        this->try_count_label = new QLabel("Try count: 5");

        std::vector<std::string> words = {
            "Lion",
            "Elephant",
            "Tiger",
            "Giraffe",
            "Monkey",
            "Dolphin",
            "Penguin",
            "Koala",
            "Kangaroo",
            "Crocodile",
            "Polar",
            "Cheetah",
            "Owl",
            "Seahorse",
            "Eagle"
        };
        int total_word_count = 15;
        for(int i = 0; i < total_word_count; i++) {
            words.push_back(words[i]);
        }
        std::srand(std::time(nullptr));
        for(int row=0; row<5; row++){
            for(int col=0; col<6; col++){
                int word_index = std::rand() % words.size();
                QString card_word = QString::fromStdString(words.at(word_index));
                CardButton *randButton = new CardButton(card_word);
                words.erase(words.begin() + word_index);

                QObject::connect(randButton, SIGNAL(clicked()), randButton, SLOT(flip_card()));
                QObject::connect(randButton, &QPushButton::clicked, [this, randButton]() {
                    this->check_card_match(randButton);
                });

                gl->addWidget(randButton, row, col, 1, 1);
            }
        }

        vb->addWidget(new_game_button);

        vb->addWidget(this->score_label);
        vb->addWidget(this->try_count_label);
        vb->addLayout(gl);

        QObject::connect(new_game_button, &QPushButton::clicked, [this]() {
            this->restartGame();
        });

        QSpacerItem *si = new QSpacerItem(0, 30, QSizePolicy::Expanding, QSizePolicy::Expanding);
        vb->addSpacerItem(si);

        setWindowTitle("Color Game");
        resize(640, 480);
    }

    void restartGame() {
        QProcess::startDetached(QApplication::arguments()[0], QApplication::arguments());
        qApp->quit();
    }

    void score_changed(){
        this->score += 1;
        this->score_label->setText("Score : " + QString::number(this->score));

        QMessageBox msgBox;

        if(this->score == 15) {
            msgBox.setText("You Won!");
            msgBox.setStandardButtons(QMessageBox::Close);
            if(msgBox.exec()==QMessageBox::Close){
                this->restartGame();
            }
        }
    }

    void try_count_changed() {
        this->try_count -= 1;
        this->try_count_label->setText("Remaining tries: " + QString::number(this->try_count));

        QMessageBox msgBox;

        if(this->try_count == 0) {
            msgBox.setWindowTitle("Warning");
            msgBox.setText("Game Over");
            msgBox.addButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::No){
                this->restartGame();
            }
        }
    }

    void check_card_match(CardButton *randomButton){
        CardButton* selectedCard = randomButton;
        if(gl->current_flipped_card != nullptr && gl->current_flipped_card->cardId == randomButton->cardId) {
            gl->current_flipped_card->flip_card();
            return;
        }

        if(gl->current_flipped_card == nullptr) {
            gl->current_flipped_card = selectedCard;
        } else{
            if (gl->current_flipped_card->text() == selectedCard->text()) {
                gl->current_flipped_card->setEnabled(false);
                selectedCard->setEnabled(false);
                this->score_changed();
            } else{
                QTimer::singleShot(500, gl->current_flipped_card, &CardButton::flip_card);
                QTimer::singleShot(500, selectedCard, &CardButton::flip_card);
            }
            gl->current_flipped_card = nullptr;
            this->try_count_changed();
        }
    }


private:
    int score;
    int try_count;
    MyGrid *gl;
    QLabel *score_label;
    QLabel *try_count_label;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyGameWindow gameWindow;
    gameWindow.show();
    return app.exec();
}
