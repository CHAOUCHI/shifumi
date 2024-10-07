#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string.h>

#define PORT 3000
#define ROCK 1
#define PAPER 2
#define SCISOR 3

/**
 * Test client for shifumi
 */

//-----------------------#
/**
 * Game states
 */
int player_one_hand = ROCK;
int player_two_hand = PAPER;
char player_one_name[50] = "Massinissa";
char player_two_name[50] = "Amazir";
//------------------------#
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
    int client = socket(AF_INET,SOCK_STREAM,0);
    perror("client socket creation.");

    struct sockaddr_in client_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(PORT)
    };
    bind(client,(struct sockaddr*)&client_addr,sizeof(client_addr));
    perror("Bind client to 127.0.0.1:3000");

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(3003),
        .sin_family = AF_INET
    };
    socklen_t server_len = sizeof(server_addr);
    connect(client,(struct sockaddr*)&server_addr,server_len);
    perror("Connect cleint to server");

    char buf[255];
    memset(buf,0,sizeof(buf));
    strcpy(buf,"PULL\nPLAYER_ONE_NAME str\nPLAYER_TWO_NAME str\nPLAYER_ONE_HAND 1\nPLAYER_TWO_HAND 2\n");

    send(client,buf,strlen(buf),0);
    perror("Send data to server");

    return 0;
}