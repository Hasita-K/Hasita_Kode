/*
Hasita Kode
Computer Science 1 (COP 3502 C) Spring 2026 - Dr. Ahmed
Assignment #0: C Review
*/


#define MAXSTRLEN 10
#define MAXCATS 500
struct cat{
    int cat_ID;
    char name[MAXSTRLEN + 1];
    int score1;
    int score2;
    int score3;
    float average;
};

void readData(struct cat *cats, int *c);

int getCutestCat(struct cat *s, int n);