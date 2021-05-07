// Working of arithmetic operators
#include <stdio.h>

void fillCards();

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
    for (int i = 0; i < 52; ++i) {
        printf("%c", cards[i].suit);
        printf("%c \n", cards[i].value);
    }
    return 0;
}

void fillCards()
{
    int t = 0;
    char suits[5] = {'H', 'C', 'D', 'S','\0'};
    char value[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            cards[t].suit = suits[i];
            cards[t].value = value[j];
            ++t;
        }
    }

}


