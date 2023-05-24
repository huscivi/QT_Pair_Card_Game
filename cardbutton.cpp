#include "cardbutton.h"

int CardButton::totalCardCount = 0;

CardButton::CardButton(const QString& text,
                       QWidget* parent)
{
    this->cardText = text;
    this->isFlipped = false;
    this->cardId = CardButton::totalCardCount;
    CardButton::totalCardCount++;
    QPalette pal = palette();
    pal.setColor(QPalette::Button, QColor(Qt::lightGray));
    setPalette(pal);
    setFlat(true);
    setAutoFillBackground(true);
    update();
}

void CardButton::flip_card(){
    if(this->isFlipped) {
        this->setText("");
    } else{
        this->setText(this->cardText);
    }
    this->isFlipped = !this->isFlipped;
    setFlat(true);
    setAutoFillBackground(true);
    update();
}
