#include <stdio.h>
#include <stdlib.h>

#define ROCK 1
#define PAPER 2
#define SCISOR 3

#define ONE_WIN -1
#define NONE_WIN 0
#define TWO_WIN 1

int is_valid_hand(int hand);
int get_hand(char* player_name);
int wich_hand_won(int hand_one,int hand_two);

int main(){
    /**
     * Defining players names
     */
    char* player_one = "Massinissa";
    char* player_two = "Amazir";

    printf("\n---------------------- ShiFuMi ! --------------------\n");

    int hand_one = get_hand(player_one);
    int hand_two = get_hand(player_two);

    //Compare two hands
    int who_won = wich_hand_won(hand_one,hand_two);
    switch (who_won)
    {
    case ONE_WIN:
        printf("%s à gagné !\n",player_one);
        break;
    case TWO_WIN:
        printf("%s à gagné !\n",player_two);
        /* code */
        break;
    case NONE_WIN:
        printf("EGALITE !\n");
        /* code */
        break;
    
    default:
        printf("error while deciding wich player won.");
        break;
    }
    printf("\n---------------------- GAME OVER ! --------------------\n");
    return 0;
}

int is_valid_hand(int hand){
    return hand == ROCK || hand == PAPER || hand == SCISOR;
}

int get_hand(char* player_name){
    int hand = -1;
    while (!is_valid_hand(hand)){
        // one choose hand
        printf("%s ?\n 1.pierre\n2.feuille\n3.iso\n",player_name);
        char buf[3];
        fgets(buf,3,stdin);
        hand = atoi(buf);
    }
    return hand;
}

/**
 * @return -1 : first | hand 0 : none | 1 : second hand
 */
int wich_hand_won(int hand_one,int hand_two){
    if(hand_one == hand_two){
        return NONE_WIN;
    }
    switch (hand_one)
    {
    case ROCK:

        switch (hand_two)
        {
        case PAPER:
            return TWO_WIN;
            break;
        case SCISOR:
            return ONE_WIN;
            break;
        }
        
        break;
    case PAPER:
        switch (hand_two)
        {
        case ROCK:
            return ONE_WIN;
            break;
        case SCISOR:
            return TWO_WIN;
            break;
        }
        break;
    case SCISOR:
        switch (hand_two)
        {
        case PAPER:
            return ONE_WIN;
            break;
        case ROCK:
            return TWO_WIN;
            break;
        }
        break;
    
    default:
        break;
    }
}