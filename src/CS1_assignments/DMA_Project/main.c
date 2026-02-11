/*COP 3502C PA1
This program is written by: Hasita Kode*/

//call all the libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//copy the structs from the program file
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


//write the function prototypes 
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
    //declare all the variables
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
    //Dynamically allocate the dictionary
    char **BreedList = malloc(sizeof(char*) * (*count));

    //fill the dictionary up with breeds
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
    //loop through the dictionary
    for(int i = 0; i < breedCount; i++)
    {
        if(strcmp(breedName, dictionary[i]) == 0)//once you find the breed return it from it's place in the dictionary
        {
            return dictionary[i];
        }

    }
    return NULL;
}


CatStore* createStore(int kennelCount, int breedCount, char** dictionary)
{
    //get memory for the CatStore struct
    CatStore *ptr = malloc(sizeof(CatStore));
    //store the total num of kennels
    ptr->numKennels = kennelCount;

    //allocate memory for capacities (2D Array so I'll double for loop)
    ptr->capacities = malloc(sizeof(int*) * kennelCount);
    for(int i = 0; i < kennelCount; i++)
    {
        //allocate memory for breedCount ints
        ptr->capacities[i] = malloc(sizeof(int) * breedCount);
        for(int j = 0; j < breedCount; j++)
        {
            //get the capacity constraints for each breed
            scanf("%d", &ptr->capacities[i][j]);
        }
    }

    ptr->kennels = createKennels(ptr->capacities, kennelCount, breedCount, dictionary);

    return ptr;   
}


Kennel* createKennels(int ** constraints, int kennelCount, int breedCount, char** dictionary)
{
    //allocate memory for the kenel struct
    Kennel* kennel = malloc(sizeof(Kennel) * kennelCount);
    //loop through the kennels and init their fields
    for(int i = 0; i < kennelCount; i++)
    {
        char tempLocation[50];
        scanf("%s", tempLocation);
        //allocate memory for the location string
        int len = strlen(tempLocation) + 1;
        kennel[i].location = malloc(sizeof(char) * len);
        strcpy(kennel[i].location, tempLocation);
        scanf("%d", &kennel[i].occupancy);

        //get the sum of all breed capacity constraints 
        kennel[i].maxCapacity = 0;
        for(int j = 0; j < breedCount; j++)
        {
            kennel[i].maxCapacity += constraints[i][j];
            
        }
        kennel[i].cats = NULL; //set this equal to null to init the cats 

        //if the kennel already has cats create and store them
        if(kennel[i].occupancy > 0)
        {
            kennel[i].cats = createCats(dictionary, breedCount, kennel[i].occupancy);
        }


    }
    
    return kennel;
}

Cat** createCats(char** dictionary, int breedCount, int count)
{
    //allocate memory for an array of cat struct pointers
    Cat** cats = (Cat**) malloc(sizeof(Cat*) * count);

    //go through a look till count to create each cat individually
    for(int i = 0; i < count; i++)
    {
        cats[i] = createSingleCat(dictionary, breedCount);
    }
    
    return cats;
}

Cat* createSingleCat(char** dictionary, int breedCount)
{
    //allocate memory for a single cat struct
    Cat* singleCat = malloc(sizeof(Cat));
    //get the cat's name from the user
    char tempName[50];
    scanf("%s", tempName);
    //get len so you know what to multiply sizeof, and allocate memory for each cat name
    int len = strlen(tempName) + 1;
    singleCat->name = malloc(sizeof(char) * len);
    strcpy(singleCat->name, tempName);

    //get cat age and weight
    scanf("%d", &singleCat->age);
    scanf("%f", &singleCat->weight);

    //get the breed name
    char tempBreed[50];
    scanf("%s", tempBreed);
    //NO DMA THE BREED!!!!!
    //instead set the breed ptr to the matching string in the dictionary
    singleCat->breed = getCharPtrByBreed(dictionary, tempBreed, breedCount);
    
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
    //go through all the kennels, then go through each cat in the kennel
    for(int i = 0; i < s->numKennels; i++)
    {
        for(int j = 0; j < s->kennels[i].occupancy; j++)
        {
            //compare the pointers to find the kennel with the target cat
            if(s->kennels[i].cats[j] == cat)
                return &s->kennels[i];//return the ADDRESS of that kennel
        }
        
    }

    return NULL;
}

