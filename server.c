#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3003
#define ROCK 1
#define PAPER 2
#define SCISOR 3


/**
 * Server for shifumi
 */

//-----------------------#
/**
 * Game states
 */
typedef  struct s_states{
    int player_one_hand;
    int player_two_hand;
    char player_one_name[50];
    char player_two_name[50];
} t_states;
t_states states;
//------------------------#
int compile_sfmp(char* sfmp_msg,char event[5],t_states* states);

/* 
# Protocole SFMP (ShiFuMi Protocole)

## Syntaxe :

```
EVENT player_name
PLAYER_ONE_NAME str
PLAYER_TWO_NAME str
PLAYER_ONE_HAND value
PLAYER_TWO_HAND value
```

--------------------------

### Syntaxe PULL event :
The pull event send all states to client

PULL
PLAYER_ONE_NAME str
PLAYER_TWO_NAME str
PLAYER_ONE_HAND 1
PLAYER_TWO_HAND 2

### Syntaxe PUSH event :
The push event send hand of a client to server

PUSH
PLAYER_NAME str
PLAYER_HAND value

### Syntaxe AUTH event :
The auth event add a player to the game and set he's name.

AUTH
PLAYER_NAME str
*/
int main(){
    int server = socket(AF_INET,SOCK_STREAM,0);
    perror("Server socket creation.");

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(PORT)
    };
    bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr));
    perror("Bind server to 127.0.0.1:3003");
    
    listen(server,10);
    perror("Server listen on 127.0.0.1:3003");
    printf("\n --- Server ready ----\n");
    struct sockaddr_in client_addr;
    socklen_t client_len;
    int client = accept(server,(struct sockaddr*)&client_addr,&client_len);
    perror("Server accept data from client");
    while(1){
        char sfmp_msg[255];
        memset(sfmp_msg,0,sizeof(sfmp_msg));
        recv(client,sfmp_msg,sizeof(sfmp_msg),0);
        if(strlen(sfmp_msg) > 0){
            printf("%s\n",sfmp_msg);
            char event[10];
            compile_sfmp(sfmp_msg,event,&states);
            printf("event : %s\n",event);
            memset(event,0,sizeof(event));
        }
    }

    return 0;
}

int compile_sfmp(char* sfmp_msg,char* event,t_states* states){
    int line_counter = 1;
    for (int i = 0; i < strlen(sfmp_msg); i++)
    {
        if(sfmp_msg[i] == '\n'){
            

            if(line_counter == 1){
                // event line
                for (int j = 0; j < i; j++)
                {
                    event[j] = sfmp_msg[j];
                }
                event[i] = '\0';                    
            }
            if(line_counter > 1){
                // state line
                char state_line_name[100];
                memset(state_line_name,0,sizeof(state_line_name));
                char state_line_value[100];
                memset(state_line_value,0,sizeof(state_line_value));

                // Extract state line name
                int index_name = 0;
                int cursor_line = i+1;
                while(sfmp_msg[cursor_line] != ' '){
                    state_line_name[index_name] = sfmp_msg[cursor_line];
                    index_name++;
                    cursor_line++;
                }
                // Extract state line value
                // cursor line is on the SPACE ' ' char.
                // I have to go by 1 postion to get the first char of the value
                cursor_line++;
                int index_value = 0;
                while(sfmp_msg[cursor_line] != '\n'){
                    state_line_value[index_value] = sfmp_msg[cursor_line];
                    cursor_line++;
                    index_value++;
                }
                
            }
            line_counter++;
        }
    }
    return 0;
}