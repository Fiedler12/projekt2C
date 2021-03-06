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
void printFoundation(int index);
void clear();


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
void moveToF();

void confirmToF(struct Card *moveCard, struct FinishedPile *toPile);

void moveLast(struct Card *moveCard, struct Card *moveTo, struct Bottom *fromBottom);

void movetoEmpty(struct Card *moveCard, struct Bottom *toColumn);

int main()
{
    while (1) {
        printBoard();
        struct Card *lastF1;
        struct Card *lastF2;
        struct Card *lastF3;
        struct Card *lastF4;
        lastF1 = donePile[0].ptr;
        lastF2 = donePile[1].ptr;
        lastF3 = donePile[2].ptr;
        lastF4 = donePile[3].ptr;
        if (lastF1 != NULL && lastF2 != NULL && lastF3 != NULL && lastF4 != NULL) {
            while (lastF1->next != NULL) {
                lastF1 = lastF1->next;
            }
            while (lastF2->next != NULL) {
                lastF2 = lastF2->next;
            }
            while (lastF3->next != NULL) {
                lastF3 = lastF3->next;
            }
            while (lastF4->next != NULL) {
                lastF4 = lastF4->next;
            }
            if (lastF1->value == 'K' && lastF2->value == 'K' && lastF3->value == 'K' && lastF4->value == 'K') {
                printf("Tillykke! Kabalen gik op!");
                exit(1);
            }
        }
    }
}

