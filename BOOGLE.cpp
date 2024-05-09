//MUHAMMAD DHITAN IMAM SAKTI
//2702367183
//AOL DATA STRUCTURE

#include <stdio.h> //standard input output
#include <stdlib.h> //for malloc
#include <string.h> //for strlen and other string related functions

struct trie { //declaring a struct called trie
	int finalChar; //it would either be 0 or 1, to find the end of a string for example Cat, t is the finalChar
	struct trie* children[256]; //where to find the node for that particular character, NULL if theres no character
	char occupant; //occupant of the root
	char description[512]; //description
};

struct trie* create_trie(char occupant){ //function to create a new node inside the trie
	struct trie* makeaTrie = (struct trie*)malloc(sizeof(struct trie)); //creates a new node in the trie
	for(int i = 0; i < 256; i++){
		makeaTrie->children[i] = NULL; //for loop to make every children NULL
	}
	makeaTrie->finalChar = 0; //set the finalChar to be false
	makeaTrie->occupant = occupant; //set the occupant to basically create a root, can be anything im using $ cause its cool
	makeaTrie->description[0] = '\0'; //set the description string to initially be the null terminator
	return makeaTrie; //return the trie
}

void menu(){ //Void function for the menu, its just a bunch of printf functions :)
	printf("Welcome to Boogle!!!\n");
	printf("Here is our features\n");
	printf("1. Release a new Slang Word\n");
	printf("2. Search a Slang Word\n");
	printf("3. View all Slang Words starting with a certain prefix word\n");
	printf("4. View all Slang Words\n");
	printf("5. Exit\n");
}

//SEPERATOR function to count each words in the string
int seperator(char desc[]){
	int wordCounter = 0; //initialize counter for a word to 0
	int i = 0; //initialize iteration counter to 0
	int length = strlen(desc); //find the length of the desc string with strlen
	while(i < length && desc[i] == ' '){ //while loop to skip the leading spaces
		i++;
	}	
	while(i < length){ //iterates until i is less than the length of the string
		if(desc[i] != ' ' && (i == 0 || desc[i - 1] == ' ')){ 
			wordCounter++; //adds 1 to the word counter if current character with index i 
			//is not a space and previous character is a space or the start of the string (index 0)
		}
		i++; //continues iteration
	}
	return wordCounter; //return the number of words counted
}

int insertSlang(struct trie** root, char slangWord[], char desc[]){ //function to insert slang word, double pointer because it changes inside the function
	if(*root == NULL){
		*root = create_trie('$'); //if the root is NULL, it creates a trie with the topmost (root) being $
	}
	struct trie* temp = *root; //temporary variable to store the root
	for(int i = 0; slangWord[i] != '\0'; i++){
		if(temp->children[slangWord[i]] == NULL){
			temp->children[slangWord[i]] = create_trie(slangWord[i]);
		}
		temp = temp->children[slangWord[i]];
	}
	if(temp->finalChar){
		strcpy(temp->description, desc);
//        printf("Updated description of slang word: %s\n", slangWord); (only for debugging)
//        printf("New Description: %s\n", temp->description); (only for debugging)
		return 0;
	}
	strcpy(temp->description, desc);
	temp->finalChar = 1;
//	printf("Inserted slang word: %s\n", slangWord); (only for debugging)
//  printf("Description: %s\n", temp->description); (only for debugging)
    
	return 1;	
}

//function for the first option or feature
void releaseNewSlang(struct trie** root){
	char slangWord[256]; //slangWord variable
	char desc[256]; //desc variable
	char destiny; //destiny variable whether the user wants to continue adding or not
	do {
		int valid = 0; //valid flag, initially set to 0
		while(!valid){ //while loop
			printf("Enter a new Slang Word [Must be more than 1 characters and contains no space]: ");
			scanf(" %[^\n]", slangWord); //input for the slang word
			int length = strlen(slangWord); //strlen to find the length of the slang word
			if(length > 1 && strchr(slangWord, ' ') == NULL){ //length is more than 1 characters and there is no space
				valid = 1; //set the flag to 1 to exit the loop, slang word has been validated
			} else {
				valid = 0; //set the flag to 0 to continue the loop (asking for a new slang word)
			}
		}
		int valid2 = 0; //valid flag for the desc, initially set to 0
		while(!valid2){
			printf("Enter a new Slang Word Description [Must be more than 2 words]: ");
        	scanf(" %[^\n]", desc);  // input for the slang word description with spaces
			int counter = seperator(desc); //calls the seperator function and store the value it returns to counter
//			printf("word counter: %d\n", counter); (debugging purposes)
			if(counter > 2){
				valid2 = 1; //set the flag to 1 exiting the loop, same as above :)
			} else {
				valid2 = 0; //set the flag to 0 continuing the loop, same as above :)
			}
		}
		
		//STRTOK CANNOT BE USED HERE BECAUSE THE SPACES IN THE STRING WOULD BE REPLACED WITH '\0' 
		//AND THEREFORE CANNOT BE PRINTED NOR UPDATED :D
		
		//insertSlang function called to actually insert the slang word
		int hasBeenInserted = insertSlang(root, slangWord, desc); 

        printf("\n"); //newline for aestethic purposes
        //simple if else according to the value returned by the insertSlang function stored in hasBeenInserted variable
        if(hasBeenInserted){
			printf("Successfully released a new Slang Word!\n");
		} else {
			printf("Successfully updated the description of the given Slang Word!\n");
		}
		//well i personally kinda like this one more than press enter to continue so yea :)
		printf("Do you wish to continue? (y/n) ");
		scanf(" %c", &destiny);
		getchar();
		
		//both clears the screen for aestethic purposes
		if(destiny == 'y'){
			system("cls");
		} else {
			system("cls");
		}
		
	} while(destiny != 'n'); //continues the loop as long as the user doesnt input n for the destiny
}

