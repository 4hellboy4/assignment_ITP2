#include <stdio.h>
#include <string.h>

// data structure to store player's positions
enum Position {
    Goalkeeper,
    Defender,
    Midfielder,
    Forward,
};

// data structure to save each player's data properly
struct Player {
    char id[5000];
    char name[100];
    enum Position position;
    int age;
    int score;
};

// array of players
struct Player players[5000];
int lengthAr = 0; // length of array

// check that a certain symbol is in the string
int contains(char sym, char str[]) {
    for (int i = 0; i < strlen(str); ++i) {
        if (sym == str[i])
            return 1;
    }
    return 0;
}

// check that string's chars are a substring of another string
int checkLetters(char string[], char list[]) {
    for (int i = 0; i < strlen(string); ++i) {
        if (contains(string[i], list) == 0)
            return 0;
    }
    return 1;
}

// check that a player ID exists in the array of players
int isExist(char id[]) {
    for (int i = 0; i < (sizeof(players) / sizeof(players[0])); ++i) {
        if (strcmp(players[i].id, id) == 0)
            return 1;
    }
    return 0;
}

// check if player data is valid to add to array
int checkData(struct Player player, int flag) {
    char str[100];
    strncpy(str, &player.name[1], strlen(player.name) - 1);
    str[strlen(player.name) - 1] = '\0';
    if (contains(player.name[0], "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
        && (strlen(player.name) >= 2 && strlen(player.name) <= 15)
        && checkLetters(str, "abcdefghijklmnopqrstuvwxyz")
        && checkLetters(player.id, "0123456789")
        && (flag == 0 ? !isExist(player.id) : isExist(player.id))
        && (player.age >= 18 && player.age <= 100)
        && (player.score >= 0 && player.score < 1000)
        && player.position != -1
            ) {
        return 1;
    }
    return 0;
}

// check if two strings are equal
int equal(char str1[], char str2[]) {
    if (strlen(str1) != strlen(str2)) {
        return 0;
    } else {
        for (int i = 0; i < strlen(str1); ++i) {
            if (str1[i] != str2[i])
                return 0;
        }
    }
    return 1;
}

// delete existing players from the array, instead print "Invalid inputs"
void delete(char id[], FILE *pointer) {
    for (int i = 0; i < lengthAr; ++i) {
        if (equal(id, players[i].id) == 1) {
            for (int j = i; j < lengthAr; ++j) {
                players[j] = players[j+1];
            }
            lengthAr--;
            return;
        }
    }
    fprintf(pointer, "Impossible to delete\n");
}

// return a players position based on the gotten argument
char* returnPosition(enum Position pos) {
    switch (pos) {
        case Goalkeeper:
            return "Goalkeeper";
        case Forward:
            return "Forward";
        case Midfielder:
            return "Midfielder";
        case Defender:
            return "Defender";
    }
}

// display all players, if an error has been caught, we print "Invalid inputs"
void display(FILE *pointer) {
    if (lengthAr < 1) {
        fprintf(pointer, "Invalid inputs\n");
    } else {
        for (int i = 0; i < lengthAr; ++i) {
            struct Player temp = players[i];
            fprintf(pointer, "ID: %s, Name: %s, Position: %s, Age: %d, Goals: %d\n", temp.id, temp.name, returnPosition(temp.position), temp.age, temp.score);
        }
    }
}

//search for players
void search(char id[], FILE *pointer) {
    fprintf(pointer, isExist(id) ? "Found\n" : "Not found\n");
}

// set a players position, if it's not in the list we return -1 and then check this condition
enum Position setPosition(char position[]) {
    if (equal(position, "Goalkeeper")) {
        return Goalkeeper;
    } else  if (equal(position, "Defender")) {
        return Defender;
    }  if (equal(position, "Midfielder")) {
        return Midfielder;
    }  if (equal(position, "Forward")) {
        return Forward;
    } else {
        return -1;
    }
}

int main() {
    // create streams for output and input
    FILE *inputPointer;
    FILE *outputPointer;

    inputPointer = fopen("input.txt", "r");
    outputPointer = fopen("output.txt", "w");

    // store a string which is stand for gotten command, then we check what it equals to
    char command[20];
    while (fscanf(inputPointer, "%s", command) == 1) {
        if (strcmp(command, "Add") == 0) {
            char id[30], name[50], position[20];
            int age, score;
            // check that input of arguments was correct, instead print "Invalid inputs" and break the loop.
            // For other cases with checking output it's the same
            if (fscanf(inputPointer, "%s %s %s %d %d", id, name, position, &age, &score) != 5) {
                fprintf(outputPointer, "Invalid inputs\n");
                break;
            }
            struct Player temp;
            strcpy(temp.id, id);
            strcpy(temp.name, name);
            temp.position = setPosition(position);
            temp.age = age;
            temp.score = score;
            if (checkData(temp, 0)) {
                players[lengthAr] = temp; // add new player and increase the length counter
                lengthAr++;
            } else {
                fprintf(outputPointer, "Invalid inputs\n");
                break;
            }
        }
        else if (strcmp(command, "Delete") == 0) {
            char id[30];
            fscanf(inputPointer, "%s", id);
            if (strcmp(id, "") == 0) {
                fprintf(outputPointer, "Invalid input\n");
                continue;
            }
            delete(id, outputPointer);
        } else if (strcmp(command, "Search") == 0) {
            char id[30];
            fscanf(inputPointer, "%s", id);
            if (strcmp(id, "") == 0) {
                fprintf(outputPointer, "Invalid input\n");
                continue;
            }
            search(id, outputPointer);
        } else if (strcmp(command, "Update") == 0) {
            char id[30], name[50], position[20];
            int age, scores;
            if (fscanf(inputPointer, "%s %s %s %d %d", id, name, position, &age, &scores) != 5) {
                fprintf(outputPointer, "Invalid inputs\n");
                break;
            }
            struct Player temp;
            strcpy(temp.id, id);
            strcpy(temp.name, name);
            temp.position = setPosition(position);
            temp.age = age;
            temp.score = scores;
            if (checkData(temp, 1)) {
                for (int i = 0; i < lengthAr; ++i) {
                    if (strcmp(id, players[i].id) == 0) {
                        strcpy(players[i].name, name);
                        players[i].position = temp.position;
                        players[i].age = age;
                        players[i].score = scores;
                        break;
                    }
                }
            } else {
                fprintf(outputPointer, "Invalid inputs\n");
                break;
            }
        } else if (strcmp(command, "Display") == 0) {
            display(outputPointer);
            break;
        }else{ // if we don't get anything or command is incorrect, print "Invalid inputs"
            fprintf(outputPointer, "Invalid inputs\n");
            break;
        }
    }

    // close all opened streams
    fclose(inputPointer);
    fclose(outputPointer);

    return 0;
}
