#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cat{
    char *name;
    int age;
    float weight;
    char *breed;
    int status;
} Cat;

typedef struct Kennel{
    char *location;
    int occupancy;
    Cat **cats;
    int maxCapacity;
} Kennel;

typedef struct CatStore{
    int **capacities;
    int numKennels;
    Kennel *kennels;
} CatStore;

const char STATUS_CAT[3][20] = {"ADOPTED", "PENDING", "AVAILABLE"};
char** readBreeds(int* count);
char* getCharPtrByBreed(char** dictionary, char* breedName, int breedCount);
CatStore* createStore(int kennelCount, int breedCount, char** dictionary);
Kennel* createKennels(int** constraints, int kennelCount, int breedCount, char** dictionary);
Cat** createCats(char** dictionary, int breedCount, int count);
Cat* createSingleCat(char** dictionary, int breedCount);
int canMoveTo(CatStore *s, char* location, char* breed, char** dictionary, int breedCount);
Kennel* getKennelByCat(CatStore* s, Cat* cat);
int getCatPosi(Kennel* home, Cat* cat);
Cat* getCatByName(CatStore* s, char* catName);
void removeCatFromKennel(Kennel* k, Cat* cat);
void runQueries(CatStore* s, char** dictionary, int breedCount, int numQueries);
void freeBreeds(char** dictionary, int breedCount);
void freeStore(int count, CatStore* s);


int main()
{
    char **dictionary;
    int breedCount;
    int kennelCount;
    int numQueries;

    //create the dictionary with readBreeds
    dictionary = readBreeds(&breedCount);

    //get the kennelCount
    scanf("%d", &kennelCount);

    //now that I have the count I can create the kennels
    //ok first I need to create the store
    CatStore* theCatStore = createStore(kennelCount, breedCount, dictionary);

    theCatStore->kennels = createKennels(theCatStore->capacities, kennelCount, breedCount, dictionary);

    //use create cats and loop through each kennel to fill it with cats
    for(int i = 0; i < kennelCount; i++)
    {
        if(theCatStore->kennels[i].occupancy <= theCatStore->kennels[i].maxCapacity)
            theCatStore->kennels[i].cats = createCats(dictionary, breedCount, theCatStore->kennels[i].occupancy);
        else    
            break;

    }

    //now read the query
    scanf("%d", &numQueries);

    //call the Queries function to process the query
    runQueries(theCatStore, dictionary, breedCount, numQueries);

    //free everything (basically)
    freeBreeds(dictionary, breedCount);
    freeStore(kennelCount, theCatStore);
    free(theCatStore);
    
    return 0;
}

char** readBreeds(int *count)
{

    //I've created the dictionary with this function bt dubs
    scanf("%d", count);
    char **BreedList = malloc(sizeof(char*) * (*count));

    for(int i = 0; i < *count; i++)
    {
        char breedName[50];
        scanf("%s",breedName);
        BreedList[i] = malloc(sizeof(char) * (strlen(breedName) + 1));
        strcpy(BreedList[i], breedName);
    }

    return BreedList;
}


char* getCharPtrByBreed(char **dictionary, char *breedName, int breedCount)
{
    
    for(int i = 0; i < breedCount; i++)
    {
        if(strcmp(breedName, dictionary[i]) == 0)
        {
            return dictionary[i];
        }

    }
    return NULL;
}


CatStore* createStore(int kennelCount, int breedCount, char** dictionary)
{
    CatStore *ptr = malloc(sizeof(CatStore));

    ptr->numKennels = kennelCount;

    ptr->capacities = (int**)malloc(sizeof(int*) * kennelCount);
    for(int i = 0; i < kennelCount; i++)
    {
        ptr->capacities[i] = malloc(sizeof(int) * breedCount);
        for(int j = 0; j < breedCount; j++)
        {
            scanf("%d", &ptr->capacities[i][j]);
        }
    }

    return ptr;   
}


Kennel* createKennels(int ** constraints, int kennelCount, int breedCount, char** dictionary)
{
    Kennel* kennel = malloc(sizeof(Kennel) * kennelCount);
    for(int i = 0; i < kennelCount; i++)
    {
        char tempLocation[50];
        scanf("%s", tempLocation);
        int len = strlen(tempLocation) + 1;
        kennel[i].location = malloc(sizeof(char) * len);
        strcpy(kennel[i].location, tempLocation);

        int maxCnt = 0;

        for(int j = 0; j < breedCount; j++)
        {
            maxCnt += constraints[i][j];
            
        }

        kennel[i].maxCapacity = maxCnt;

        scanf("%d", &kennel[i].occupancy);

    }
    
    return kennel;
}

