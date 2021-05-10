// Working of arithmetic operators
#include <stdio.h>
#include <accctrl.h>
#include <string.h>
#include <stdlib.h>

void fillCards();
void mixCards();
void layOut(int deckSize, int index, int turnedAmount);
void printStack();
void printBoard();
void printLine(int lineIndex);
struct Card *getListIndex(int lineIndex, int arrayIndex);
void move(struct Card *moveCard, struct Card *moveTo);
void takeCommand();
void moveCommand();
void moveToF();
void printFoundation(int index);

int topCard;
char lastCommand[9];
char getCommand[9];
char status[2];

enum boolean{S, F};

struct Card
{
    boolean isShown;
    char suit;
    char value;
    struct Card *next;
    struct Card *prev;
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
    char suit;
};

struct FinishedPile donePile[4];

int main()
{
    while (1) {
        printBoard();
    }

    /*struct Card *moveCard;
    struct Card *moveTo;
    moveCard = columns[3].ptr;
    moveTo = columns[4].ptr;
    while (moveCard->value != 'A' || moveCard->suit != 'S'){
        moveCard = moveCard->next;
    }
    while (moveTo->value != '2' || moveTo->suit != 'H') {
        moveTo = moveTo->next;
    }
    move(moveCard, moveTo);
    printBoard();
     */

    /*printf("C2: ");
    struct Card *current;
    current = &cards[36];
    while(current->prev != NULL) {
        printf("%c%c ", current->prev->suit, current->prev->value);
        current = current->prev;
    } */
    return 0;
}



