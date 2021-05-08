// Working of arithmetic operators
#include <stdio.h>
#include <accctrl.h>

void fillCards();
void mixCards();
void layOut(int deckSize, int index, int turnedAmount);
void printStack();
void printBoard();
void printLine(int lineIndex);
struct Card *getListIndex(int lineIndex, int arrayIndex);

int topCard;

enum boolean{F, T};

struct Card
{
    boolean isShown;
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

struct FinishedPile
{
    struct Card *ptr;
};

struct FinishedPile donePile[4];

int main()
{
    fillCards();
    mixCards();
    topCard = 0;
    layOut(1,0,0);
    layOut(6, 1,1);
    layOut(7,2,2);
    layOut(8,3,3);
    layOut(9,4,4);
    layOut(10,5,5);
    layOut(11,6,6);
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
void layOut(int deckSize, int index, int turnedAmount) {
    int t = 0;
    struct Card *current;
    current = &cards[topCard];
    struct Card *next;
    if (t < turnedAmount) {
        current->isShown = F;
        ++t;
    }
    else {
        current->isShown = T;
    }
    columns[index].ptr = current;
    for (int i = 0; i < deckSize; ++i) {
        if (i == deckSize -1) {
            ++topCard;
            return;
        }
        current->next = &cards[topCard + 1];
        next = current->next;
        current = next;
        if (t < turnedAmount) {
            current->isShown = F;
            ++t;
        }
        else {
            current->isShown = T;
        }
        ++topCard;
    }
}
void printLine(int lineIndex) {
    struct Card *current;
    for (int i = 0; i < 7; ++i) {
        current = getListIndex(lineIndex,i);
        if (current == NULL){
            printf("\t");
        }
        else {
            if(current->isShown == T) {
                printf("%c%c\t", current->value, current->suit);
            }
            else {
                printf("[]\t");
            }
        }
    }
}

struct Card *getListIndex(int lineIndex, int arrayIndex) {
    struct Card *result;
    result = columns[arrayIndex].ptr;
    if (result == NULL) {
        return result;
    }
    if (lineIndex == 1) {
        return result;
    }
    struct Card *next;
    next = result->next;
    if (next == NULL) {
        return next;
    }
    for (int i = 0; i < lineIndex - 1; ++i) {
        result = next;
        next = result->next;
        if (next == NULL && i < lineIndex - 2) {
            return NULL;
        }
    }
    return result;
}


void printBoard() {
    printf("C1\tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \n\n");
    printLine(1);
    printf("\t [] \t F1 \n");
    printLine(2);
    printf("\n");
    printLine(3);
    printf("\t [] \t F2 \n");
    printLine(4);
    printf("\n");
    printLine(5);
    printf("\t [] \t F3 \n");
    printLine(6);
    printf("\n");
    printLine(7);
    printf("\t [] \t F4 \n");
    printLine(8);
    printf("\n");
    printLine(9);
    printf("\n");
    printLine(10);
    printf("\n");
    printLine(11);
    printf("\n");
    printLine(12);
    printf("\n");
    printLine(13);
    printf("\n");
    printLine(14);
    printf("\n");
    printLine(15);
    printf("\n");
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
