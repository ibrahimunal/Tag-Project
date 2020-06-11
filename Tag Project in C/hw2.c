#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "myStruct.h"
typedef struct {
    char *id;
    char *userNote;//user can enter 100 lines of note
    char *tag;
} note;

int andCase(char tag[], char* bool);
int orCase(char tag[], char* bool);
int notCase(char tag[], char* bool);
int subExpression(char check[], char newString[]);
int splitCommand(char *input, char delim, char *seperateArr[]){

int counter=0;
        char *tempArr = malloc(sizeof(char) * strlen(input));

        if (input != NULL)
        {
                char *token;
                strcpy(tempArr, input);
                token = strtok(tempArr, &delim);
                seperateArr[counter] = malloc(sizeof(char) * strlen(token));
                strcpy(seperateArr[counter], token);
                counter++;
                while (token != NULL)
                {
                        token = strtok(NULL, &delim);
                        if (token == NULL)
                        {

                                break;
                        }
                        seperateArr[counter] = malloc(sizeof(char) * strlen(token));
                        strcpy(seperateArr[counter], token);
                        counter++;
                }
                return counter;
        }
}


int main(int argc, char* argv[]){
  char input[50];
  int noteCounter=0;
  char command[50];
  char *inputptr=malloc(sizeof(char)*500);
  //inputptr = input;
  char *seperatedCommands[1000];

  int numOfcommands;
  note *noteList[100];
  char *pos;


    while(fgets(inputptr,500,stdin)) {
   if ((pos=strchr(inputptr, '\n')) != NULL)
    *pos = '\0';
  int numOfcommands=splitCommand(inputptr,' ',seperatedCommands);
    if(strcmp(seperatedCommands[0],"ADD")==0){
        //ADD COMMAND
        char *tempInput;
        //tempNote.userNote=malloc(sizeof(char)*500);
        //gets(tempNote.userNote);
        char *newLine;
        tempInput=(char *)malloc(sizeof(char)*500);
        fgets(tempInput,500,stdin);

        while(strcmp(tempInput,"END")!=0){
            newLine=(char *)malloc(sizeof(char)*500);
            fgets(newLine,500,stdin);

            if(strcmp(newLine,"END\n")==0){
            //printf("YAYY i found the end its time to quit \n");
            //printf("%s", tempInput);
            break;
            }
            tempInput=realloc(tempInput,sizeof(char)*(strlen(tempInput)+strlen(newLine)+1));
            strcat(tempInput,newLine);



        }

        noteList[noteCounter] = malloc(sizeof(note));
        noteList[noteCounter]->id = malloc(sizeof(char)*3);
        noteList[noteCounter]->tag = malloc(sizeof(char)*10);
        strcpy(noteList[noteCounter]->id,seperatedCommands[1]);
        noteList[noteCounter]->userNote = malloc(strlen(tempInput)+1);
        strcpy(noteList[noteCounter]->userNote,tempInput);
        //printf("my note is %s\n iput is  %s\n",noteList[addCounter]->userNote,tempInput);
        noteCounter++;
       /* for(int i=0; i<noteCounter; i++){
            printf("%s st note's note is %s\n",noteList[i]->id,noteList[i]->userNote);
        } */

    }else if(strcmp(seperatedCommands[0],"TAG")==0){
    //printf("Im in thee tag");
        //printf("%s:",seperatedCommands[numOfcommands-1]);
        if(strcmp(seperatedCommands[numOfcommands-1],"-1")!=0){
        //printf("Your last input should be -1 Please enter your TAG command again..\n");
        }
        else{
        for(int i=2; i<numOfcommands-1; i++){
        for(int k=0; k<noteCounter; k++){
            if(strcmp(seperatedCommands[i],noteList[k]->id)==0){
            //   printf("i found the struct!! and u want to add keyword %s\n",seperatedCommands[1]);
               noteList[k]->tag=realloc(noteList[k]->tag,sizeof(char)*(strlen(noteList[k]->tag)+strlen(seperatedCommands[1])));
               strcat(noteList[k]->tag,seperatedCommands[1]);
               strcat(noteList[k]->tag," ");
             }
           }
        }
      //printf("tags of the note are %s:\n",noteList[0]->tag);

    }

    }
    else if(strcmp(seperatedCommands[0],"DISPLAY")==0){
       for(int k=0; k<noteCounter; k++){
            if(strcmp(seperatedCommands[1],noteList[k]->id)==0){
               printf("Id: %s\n",noteList[k]->id);
               printf("%s",noteList[k]->userNote);

             }

           }
    }else if(strcmp(seperatedCommands[0],"FIND")==0){

    int match;
    note* matches[1000];
    int found = 0;

    for(int i=0; i<noteCounter; i++){

    if (inputptr[5] == 'A' && inputptr[6] == 'N' && inputptr[7] == 'D' )
     match = andCase(noteList[i]->tag, &inputptr[5]);
     else if (inputptr[5] == 'N' && inputptr[6] == 'O' && inputptr[7] == 'T' )
     match = notCase(noteList[i]->tag, &inputptr[5]);
     else if (inputptr[5] == 'O' && inputptr[6] == 'R')
     match = orCase(noteList[i]->tag, &inputptr[5]);
     //printf("finding id: %s tag: %s result: %d\n",noteList[i]->id,noteList[i]->tag, match);
    if(match==1){
    printf("Results:\n");
    printf("Id: %s %s",noteList[i]->id,noteList[i]->userNote);
    matches[++found]= noteList[i];

    }
    }

}

else{

    printf("Undefined command please enter your command again..!\n");
    }


}
  return 0;

}