Cat** createCats(char** dictionary, int breedCount, int count)
{
    Cat** cats = (Cat**) malloc(sizeof(Cat*) * count);
    for(int i = 0; i < count; i++)
    {
        cats[i] = createSingleCat(dictionary, breedCount);
    }
    
    return cats;
}

Cat* createSingleCat(char** dictionary, int breedCount)
{
    Cat* singleCat = malloc(sizeof(Cat));
    char tempName[50];
    scanf("%s", tempName);
    int len = strlen(tempName) + 1;
    singleCat->name = malloc(sizeof(char) * len);
    strcpy(singleCat->name, tempName);

    scanf("%d", &singleCat->age);
    scanf("%f", &singleCat->weight);
    char tempBreed[50];
    scanf("%s", tempBreed);
    singleCat->breed = getCharPtrByBreed(dictionary, tempBreed, breedCount);
    //I'm going to handle for when the breed pointer is NULL
    if(singleCat->breed == NULL)
    {
        singleCat->breed = dictionary[0];
    }
    singleCat->status = 2;

    

    return singleCat;
}

int canMoveTo(CatStore* s, char* location, char* breed, char** dictionary, int breedCount)
{
    //loop through kennel of store and look for location name (strcmp)
    //then get the index
    int kennelIndex = -1;
    for(int i = 0; i < s->numKennels; i++)
    {
        if((strcmp(location, s->kennels[i].location)) == 0)
        {
            kennelIndex = i;
            break;
        }
    }

    if(kennelIndex == -1)
        return 0;

    //use the index to then check if current #of cats and the capacity match
    //check total occupancy vs maxCapacity
    //if it doesn't work then return 0
    if(s->kennels[kennelIndex].occupancy >= s->kennels[kennelIndex].maxCapacity)
        return 0;
    
    //compare the constraint of the specific breed
    //find the breed and store the index of it in the dictionary

    //loop through the dictionary and get the index that is holding the breed
    //use strcmp and once you find it save the index
    int breedIndex = -1;
    for(int j = 0; j < breedCount; j++)
    {
        if(strcmp(dictionary[j], breed) == 0)
        {
            breedIndex = j;
            break;
        }
    }
    if(breedIndex == -1)
        return 0;
    


    //count how many of this specific breed you have in that specific kennel

    //go through all the cats stored in the kennel
    //count how many cats of the breed you have
    //init variable to 0 and go through all the cats in that kennel
    //use strcmp and everytime you find that breed, incrememnt the coutner by 1
    int totalBreed = 0;
    for(int k = 0; k < s->kennels[kennelIndex].occupancy; k++)
    {
        if((strcmp(s->kennels[kennelIndex].cats[k]->breed, breed)) == 0)
        {
            totalBreed++;
        }
    }

    //now check if the counter's sum is going over the capacity
    //compare the current number of cats of this specific breed from this kennel to the breed capacity of this kennel
    if(totalBreed >= s->capacities[kennelIndex][breedIndex])
    {
        return 0;
    }

    return 1;
    //get the breed capacity in the capacities 2D array
}

Kennel* getKennelByCat(CatStore* s, Cat* cat)
{
    for(int i = 0; i < s->numKennels; i++)
    {
        for(int j = 0; j < s->kennels[i].occupancy; j++)
        {
            if(s->kennels[i].cats[j] == cat)
                return &s->kennels[i];
        }
        
    }

    return NULL;
}

int getCatPosi(Kennel* home, Cat* cat)
{
    for(int i = 0; i < home->occupancy; i++)
    {
        if(home->cats[i] == cat)
        {
            return i;
        }
    }
    return -1;
}

Cat* getCatByName(CatStore *s, char* catName)
{
    for(int i = 0; i < s->numKennels; i++)
    {
        for(int j = 0; j < s->kennels[i].occupancy; j++)
        {
            if((strcmp(s->kennels[i].cats[j]->name, catName)) == 0)
            {
                return s->kennels[i].cats[j];
            }
        }
    }
    return NULL;
}