void fillCards()
{
    /*int t = 0;
    char suits[4] = {'H', 'C', 'D', 'S'};
    char values[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    for (int i = 0; i < 4; ++i) {
        donePile[i].suit = suits[i];
        for (int j = 0; j < 13; ++j) {
            cards[t].suit = suits[i];
            cards[t].value = values[j];
            ++t;
        }
    } /*
        FILE *fp;
        fp = fopen ("C:\\Users\\olyng\\Desktop\\CardDeck.txt", "r");        // Open the file with 'read' option.    ''
        if(fp==NULL){ exit(-1);}
        char line[500];
        int t = 0;
        while (feof(fp)) {
            fscanf(fp, "%s", line);
            ++t;
        }
        line[t] = "\0";
        fclose(fp);
        printf("%s", line);
//while(head !=NULL){
        //   pop();
//}
 */
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "C:\\Users\\olyng\\Desktop\\CardDeck.txt";
    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Could not open file %s",filename);
    }
    int t = 0;
    int i = 0;
    while (fgets(str, MAXCHAR, fp) != NULL) {
        cards[t].value = str[i];
        ++i;
        cards[t].suit = str[i];
        i = 0;
        t++;
    }
    fclose(fp);
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
    struct Card *prev;
    struct Card *current;
    current = &cards[topCard];
    struct Card *next;
    if (t < turnedAmount) {
        current->isShown = F;
        ++t;
    }
    else {
        current->isShown = S;
    }
    columns[index].ptr = current;
    for (int i = 0; i < deckSize; ++i) {
        if (i == deckSize -1) {
            ++topCard;
            current->prev = prev;
            return;
        }
        if (i != 0) {
            current->prev = &cards[topCard - 1];
        }
        current->next = &cards[topCard + 1];
        next = current->next;
        prev = current;
        current = next;
        if (t < turnedAmount) {
            current->isShown = F;
            ++t;
        }
        else {
            current->isShown = S;
        }
        ++topCard;
    }
    current->prev = prev;
}
void printLine(int lineIndex) {
    struct Card *current;
    for (int i = 0; i < 7; ++i) {
        current = getListIndex(lineIndex,i);
        if (current == NULL){
            printf("\t");
        }
        else {
            if(current->isShown == S) {
                printf("%c%c\t", current->value, current->suit);
            }
            else if (current->isShown == F && current->next == NULL) {
                current->isShown = 'S';
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
    printFoundation(0);
    printf("F1 (Hearts)");
    printf("\n");
    printLine(2);
    printf("\n");
    printLine(3);
    printFoundation(2);
    printf("F2 (Clubs)");
    printf("\n");
    printLine(4);
    printf("\n");
    printLine(5);
    printFoundation(3);
    printf("F3 (Diamonds)");
    printf("\n");
    printLine(6);
    printf("\n");
    printLine(7);
    printFoundation(3);
    printf("F4 (Spades)");
    printf("\n");
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
    printf("LAST Command: %s\nMessage: %s\nINPUT >", lastCommand,status);
    takeCommand();
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

    void move(struct Card *moveCard, struct Card *moveTo) {
        if (moveCard->isShown == F || moveTo->next != NULL || moveCard->suit == moveTo->suit) {
            status[0] = 'E';
            status[1] = 'R';
            return;
        } else { switch (moveCard->value) {
            case 'A':
                if (moveTo->value == '2') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                break;
            case '2':
                if (moveTo->value == '3') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;

                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                break;
            case '3':
                if (moveTo->value == '4') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;

                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                break;
            case '4':
                if (moveTo->value == '5') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;

                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case '5':
                if (moveTo->value == '6') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;

                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case '6':
                if (moveTo->value == '7') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case '7':
                if (moveTo->value == '8') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case '8':
                if (moveTo->value == '9') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case '9':
                if (moveTo->value == 'T') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case 'T':
                if (moveTo->value == 'J') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case 'J':
                if (moveTo->value == 'Q') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
            case 'Q':
                if (moveTo->value == 'K') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev != NULL) {
                        prev->next = NULL;
                    }
                    moveCard->prev = &moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                }
                    break;
        }
    }
}

void takeCommand() {
    gets(getCommand);
    strupr(getCommand);
    strcpy(lastCommand, getCommand);
    if (getCommand[0] == 'L' && getCommand[1] == 'D') {
        status[0] = 'O';
        status[1] = 'K';
        fillCards();
        topCard = 0;
    } else if (getCommand[0] == 'S' && getCommand[1] == 'W') {
        status[0] = 'O';
        status[1] = 'K';
    } else if (getCommand[0] == 'S' && getCommand[1] == 'I') {
        status[0] = 'O';
        status[1] = 'K';
    } else if (getCommand[0] == 'S' && getCommand[1] == 'R') {
        status[0] = 'O';
        status[1] = 'K';
        mixCards();
    } else if (getCommand[0] == 'S' && getCommand[1] == 'D') {
        status[0] = 'O';
        status[1] = 'K';
    } else if (getCommand[0] == 'Q' && getCommand[1] == 'Q') {
        status[0] = 'O';
        status[1] = 'K';
        exit(0);
    } else if (getCommand[0] == 'P' && strlen(getCommand) == 1) {
        status[0] = 'O';
        status[1] = 'K';
        layOut(1, 0, 0);
        layOut(6, 1, 1);
        layOut(7, 2, 2);
        layOut(8, 3, 3);
        layOut(9, 4, 4);
        layOut(10, 5, 5);
        layOut(11, 6, 6);
    } else if (getCommand[0] == 'Q' && strlen(getCommand) == 1) {
        status[0] = 'O';
        status[1] = 'K';
    } else if (strlen(getCommand) == 9 && getCommand[0] == 'C' && getCommand[7] == 'C') {
        moveCommand();
    } else if (strlen(getCommand) == 9 && getCommand[7] == 'F' && getCommand[0] == 'C') {
        moveToF();
    }
    else {
        status[0] = 'E';
        status[1] = 'R';
        return;
    }
}

void moveCommand() {
    if (getCommand[2] != ':' || getCommand[5] != '-' || getCommand[6] != '>') {
        status[0] = 'E';
        status[1] = 'R';
        return;
    } else {
        struct Bottom *fromColumn;
        struct Bottom *toColumn;
        struct Card *moveCard;
        struct Card *moveTo;
        switch (getCommand[1]) {
            case '1':
                fromColumn = &columns[0];
                break;
            case '2':
                fromColumn = &columns[1];
                break;
            case '3':
                fromColumn = &columns[2];
                break;
            case '4':
                fromColumn = &columns[3];
                break;
            case '5':
                fromColumn = &columns[4];
                break;
            case '6':
                fromColumn = &columns[5];
                break;
            case '7':
                fromColumn = &columns[6];
                break;
            default:
                status[0] = 'E';
                status[1] = 'R';
                return;
        }
        switch (getCommand[8]) {
            case '1':
                toColumn = &columns[0];
                break;
            case '2':
                toColumn = &columns[1];
                break;
            case '3':
                toColumn = &columns[2];
                break;
            case '4':
                toColumn = &columns[3];
                break;
            case '5':
                toColumn = &columns[4];
                break;
            case '6':
                toColumn = &columns[5];
                break;
            case '7':
                toColumn = &columns[6];
                break;
            default:
                status[0] = 'E';
                status[1] = 'R';
                return;
        }
        moveCard = fromColumn->ptr;
        while (moveCard->value != getCommand[3] || moveCard->suit != getCommand[4]) {
            moveCard = moveCard->next;
            if (moveCard == NULL) {
                status[0] = 'E';
                status[1] = 'R';
                return;
            }
        }
        moveTo = toColumn->ptr;
        while (moveTo->next != NULL) {
            moveTo = moveTo->next;
        }
        move(moveCard, moveTo);
        return;
    }
}

void moveToF() {

}

void printFoundation(int index) {
    if (donePile[index].ptr == NULL) {
        printf("[] ");
    }
    else {
        struct Card *current;
        current = donePile->ptr;
        while (current->next != NULL) {
            current = current->next; 
        }
        printf("%c%c", current->value, current->suit); 
    }
}