int subExpression(char check[], char newString[]){
    int control = 0;
    for (int i = 0; i < strlen(check); i++)
    {
        if (check[i] == '(')
            control++;
        if (check[i] == ')')
            control--;
        newString[i] = check[i];
        if (control == 0 && i > 3){
            check[i+1] = '\0';
            break;
        }
    }
}

int andCase(char tag[], char* bool){
    char* parts;
    bool = bool +5;
    int control = 1;
    while (strlen(bool)> 1) {
            if (parts == NULL)
                parts = malloc(strlen(bool));
            if (bool[0] == 'A' && bool[1] == 'N' && bool[2] == 'D' && bool[3] == '(')
            {
                subExpression(bool, parts);
                bool += strlen(parts) + 1;
                control = control * andCase(tag, parts);
            }
            else if (bool[0] == 'N' && bool[1] == 'O' && bool[2] == 'T' && bool[3] == '(')
            {
                subExpression(bool, parts);
                bool += strlen(bool) + 1;
                control = control * notCase(tag, parts);
            }
            else if (bool[0] == 'O' && bool[1] == 'R' && bool[2] == '(') {

                subExpression(bool, parts);
                 bool += strlen(parts) + 1;
                control =  control * orCase(tag, parts);
            }

            else
            {
                char* strCopy;
                strCopy = malloc(strlen(bool));
                strcpy(strCopy, bool);
                parts = strtok(strCopy, " ");
                bool += strlen(parts) + 1;
                if (strstr(tag, parts)==NULL)
                    control = 0;
            }
        }
        return control;

}
int orCase(char tag[], char* bool){
    char* parts;
    bool = bool +4;
    int control = 0;
    while (strlen(bool) > 1)
        {
            if (parts == NULL)
            {
                parts = malloc(strlen(bool));
            }
            if (bool[0] == 'A' && bool[1] == 'N' && bool[2] == 'D' && bool[3] == '(')
            {
                subExpression(bool, parts);
                bool +=strlen(parts) + 1;
                control = control + andCase(tag, parts);
            }
            else if (bool[0] == 'N' && bool[1] == 'O' && bool[2] == 'T' && bool[3] == '(')
            {
                subExpression(bool, parts);
                bool += strlen(parts) + 1;
                control += notCase(tag, parts);
            }
            else if (bool[0] == 'O' && bool[1] == 'R' && bool[2] == '(')
            {
                subExpression(bool, parts);
                bool +=  strlen(bool) + 1;
                control += orCase(tag, parts);
            }
            else
            {
               char* strCopy = malloc(strlen(bool));
                strcpy(strCopy, bool);
                parts = strtok(strCopy, " ");
                bool +=  strlen(parts) + 1;
                if (strstr(tag, parts) != NULL)
                    control+= 1;
            }
        }
            if(control > 0)
            return 1;
            else
            return 0;
}
int notCase(char tag[], char* bool){
    char* parts;
    int control = 1;
    bool = bool +5;
    while (strlen(bool) > 1)
        {
            if (parts == NULL)
                parts = malloc(strlen(bool));

            if (bool[0] == 'A' && bool[1] == 'N' && bool[2] == 'D' && bool[3] == '(')
            {
                subExpression(bool, parts);
                bool += strlen(parts) + 1;
                control = andCase(tag, parts);
            }
            else if (bool[0] == 'N' && bool[1] == 'O' && bool[2] == 'T' && bool[3] == '(')
            {
                subExpression(bool, parts);
                bool += strlen(parts) + 1;
                control = notCase(tag, parts);
            }
            else if (bool[0] == 'O' && bool[1] == 'R' && bool[2] == '(')
            {
                subExpression(bool, parts);
                bool += strlen(parts) + 1;
                control = orCase(tag, parts);
            }
            else
            {
                char* strCopy = malloc(strlen(bool));
                strcpy(strCopy, bool);
                parts = strtok(strCopy, " ");
                bool += strlen(parts) + 1;
                if (strstr(tag, parts) == NULL)
                    control = 1;

            }
        }
        if (control == 0)
            control = 1;
        else
            control = 0;
    return control;
}
