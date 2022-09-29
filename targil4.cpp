#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Person {
	char* name;
	int id;
	struct Person* nextadders; 
} Person;

/***************************************************************************************
Function name: kill
Input: the pointer to the stuct of the Person we want to "kill".
Output: None
The function operation: "kills" the Person - free all the space that was allocated to the
Person that we are about to kill.
****************************************************************************************/
void kill(Person* deadman)
{
	//free(deadman->name); // free the space allocated for the dead man name. 
	//free(deadman); // free the space allocated for the dead man . RIP.

	if (deadman->name != NULL)
	{
		free(deadman->name);
	}
	free(deadman);
	return;
}

/***************************************************************************************
Function name: Failed
Input: the pointer to the first Person on the list.
Output: None
The function operation: only reached if malloc is failed somewhere in the initalization
. free all the space allocated by calling kill
****************************************************************************************/
void failed(Person** fst, Person** lt)
{
Person* ptr = NULL;
(*lt)->nextadders = NULL;
while (((*fst)->nextadders) != NULL)
{
	ptr = (*fst)->nextadders;
	(*fst)->nextadders = ptr->nextadders;
	kill(ptr);
}
kill(*fst);
exit(1);
}

/***************************************************************************************
Function name: Addplayers
Input: the pointer to the Person that the user want to intalize. the "first" pointer only
called because somewhere in this func we might want to call the func failed.
Output: None
The function operation: asks the user info about the current Person and insert the info to
the struct.
****************************************************************************************/
void Addplayers(Person** last, Person** first)
{
	char* finalName;
	char name[81];
	int id, nameLength;

	printf("name:\n");
	//flushall();
	//fgets(name, 81, stdin);
	scanf(" %[^\n]s", &name);
	nameLength = strlen(name)+1;
	finalName = (char*)malloc(nameLength * sizeof(char));
	if (finalName == NULL)
	{
		failed(first, last);
	}
	strcpy(finalName, name);
	printf("id:\n");
	scanf("%d", &id);

	
	
	if (*first == NULL)
	{
		*first = (Person*)malloc(sizeof(Person));
		if (*first == NULL)
		{
			free(finalName);
			exit(1);
		}
		(*first)->id = id;
		(*first)->name = finalName;
		(*first)->nextadders = *first;
		*last = *first;
	}
	else
	{
		Person* newPlayer = (Person*)malloc(sizeof(Person));
		if (newPlayer == NULL)
		{
			free(finalName);
			failed(first, last);
		}
		newPlayer->id = id;
		newPlayer->name = finalName;
		newPlayer->nextadders = (*last)->nextadders;
		(*last)->nextadders = newPlayer;
		*last = newPlayer;
	}

}


/***************************************************************************************
Function name: LetTheGamesBegin
Input:  the pointer to the first Person on the list.
Output: None
The function operation: playes the game, each Person kills the one after him in turns.
****************************************************************************************/
void LetTheGamesBegin(Person* first)
{
	Person* tmp = first;
	Person* killed = NULL;
	while (tmp->nextadders != tmp)
	{
		killed = tmp->nextadders;
		printf("%s kills %s\n", tmp->name, killed->name);
		tmp->nextadders = killed->nextadders;
		tmp = killed->nextadders;
		kill(killed);
	}
	printf("%s stayin alive!!\n", tmp->name);
	kill(tmp);
}

/***************************************************************************************
Function name: InitTheHungerGame
Input:  the pointer to the first Person on the list.
Output: None
The function operation: Intalize the game, asks the user for players and line them up in
a conected list.
****************************************************************************************/
void InitTheHungerGame(Person** first)
{
	Person* last = NULL;
	int flag;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &flag);
	if (flag == 0)
	{
		exit(1);
	}
	while (flag != 0 && flag != 1)
	{
		printf("no such option!\n");
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &flag);
		if (flag == 0)
		{
			exit(1);
		}
	}
	while (flag == 1)
	{
		Addplayers(&last, first);
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &flag);

		while (flag != 0 && flag != 1)
		{
			printf("no such option!\n");
			printf("Add a person to the game? 1 for yes, 0 for no\n");
			scanf("%d", &flag);
		}
	}


}

int main()
{
	Person* first = NULL; // a pointer to the first man.

	InitTheHungerGame(&first);
	LetTheGamesBegin(first);

	return 0;
}