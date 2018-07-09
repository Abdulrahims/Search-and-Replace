/*

Author: Abdul Rahim 
		Omar Abdeen

search_and_replace.c : overall goal of the program was to build a robust program that can 
				read a text file, search for a user queried word within that text file,
				and then replace the word with a user inputted replacement word. At the
				end, the program should save the text file with the new replacement 
				word, and count the number of replacements that took place. 		
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
 
//Rather arbritrary, but a large number should be satisfactory
int MAX_LENGTH = 1000;

//Also arbritary
int char_length = 256;

//The search and replace function is the main function that is used to search and replace
//the words inputted by the user
char *search_and_replace(char *text_string, char *search, char *replace){
    
    //A temparary char array for handiling the string later on
    char temp[MAX_LENGTH];
    
    //Used in this method only if there is a succesful replacement. Otherwise, unsuccessful
    //replacement handled in the main
    int num_replacements = 0;
    //char placeholder
    char *s;
     
    if(!(s = strstr(text_string, search))){
        return text_string;
    }
    
    //Use the strncpy() function to copy n characters from a string. Up to 
    //n = (p - the length of the string)
    //Destination: temp 
    //Source: text_string
    strncpy(temp, text_string, s - text_string);
    
    temp[s - text_string] = '\0';
     
    //Use sprintf to format the first part up to search word, the replacement word, and 
    //the length of the string together
    //This will result in the search word being removed, with the replacement word in 
    //its place
    sprintf(temp + (s - text_string), "%s %s", replace, s + strlen(search));
    
    //Increment replacements to 1, meaning a succesful replacement took place
    num_replacements = num_replacements + 1;
    printf("The number of succesful replacements is: %d \n", num_replacements);
    puts(temp);
    
    //Dynamic allocation was required to address error when function returns address of
    //local variable
    char* result = malloc(strlen(temp) + 1);
    
    return result;
}
 
//The main program where the program starts/enters 
int main(){
    
    //Reading in the text file    
    char text_as_string[MAX_LENGTH][MAX_LENGTH],buffer[MAX_LENGTH];
    FILE *file_in;
    file_in = fopen("test.txt", "r");
    
    //Store the text file as a string. fgets() reads the string from a file
    int i = 0;
    while(fgets(buffer,MAX_LENGTH,file_in)){
        strcpy(text_as_string[i],buffer);
        i++;
    }
    
    //The text file is in the first element of this array, but moving it to a string as 
    //to not have to deal with indices at any point
    char *txtstring = text_as_string[0];
    //The final string will be compiled in this variable
    char *final_string = NULL;
    
    printf("Welcome to the search and replace program! \n");
    
    if( access( "test.txt", F_OK ) != -1 ){
        printf("Text file found. \n");
    
        printf("This is the text file:\n");
        puts(txtstring);

        //Query the user for the word to be searced
        char input_search[char_length];
        printf("Input a word to search and replace:\n");
        scanf("%s",input_search);

        //If the word is not in the text file, do not continue the program
        while(!strstr(txtstring, input_search)){
            printf("This word is not in the text file! Please try again. \n");
            printf("Input a word to search and replace:\n");
            scanf("%s",input_search);

        }
        //Get the replacement word from the user
        char replacement[char_length];
        printf("Input the replacement word:\n");
        scanf(" %s",replacement);
    
        //Reprint both the query word and the replacement word
        printf("Input word: %s \n", input_search);
        printf("Replacement word: %s \n", replacement);

        //Call the search and replace method
        final_string = search_and_replace(txtstring, input_search, replacement);
    
        //If the string from the textfile and the final string are the same, then nothing
        //happened. No replacement occured
        if(strstr(final_string, txtstring)){
            printf("No succesful replacements \n");
        }  
    
        printf("%s", final_string);
    
        //save this to a text file
        fprintf(file_in,"%s",final_string);
        }
        else{
            printf("Text file not found.  \n");

    }
    //Close the text file
    fclose(file_in);

}
