// Working of arithmetic operators
#include <stdio.h>
#include <accctrl.h>

void fillCards();
void mixCards();

struct Card
{
    char suit;
    char value;
    struct Card* next;
};

struct Card cards[52];

int main()
{
    fillCards();
    mixCards();
    for (int i = 0; i < 52; ++i) {
        printf("%c",cards[i].suit);
        printf("%c \n",cards[i].value);
    }

    return 0;
}

void fillCards()
{
    int t = 0;
    char suits[4] = {'H', 'C', 'D', 'S'};
    char values[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            cards[t].suit = suits[i];
            cards[t].value = values[j];
            ++t;
        }
    }
}

void mixCards()
{   int j, n;
    struct Card temp;
    for (int i = 0; i < 300; ++i) {
        n = rand() % 52;
        j = rand() % 52;
        temp.suit = cards[n].suit;
        temp.value = cards[n].value;
        cards[n].suit = cards[j].suit;
        cards[n].value = cards[j].value;
        cards[j].suit = temp.suit;
        cards[j].value = temp.value;
    }

}

