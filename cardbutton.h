#ifndef CARDBUTTON_H
#define CARDBUTTON_H
#include <QPushButton>
#include <QPalette>

class CardButton : public QPushButton
{
    Q_OBJECT
public:
    CardButton(const QString& text,
               QWidget* parent = 0);
    QString cardText;
    bool isFlipped;
    int cardId;
    static int totalCardCount;
public slots:
    void flip_card();
};



#endif // CARDBUTTON_H
