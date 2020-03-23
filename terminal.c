#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>                                                                    // Biblioteca para tolower em string sem warning

#include <dirent.h>                                                                   // Biblioteca para listagem de arquivo
#include <unistd.h>                                                                   // Biblioteca para receber hostname
#include <time.h>                                                                     // Biblioteca para comandos usando time


void clear(){
    printf("\033[H\033[J");
}

void limpa(){
    setbuf(stdin, NULL);
}

int main(){
    char command[100];
    char *user = getenv("USER");
    char hostname[1024];
    gethostname(hostname, 1024);


    while(1){
        char *currentPath = getenv("HOME");
        printf("%s@%s:%s$ ", user, hostname, currentPath);
        scanf("%[^\n]", command);                                                     // Ler comando do teclado
        limpa();
        for(int i = 0; i < strlen(command); i++){
            command[i] = tolower(command[i]);
        }

        if(strcmp(command, "help") == 0){
            printf("DevTerminal, version 0.1\nDeveloped by Gabriel Bernardi\n");
        }
        else if(strcmp(command, "cls") == 0){                                         // Limpa tela                  
            clear();
        }
        else if(strcmp(command, "dir") == 0){                                         // Lista diretorios, similar ao ls
            struct dirent *de;
            DIR *dr = opendir(".");
            if (dr == NULL){
                printf("Nao foi possivel abrir o diretorio\n");
                break;
            }else{
                while((de = readdir(dr)) != NULL){
                    printf("%s\n", de->d_name);
                }
                closedir(dr);
            }
        }
        else if(strcmp(command, "date") == 0){
            time_t t = time(NULL);
            struct tm actualDate = *localtime(&t);
            printf("%d/%02d/%02d\n", actualDate.tm_mday, actualDate.tm_mon + 1, actualDate.tm_year + 1900);
        }else if(strcmp(command, "time") == 0){
            time_t t = time(NULL);
            struct tm actualTime = *localtime(&t);
            printf("%02d:%02d:%02d\n", actualTime.tm_hour, actualTime.tm_min, actualTime.tm_sec);
        }
        else if(strcmp(command, "exit") == 0){                                        // Exit no shell
            printf("%s\n", command);
            break;
        }else{                                                                        // Retorno de erro se comando digitado nao for encontrado
            printf("%s: ", command);
            printf("Command not found\n");
        }
    }
}