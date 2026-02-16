//Hasita Kode
//Dr. Steinberg
//COP 3223
//Small Program 8

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 50

typedef struct{
    char * fname; //first name
	char * lname; //last name
	char * show; //favorite show
}record_t;

record_t * createArray(int maxsize);
record_t * insert(record_t *myarray, int *maxsize, int *currentsize); 
void display(record_t *myarray, int currentsize);
record_t * doubleIt(record_t *arr, int size); 
int removeRecord(record_t *arr, int size, int index); 
void freeRecords(record_t *arr, int size); 
void chomp(char word []);

int main(void)
{
	int maxsize;

	printf("Enter a size for the dynamic array: ");
	scanf("%d", &maxsize);


	record_t *myarray = createArray(maxsize);
	
	int currentsize = 0;
	int option = -1;

	while(option != 0)
    {
        printf("What would you like to do?\n");
        printf("1: Insert a record\n");
        printf("2: Display records\n");
        printf("3: Remove record\n");
        printf("4: Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                printf("Insert was selected...\n");
                myarray = insert(myarray, &maxsize, &currentsize);
                break;

            case 2:
                printf("Display was selected...\n");
                display(myarray, currentsize);
                break;

            case 3:
                printf("Remove was selected...\n");
                printf("Select an index of record to remove...\n");
                int index;
                scanf("%d", &index);
                currentsize = removeRecord(myarray,currentsize,index);
                break;

            case 4:
                printf("Exiting...\n");
                option = 0;
				break;

            default:
                printf("Invalid Selection...\n"); 
        }

    }
	
	freeRecords(myarray, currentsize);
	free(myarray);

	myarray = NULL;

	return 0;
}



record_t * insert(record_t *myarray, int *maxsize, int *currentsize)
{
	//check if there is enough size
	if(*currentsize == *maxsize)
    {
        printf("Array is full...Need to doubleIt...\n");
        myarray = doubleIt(myarray, *maxsize);
        *maxsize = *maxsize * 2;
    }
	
	//create temp variables
    char firstNamePlaceholder[LIMIT];
    char lastNamePlaceholder[LIMIT];
    char favoriteShowPlaceholder[LIMIT];
	
    int index = *currentsize;


	//get first name from the user
    printf("Enter the first name: ");
    scanf("%s", firstNamePlaceholder);
	chomp(firstNamePlaceholder);
	
    int len = strlen(firstNamePlaceholder) + 1;
    myarray[index].fname = malloc(sizeof(char) * len);
	
    if(myarray[index].fname == NULL)
    {
        printf("malloc error in insert...program exiting\n");
    }
	else 
	{
		strcpy(myarray[index].fname, firstNamePlaceholder);
	}
	
	//get last name from the user
    printf("Enter the last name: ");
    scanf("%s", lastNamePlaceholder);
	chomp(lastNamePlaceholder);
	
    len = strlen(lastNamePlaceholder) + 1;
    myarray[index].lname = malloc(sizeof(char) * len);
    if(myarray[index].lname == NULL)
    {
        printf("malloc error in insert...program exiting\n");
    }
    else 
	{
		strcpy(myarray[index].lname, lastNamePlaceholder);
	}
	
	//clear the buffer for the fgets to work 
	while(getchar() != '\n');
	
	//get the favorite show from the user
    printf("Enter favorite show: ");
	//use fgets to accomodate for the space
    fgets(favoriteShowPlaceholder, sizeof(favoriteShowPlaceholder), stdin);
	chomp(favoriteShowPlaceholder);
	
    len = strlen(favoriteShowPlaceholder) + 1;
    myarray[index].show = malloc(sizeof(char) * len);
	
    if(myarray[index].show == NULL)
    {
        printf("malloc error in insert...program exiting\n");
    }
	else 
	{
		strcpy(myarray[index].show, favoriteShowPlaceholder);
	}

	//increment the size
    (*currentsize)++;

    return myarray;
	
}

record_t * doubleIt(record_t * arr, int size)
{
	//allocate twice the array's size in the heap
	record_t * biggerRecord = malloc(sizeof(record_t) * (size * 2));
	
	if(biggerRecord == NULL)
	{
		printf("malloc error in doubleIt...program exiting\n");
		return biggerRecord ;
	}
	
	//copy from the old array into the new one
	for(int i = 0; i < size; i++)
		biggerRecord[i] = arr[i];
	
	free(arr);//free the old array
	
	return biggerRecord;

}


int removeRecord(record_t *arr, int size, int index)
{
	
	//check if the index is in range
	if(index < 0 || index >= size)
	{
		printf("Invalid Index\n");
		return size;
	}
	
	//free the memory of the records that were deleted
	free(arr[index].fname);
	free(arr[index].lname);
	free(arr[index].show);
	
	//shift the array to the left
	for(int i = index; i < size - 1; i++)
		arr[i] = arr[i + 1];
	
	size--;
	//return the new currsize
	return size;
}


void freeRecords(record_t * arr, int size)
{
	if(arr != NULL)
	{
		//free the strings inside the struct
		for(int i = 0; i < size; i++)
		{
			free(arr[i].fname);
			free(arr[i].lname);
			free(arr[i].show);
		} 
		
		//DO NOT free(arr), it's already done in the main
	}
}






record_t * createArray(int maxsize)
{
	record_t * arr = malloc(maxsize * sizeof(record_t));
	
	if(arr == NULL)
	{
		printf("malloc error in createArray...program exiting\n");
		exit(1);
	}
	
	return arr;
}



void display(record_t *myarray, int currentsize)
{
	printf("---------------------------------\n");

	for(int x = 0; x < currentsize; ++x)
	{
	    printf("myarray[%d].fname = %s\n", x, (x + myarray)->fname); //try it with myarray[x].name
		printf("myarray[%d].lname = %s\n", x, (x + myarray)->lname); //try it with myarray[x].name
		printf("myarray[%d].show = %s\n", x, (x + myarray)->show); //try it with myarray[x].show
	}

	printf("---------------------------------\n");
}

void chomp(char word [])
{
	if(word[strlen(word) - 1] == '\n')
		word[strlen(word) - 1] = '\0';
}