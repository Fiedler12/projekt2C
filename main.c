// Working of arithmetic operators
#include <stdio.h>
#include <accctrl.h>

void fillCards();
void mixCards();
void layOut();
int topCard;
void printStack();
void printBoard();



struct Card
{
    char suit;
    char value;
    struct Card* next;
};
struct Card cards[52];

struct Bottom
{
    struct Card* ptr;
};
struct Bottom c1;



int main()
{
    fillCards();
    mixCards();
    topCard = 0;
    layOut();
    printStack();
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

void layOut() {
    c1.ptr = &cards[topCard];
    ++topCard;
    c1.ptr->next = &cards[topCard];
    for (int i = 0; i < 7; ++i) {
        cards[topCard].next = &cards[++topCard];
    }
}

void printBoard() {
    printf("C1\t C2 \t C3 \t C4 \t C5 \t C6 \t C7");
}

void printStack() {
    printf("C1: %c%c", c1.ptr->suit, c1.ptr->value);

}
