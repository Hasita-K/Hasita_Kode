/*
Hasita Kode
Computer Science 1 (COP 3502 C) Spring 2026 - Dr. Ahmed
Assignment #0: C Review
*/

#include <stdio.h>
#include "main.h"

void readData(struct cat *cats, int *c)
{
    //scan # of cats
    scanf("%d", c);

    //scan cat info
    for(int i = 0; i < *c; i++){
        scanf("%d %s %d %d %d", &cats[i].cat_ID, cats[i].name, &cats[i].score1, &cats[i].score2, &cats[i].score3);
        cats[i].average = (cats[i].score1 + cats[i].score2 + cats[i].score3) / 3.0;
    }
}

int getCutestCat(struct cat *s, int n)
{
    //init max value = 0
    float maxValue = 0;

    //init idx = -1

    int idx = -1;

    //Loop up to count, everytime you find a better average update max value

    for(int i = 0; i < n; i++)
    {
        if(s[i].average > maxValue)
        {
            maxValue = s[i].average;
            idx = i;
        }
    }
    
    //return idx with max
    return idx;
}

int main()
{
    //declare and init variables
    struct cat cat[MAXCATS];

    int count;

    int letterCount[26] = {0};
    int total = 0;

    //call read data
    readData(cat, &count);

    //call and get return index from cutestCat
    int idxCutest = getCutestCat(cat, count);

   
    //print all cat info
    for(int i = 0; i < count; i++)
    {
        printf("%d %s %d %d %d %.2lf\n", cat[i].cat_ID, cat[i].name, cat[i].score1, cat[i].score2, cat[i].score3, cat[i].average);

        //from char frequency video in C review folder
        if(cat[i].name[0] >= 'A' && cat[i].name[0] <= 'Z')
        {
            letterCount[cat[i].name[0] - 'A']++;
            total++;
        }
        
    }

    printf("Cutest cat is %s\n", cat[idxCutest].name);
    //char frequency loop
    for(int i = 0; i < 26; i++)
    {
        printf("%c: %d %.2lf%%\n", i + 'A', letterCount[i], 100*(letterCount[i] * 1.0/total) );
    }

    return 0;


}