void removeCatFromKennel(Kennel* k, Cat* cat)
{
    int targetRemoval = getCatPosi(k, cat);
    if(targetRemoval == -1)
        return;
    for(int i = targetRemoval; i < (k->occupancy - 1); i++)
    {
        k->cats[i] = k->cats[i + 1];
    }

    k->occupancy--;

    //make sure to handle the case where there are no cats
    if(k->occupancy == 0)
    {
        free(k->cats);
        k->cats = NULL;
    }
    else
    {
        k->cats = realloc(k->cats, k->occupancy * sizeof(Cat*));
    }
}

void freeBreeds(char** dictionary, int breedCount)
{
    for(int i = 0; i < breedCount; i++)
    {
        free(dictionary[i]);
    }
    free(dictionary);
}

void freeStore(int count, CatStore* store)
{
    for(int i = 0; i < count; i++)
    {
        free(store->kennels[i].location);
            for(int k = 0; k < store->kennels[i].occupancy; k++)
            {
                free(store->kennels[i].cats[k]->name);
                free(store->kennels[i].cats[k]);
                
            }
        free(store->kennels[i].cats);
        free(store->capacities[i]);
    }
        
    free(store->kennels);
    free(store->capacities);
}

void runQueries(CatStore* s, char** dictionary, int breedCount, int numQueries)
{
    int qType = 0;
    for(int i = 0; i < numQueries; i++)
    {
        scanf("%d", &qType);

        if(qType == 1)
        {
            int foundedCat = 0;
            char tempName[50];
            scanf("%s", tempName);
            for(int i = 0; i < s->numKennels; i++)
            {
                for(int j = 0; j < s->kennels[i].occupancy; j++)
                {
                    
                    if((strcmp(tempName, s->kennels[i].cats[j]->breed)) == 0)
                    {
                        printf("%s %.2f %d %s %s\n", s->kennels[i].cats[j]->name, s->kennels[i].cats[j]->weight, 
                    s->kennels[i].cats[j]->age, s->kennels[i].location, STATUS_CAT[s->kennels[i].cats[j]->status]);
                        foundedCat = 0;
                    }
                }
            }

            if(foundedCat == 0)
            {
                printf("No cat found with breed <%s>\n", tempName);
            }

        }
        else if(qType == 2)
        {
            int updatedCatStatus;
            char tempCatName[50];
            scanf("%d %s", &updatedCatStatus, tempCatName);

            Cat* catPointerWithName = getCatByName(s, tempCatName);
            if(catPointerWithName == NULL)
            {
                continue;
            }

            catPointerWithName->status = updatedCatStatus;

            if(updatedCatStatus == 0)
            {
                Kennel *home = getKennelByCat(s, catPointerWithName);
                if(home != NULL)
                {
                    removeCatFromKennel(home, catPointerWithName);
                    free(catPointerWithName->name);
                    free(catPointerWithName);   
                }
            }
            

            printf("%s is now %s\n", tempCatName, STATUS_CAT[updatedCatStatus]);
        
        }
        else if(qType == 3)
        {
            //create temp variables to get the input
            char tempCatName[50];
            char tempLocation[50];
            scanf("%s %s", tempCatName, tempLocation);

            //call getCatByName to get the pointer with the cat requested in the input
            Cat* targetCat = getCatByName(s, tempCatName); //lol target Cat sounds so devious

            if(targetCat == NULL)
                continue;
            //call canMoveTo to actually check if the cat can move
            int canMove = canMoveTo(s, tempLocation, targetCat->breed, dictionary, breedCount);
            if(canMove == 0)
            {
                printf("%s cannot take a %s cat!", tempLocation, targetCat->breed);
                continue;
            }
                
            Kennel* kennelToMoveCat = getKennelByCat(s, targetCat);

            if(kennelToMoveCat == NULL)
                continue;

            Kennel* targetKennel = NULL;
            for(int i = 0; i < s->numKennels; i++)
            {
                if(strcmp(tempLocation, s->kennels[i].location) == 0)
                {
                    targetKennel = &s->kennels[i];
                    break;
                }
            }

            if(targetKennel == NULL)
            {
                continue;
            }

            //now remove it
            removeCatFromKennel(kennelToMoveCat, targetCat);

            //now add it to the target one
            targetKennel->cats = realloc(targetKennel->cats, (targetKennel->occupancy + 1) * sizeof(Cat*));
            targetKennel->occupancy++;
            int indexToMoveCat = targetKennel->occupancy - 1;
            targetKennel->cats[indexToMoveCat] = targetCat;
            printf("%s moved successfully to %s\n", tempCatName, tempLocation);
            
        }
        else
            return;
    }   
}