struct trie* searchSlang();

struct trie* searchSlangPrefix();

//THIS FUNCTION IS ONLY FOR DEBUGGING PURPOSES 
void printWithDescRec(struct trie* root, char* temp, int depth, char desc[], int* numberOfSlangs){
	if(root->finalChar){
		temp[depth] = '\0'; 
		printf("%d. %s: %s\n", (*numberOfSlangs), temp, desc);
		(*numberOfSlangs)++;
	}
	for(int i = 0; i < 256; i++){
		if(root->children[i] != NULL){
			temp[depth] = i;
			printWithDescRec(root->children[i], temp, depth + 1, root->children[i]->description, numberOfSlangs);
		}
	}
}

//THIS FUNCTION IS ONLY FOR DEBUGGING PURPOSES 
void printWithDesc(struct trie* root){
	char destiny;
	printf("List of all Slang Words available in the Dictionary: \n");
	char temp[256]; //temp declaration
	int numberOfSlangs = 1; //number starts at 1
	
	printWithDescRec(root, temp, 0, root->description, &numberOfSlangs); //recursive printing function called
	
	printf("Do you wish to continue? (y/n) ");
	scanf(" %c", &destiny);
	getchar();
	
	if(destiny == 'y'){
		system("cls");
	} else {
		system("cls");
	}
}

//print all slang recursive function, the ones with pointers are constantly changing
void printAllSlangRec(struct trie* root, char* temp, int depth, int* numberOfSlangs){
	if(root == NULL){
		printf("Dictionary is empty\n"); //if the root is null then the dictionary is empty
		return; //return
	}
	if(root->finalChar){ //if the root
		temp[depth] = '\0'; 
		printf("%d. %s\n", (*numberOfSlangs), temp);
		(*numberOfSlangs)++;
	}
	for(int i = 0; i < 256; i++){
		if(root->children[i] != NULL){
			temp[depth] = i;
			printAllSlangRec(root->children[i], temp, depth + 1, numberOfSlangs);
		}
	}
}

void printAllSlang(struct trie* root){
	if(root != NULL){
		printf("List of all Slang Words available in the Dictionary: \n");	
	}
	
	char destiny;
	char temp[256]; //temp declaration
	int numberOfSlangs = 1; //number starts at 1
	
	printAllSlangRec(root, temp, 0, &numberOfSlangs); //recursive printing function called
	
	printf("Do you wish to continue? (y/n) ");
	scanf(" %c", &destiny);
	getchar();
	
	if(destiny == 'y'){
		system("cls");
	} else {
		system("cls");
	}
}

int main (){
	int input; //get input from the user
	struct trie* root = NULL; //root set to NULL at the start
	char choice; //choice
	do {
		menu(); //menu function called to be displayed on the screen
		printf("Your Choice: "); //asks for the choice
		scanf("%d", &input); //gets input for the choice
		getchar(); //eliminates newline	
		switch(input){ //start of switch case
			case 1: //if the user chooses 1
				system("cls");
				releaseNewSlang(&root);
				break;
			case 2: //if the user chooses 2
				system("cls");
				break;
			case 3: //if the user chooses 3
				system("cls");
				break;
			case 4: //if the user chooses 4
				system("cls");
				printAllSlang(root);
				break;
			case 5: //if the user chooses to exit the program
				system("cls");
				printf("Thank you for using BOOGLE!!!");
				break;
			default:
                printf("Invalid choice! Please choose a valid option.\n"); //default message
                break;
            if(input != 5) {
        		printf("Do you wish to continue using the program? (y/n): "); //equivalent to a press enter to continue
        		scanf(" %c", &choice); //gets input whether the user wants to continue or not
        		if(choice == 'y'){
            		system("cls"); //resets the screen
        		}
        	}
		}
	} while(input != 5);	
	return 0;
}
