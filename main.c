#include <stdio.h>
#include <string.h>

enum Position {
    Goalkeeper,
    Defender,
    Midfielder,
    Forward,
};

struct Player {
    char id[5000];
    char name[100];
    enum Position position;
    int age;
    int score;
};

struct Player players[5000];
int lengthAr = 0;

void add(char id[], char name[], char position[], int age, int score, FILE *pointer);
void delete(char id[], FILE *pointer);
void display(FILE *pointer);
void search(char id[], FILE *pointer);
void update(char id[], char name[], char position[], int age, int scores, FILE *pointer);
int checkData(struct Player player, int flag);

int main() {
    FILE *inputPointer;
    FILE *outputPointer;

    inputPointer = fopen("input.txt", "r");
    outputPointer = fopen("output.txt", "w");

    char command[20];
    while (fscanf(inputPointer, "%s", command)) {
        if (strcmp(command, "Add") == 0) {
            char id[30], name[50], position[20];
            int age, score;
            fscanf(inputPointer, "%s\n", id);
            fscanf(inputPointer, "%s\n", name);
            fscanf(inputPointer, "%s\n", position);
            fscanf(inputPointer, "%d\n", &age);
            fscanf(inputPointer, "%d\n", &score);
            add(id, name, position, age, score, outputPointer);
        }
        else if (strcmp(command, "Delete") == 0) {
            char id[30];
            fscanf(inputPointer, "%s\n", id);
            delete(id, outputPointer);
        } else if (strcmp(command, "Search") == 0) {
            char id[30];
            fscanf(inputPointer, "%s\n", id);
            search(id, outputPointer);
        } else if (strcmp(command, "Update") == 0) {
            char id[30], name[50], position[20];
            int age, score;
            fscanf(inputPointer, "%s\n", id);
            fscanf(inputPointer, "%s\n", name);
            fscanf(inputPointer, "%s\n", position);
            fscanf(inputPointer, "%d\n", &age);
            fscanf(inputPointer, "%d\n", &score);
            update(id, name, position, age, score, outputPointer);
        } else {
            display(outputPointer);
            break;
        }
    }

    fclose(inputPointer);
    fclose(outputPointer);

    return 0;
}


int contains(char sym, char str[]) {
    for (int i = 0; i < strlen(str); ++i) {
        if (sym == str[i])
            return 1;
    }
    return 0;
}

int checkLetters(char string[], char list[]) {
    for (int i = 0; i < strlen(string); ++i) {
        if (contains(string[i], list) == 0)
            return 0;
    }
    return 1;
}

int isExist(char id[]) {
    for (int i = 0; i < (sizeof(players) / sizeof(players[0])); ++i) {
        if (strcmp(players[i].id, id) == 0)
            return 1;
    }
    return 0;
}

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

int checkData(struct Player player, int flag) {
    if (contains(player.name[0], "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
        && (strlen(player.name) >= 2 && strlen(player.name) <= 15)
        && checkLetters(player.name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
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

//add new player
void add(char id[], char name[], char position[], int age, int score, FILE *pointer) {
    struct Player temp;
    strcpy(temp.id, id);
    strcpy(temp.name, name);
    temp.position = setPosition(position);
    temp.age = age;
    temp.score = score;
    if (checkData(temp, 0)) {
        players[lengthAr] = temp;
        lengthAr++;
    } else {
        fprintf(pointer, "Invalid inputs\n");
    }
}


//delete player
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


// display all players
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

//update
void update(char id[], char name[], char position[], int age, int scores, FILE *pointer) {
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
        fprintf(pointer, "Invalid inputs\n");
    }
}