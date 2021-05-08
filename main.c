// Working of arithmetic operators
#include <stdio.h>
#include <accctrl.h>

void fillCards();
void mixCards();
void layOut(int deckSize, int index);
void printStack();
void printBoard();
void printLine(int lineIndex);
struct Card *getListIndex(int lineIndex, int arrayIndex);

int topCard;

struct Card
{
    char suit;
    char value;
    struct Card *next;
};
struct Card cards[52];

struct Bottom
{
    struct Card *ptr;
};
struct Bottom columns[7];


int main()
{
    fillCards();
    mixCards();
    topCard = 0;
    layOut(7,1);
    printBoard();
    /*printf("C1: ");
    struct Card *current = columns[1].ptr;
    struct Card *next = current->next;
    while (1) {
        printf("%c%c ", current->suit, current->value);
        current = next;
        next = current->next;
        if (next == NULL) {
            break;
        }
        */
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
//WORKS and poops and ze sprms
void layOut(int deckSize, int index) {
    struct Card *current;
    current = &cards[topCard];
    struct Card *next;
    columns[index].ptr = current;

    for (int i = 0; i < deckSize-1; ++i) {
        current->next = &cards[topCard + 1];
        next = current->next;
        current = next;
        topCard++;
    }
}
void printLine(int lineIndex) {
    struct Card *current;
    for (int i = 0; i < 7; ++i) {
        current = getListIndex(lineIndex,i);
        if (current == NULL){
            printf("\t");
        }
        printf("%c%c\t", current->value, current->suit);
    }
}

struct Card *getListIndex(int lineIndex, int arrayIndex) {
    struct Card *result;
    result = columns[arrayIndex].ptr;
    struct Card *next;
    next = result->next;
    if (lineIndex == 1) {
        return result;
    }
    for (int i = 0; i < lineIndex-1; ++i) {
        result = next;
        next = result->next;
        if (next == NULL) {
            break;
        }
    }
    return result;
}


void printBoard() {
    printf("C1\t C2 \t C3 \t C4 \t C5 \t C6 \t C7 \n\n");
    printLine(1);
}

void printStack() {
    struct Card *current;
    struct Card *next;
    current = columns[5].ptr;
    next = current->next;
    current = next;
        while (1) {
            printf("%c%c ", current->suit, current->value);
            if (current->next == NULL) {
                break;
            }
            next = current->next;
            current = next;
        }
    }