void fillCards()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "C:\\Users\\andre\\OneDrive\\Skrivebord\\daus.txt";
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
    donePile[0].suit = 'H';
    donePile[1].suit = 'C';
    donePile[2].suit = 'D';
    donePile[3].suit = 'S';
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
    if (result->next == NULL && result->isShown == 'F') {
        result->isShown = 'S';
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
    printFoundation(1);
    printf("F2 (Clubs)");
    printf("\n");
    printLine(4);
    printf("\n");
    printLine(5);
    printFoundation(2);
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
        if (moveCard->isShown == F || moveTo->next != NULL || moveCard->suit == moveTo->suit || moveTo == NULL) {
            status[0] = 'E';
            status[1] = 'R';
            return;
        }else {
            struct Bottom *column;
            switch (getCommand[1]) {
                case '1':
                    column = &columns[0];
                    break;
                case '2':
                    column = &columns[1];
                    break;
                case '3':
                    column = &columns[2];
                    break;
                case '4':
                    column = &columns[3];
                    break;
                case '5':
                    column = &columns[4];
                    break;
                case '6':
                    column = &columns[5];
                    break;
                case '7':
                    column = &columns[6];
                    break;
                default:
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
            }
            switch (moveCard->value) {
            case 'A':
                if (moveTo->value == '2') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                break;
            case '2':
                if (moveTo->value == '3') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                break;
            case '3':
                if (moveTo->value == '4') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                break;
            case '4':
                if (moveTo->value == '5') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case '5':
                if (moveTo->value == '6') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case '6':
                if (moveTo->value == '7') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case '7':
                if (moveTo->value == '8') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case '8':
                if (moveTo->value == '9') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case '9':
                if (moveTo->value == 'T') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case 'T':
                if (moveTo->value == 'J') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case 'J':
                if (moveTo->value == 'Q') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
                }
                    break;
            case 'Q':
                if (moveTo->value == 'K') {
                    struct Card *prev;
                    prev = moveCard->prev;
                    if (prev == NULL) {
                        moveTo->next = moveCard;
                        column->ptr = NULL;
                        return;
                    }
                    prev->next = NULL;
                    moveCard->prev = moveTo;
                    moveTo->next = moveCard;
                }
                else {
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
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
        clear();
        fillCards();
        layOut(8, 0, 8);
        layOut(8, 1, 8);
        layOut(8, 2, 8);
        layOut(7, 3, 7);
        layOut(7, 4, 7);
        layOut(7, 5, 7);
        layOut(7, 6, 7);
        topCard = 0;
    } else if (getCommand[0] == 'S' && getCommand[1] == 'W') {
        status[0] = 'O';
        status[1] = 'K';
        clear();
        layOut(8, 0, 0);
        layOut(8, 1, 0);
        layOut(8, 2, 0);
        layOut(7, 3, 0);
        layOut(7, 4, 0);
        layOut(7, 5, 0);
        layOut(7, 6, 0);
        topCard = 0;
    } else if (getCommand[0] == 'S' && getCommand[1] == 'I') {
        status[0] = 'O';
        status[1] = 'K';
    } else if (getCommand[0] == 'S' && getCommand[1] == 'R') {
        status[0] = 'O';
        status[1] = 'K';
        mixCards();
    } else if (getCommand[0] == 'S' && getCommand[1] == 'D') {
        status[0] = 'N';
        status[1] = 'O';
    } else if (getCommand[0] == 'Q' && getCommand[1] == 'Q') {
        status[0] = 'O';
        status[1] = 'K';
        exit(0);
    } else if (getCommand[0] == 'P' && strlen(getCommand) == 1) {
        status[0] = 'O';
        status[1] = 'K';
        clear();
        layOut(1, 0, 0);
        layOut(6, 1, 1);
        layOut(7, 2, 2);
        layOut(8, 3, 3);
        layOut(9, 4, 4);
        layOut(10, 5, 5);
        layOut(11, 6, 6);
        topCard = 0;
    } else if (getCommand[0] == 'Q' && strlen(getCommand) == 1) {
        status[0] = 'O';
        status[1] = 'K';
        clear();
    } else if (strlen(getCommand) == 9 && getCommand[0] == 'C' && getCommand[7] == 'C') {
        moveCommand();
    } else if (strlen(getCommand) == 9 && getCommand[7] == 'F' && getCommand[0] == 'C') {
        moveToF();
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
        if (toColumn->ptr == NULL) {
            if (moveCard->value != 'K') {
                status[0] = 'E';
                status[1] = 'R';
                return;
            }
            movetoEmpty(moveCard, toColumn);
            return;
        }
        moveTo = toColumn->ptr;
        while (moveTo->next != NULL) {
            moveTo = moveTo->next;
        }
        if (fromColumn->ptr->next == NULL) {
            moveLast(moveCard, moveTo, fromColumn);
            return;
        }
        move(moveCard, moveTo);
        return;
    }
}


void moveToF() {
    if (getCommand[2] != ':' || getCommand[5] != '-' || getCommand[6] != '>') {
        status[0] = 'E';
        status[1] = 'R';
        return;
    } else {
        struct Bottom *fromColumn;
        struct Card *moveCard;
        struct FinishedPile *toPile;
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
                    toPile = &donePile[0];
                    break;
                case '2':
                    toPile = &donePile[1];
                    break;
                case '3':
                    toPile = &donePile[2];
                    break;
                case '4':
                    toPile = &donePile[3];
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
            confirmToF(moveCard, toPile);
        }
    }

void clear() {
    for (int i = 0; i < 7; ++i) {
        columns[i].ptr = NULL;
    }
    for (int i = 0; i < 52; ++i) {
        cards[i].next = NULL;
        cards[i].prev = NULL;
    }
    for (int i = 0; i < 4; ++i) {
        donePile[i].ptr = NULL;
    }
}

void printFoundation(int index) {
    if (donePile[index].ptr == NULL) {
        printf("[] ");
    }
    else {
        struct Card *current;
        current = donePile[index].ptr;
        while (current->next != NULL) {
            current = current->next; 
        }
        printf("%c%c ", current->value, current->suit);
    }
}

void confirmToF(struct Card *moveCard, struct FinishedPile *toPile) {
    if (toPile->suit != moveCard->suit) {
        status[0] = 'E';
        status[1] = 'R';
        return;
    } else if (moveCard->next != NULL) {
        status[0] = 'E';
        status[1] = 'R';
        return;
    } else {
        if (toPile->ptr == NULL && moveCard->value == 'A') {
            if (moveCard->prev != NULL) {
                struct Card *prev;
                prev = moveCard->prev;
                prev->next = NULL;
                moveCard->prev = NULL;
            }
            toPile->ptr = moveCard;
            status[0] = 'O';
            status[1] = 'K';
            return;
        } else {
            struct Card *endOfPile;
            endOfPile = toPile->ptr;
            while (endOfPile->next != NULL) {
                endOfPile = endOfPile->next;
            }
            switch (endOfPile->value) {
                case 'A':
                    if (moveCard->value != '2') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '2':
                    if (moveCard->value != '3') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '3':
                    if (moveCard->value != '4') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '4':
                    if (moveCard->value != '5') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '5':
                    if (moveCard->value != '6') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '6':
                    if (moveCard->value != '7') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                    }
                    return;
                case '7':
                    if (moveCard->value != '8') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '8':
                    if (moveCard->value != '9') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case '9':
                    if (moveCard->value != 'T') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case 'T':
                    if (moveCard->value != 'J') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case 'J':
                    if (moveCard->value != 'Q') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                case 'Q':
                    if (moveCard->value != 'K') {
                        status[0] = 'E';
                        status[1] = 'R';
                        return;
                    } else {
                        if (moveCard->prev != NULL) {
                            struct Card *prev;
                            prev = moveCard->prev;
                            prev->next = NULL;
                            moveCard->prev = NULL;
                        }
                        endOfPile->next = moveCard;
                        status[0] = 'O';
                        status[1] = 'K';
                        return;
                    }
                default:
                    status[0] = 'E';
                    status[1] = 'R';
                    return;
            }
        }
    }
}

void moveLast(struct Card *moveCard, struct Card *moveTo, struct Bottom *fromBottom) {
    fromBottom->ptr = NULL;
    moveCard->prev = moveTo;
    moveTo->next = moveCard;
}

void movetoEmpty(struct Card *moveCard, struct Bottom *toColumn) {
    toColumn->ptr = moveCard;
    struct Card* prev;
    prev = moveCard->prev;
    prev->next = NULL;
    moveCard->prev = NULL;
}