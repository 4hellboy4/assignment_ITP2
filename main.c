#include <stdio.h>

struct Player {
    char id[50];
    char name[100];
    char position[20];
    int age;
    int score;
};

void add(char *id[], char *name[], char *position[], int age, int scores, struct Player *ar[]);
void delete(int id);
void display();
void search(int id);
void update(char *id[], char *name[], char *position[], int age, int scores, struct Player *ar[]);


enum Positions {
    Goalkeeper,
    Defender,
    Midfielder,
    Forward,
};


int main() {
    printf("Hello, World!\n");
    return 0;
}


//add new player



//delete player



// display all players



//search for players



//update