int getCatPosi(Kennel* home, Cat* cat)
{
    //go through all the cats in the kennel
    //then compare the pointers to find the specific target cat
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
    //go through the kennels in store, then go through cats in that kennel
    for(int i = 0; i < s->numKennels; i++)
    {
        for(int j = 0; j < s->kennels[i].occupancy; j++)
        {
            //compare the cat's name with the target cat's name
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
    //get the index of the cat that needs to be removed
    int targetRemoval = getCatPosi(k, cat);
    //if there's no cat found then get out of this function
    if(targetRemoval == -1)
        return;
     //shift all the cats to the left once it's removed
    for(int i = targetRemoval; i < k->occupancy - 1; i++)
    {
        k->cats[i] = k->cats[i + 1];
    }
    //decreasing the occupancy bcs 1 cat is gone
    k->occupancy--;

    //make sure to handle the case where there are no cats in kennel
    //I'll just free the cats array
    if(k->occupancy == 0)
    {
        free(k->cats);
        k->cats = NULL;
    }
    else
    {
        //resize the cat array to match the new kennel occupancy
        k->cats = realloc(k->cats, k->occupancy * sizeof(Cat*));
    }
}

void freeBreeds(char** dictionary, int breedCount)
{
    //free the breed in the dictionary by iterating through the dictionary.
    for(int i = 0; i < breedCount; i++)
    {
        free(dictionary[i]);
    }
    //free the array of breed pointers in the dictionary
    free(dictionary);
}

void freeStore(int count, CatStore* store)
{
    //loop through each kennel in store and free the location string
    for(int i = 0; i < count; i++)
    {
        free(store->kennels[i].location);
            //loop through all the cats in the kennel
            for(int k = 0; k < store->kennels[i].occupancy; k++)
            {   
                //free the name of the cat and the cat struct
                free(store->kennels[i].cats[k]->name);
                free(store->kennels[i].cats[k]);
                
            }
        //free the cat pointers and capacities in the kennel
        free(store->kennels[i].cats);
        free(store->capacities[i]);
    }
    //free the array of kennel structs and the array of capacity pointers    
    free(store->kennels);
    free(store->capacities);
}

void runQueries(CatStore* s, char** dictionary, int breedCount, int numQueries)
{
    int qType = 0;
    for(int i = 0; i < numQueries; i++)
    {   
        //get the query type
        scanf("%d", &qType);
        //use if else if to go through each scenario
        if(qType == 1)
        {
            int foundedCat = 0;//using this to see if at least a cat is found
            char tempName[50];//temporarily stores teh breed's name
            scanf("%s", tempName);
            //loop through the kennels then the cats in the current kennel
            for(int i = 0; i < s->numKennels; i++)
            {
                for(int j = 0; j < s->kennels[i].occupancy; j++)
                {
                    //I'm just going to make a cat pointer so my code looks neat
                    Cat* cat = s->kennels[i].cats[j];
                    //compare cat's breed with the temp breed
                    if(strcmp(cat->breed, tempName) == 0)
                    {
                        //print all the cat details
                        printf("%s %.2f %d %s %s\n", cat->name, cat->weight, cat->age, s->kennels[i].location, STATUS_CAT[cat->status]);
                        foundedCat = 1;
                    }
                }
            }

            //what to do if no cat is found
            if(foundedCat == 0)
            {
                printf("No cat with breed %s\n", tempName);
            }

        }
        else if(qType == 2)
        {
            int updatedCatStatus;
            char tempCatName[50];
            //get the updated cat status and name of the cat being updated
            scanf("%d %s", &updatedCatStatus, tempCatName);
            
            //get the pointer to the cat
            Cat* catPointerWithName = getCatByName(s, tempCatName);
            if(catPointerWithName == NULL)
            {
                continue;
            }
            //change the cat's status
            catPointerWithName->status = updatedCatStatus;

            printf("%s is now %s!\n", catPointerWithName->name, STATUS_CAT[updatedCatStatus]);
            //if the cat is adopted already then remove it from the kennel
            if(updatedCatStatus == 0)
            {
                Kennel *home = getKennelByCat(s, catPointerWithName);
                if(home != NULL)//the pointer not being null means that a kennel was found
                {
                    //remove the cat and free the dynamic memory aspects of the cat
                    removeCatFromKennel(home, catPointerWithName);
                    free(catPointerWithName->name);
                    free(catPointerWithName);   
                }
            }
            
        
        }
        else if(qType == 3)
        {
            char tempCatName[50];
            char tempLocation[50];
            //get the cat name and location
            scanf("%s %s", tempCatName, tempLocation);

            //call getCatByName to get the pointer with the cat requested in the input
            Cat* targetCat = getCatByName(s, tempCatName); //lol target Cat sounds so devious

            //if the cat isn't found then skip through
            if(targetCat == NULL)
                continue;


            //call canMoveTo to actually check if the cat can move
            int canMove = canMoveTo(s, tempLocation, targetCat->breed, dictionary, breedCount);
            if(canMove == 0)
            {
                printf("%s cannot take a %s cat!\n", tempLocation, targetCat->breed);
                continue;
            }
            //find the current kennel of the cat        
            Kennel* kennelToMoveCat = getKennelByCat(s, targetCat);

            if(kennelToMoveCat == NULL)
                continue;
            //find the target kennel now
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


