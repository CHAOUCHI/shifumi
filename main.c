#include <stdio.h>
#include <stdlib.h>

#define ROCK 1
#define PAPER 2
#define SCISOR 3

#define ONE_WIN -1
#define NONE_WIN 0
#define TWO_WIN 1

// Define functions signatures.
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

    /*
    * Ask both players to choose a hand.
    */
    int hand_one = get_hand(player_one);
    int hand_two = get_hand(player_two);

    /**
     * Compute who is the winning hand...
     */
    int who_won = wich_hand_won(hand_one,hand_two);
    switch (who_won)
    {
    case ONE_WIN:
        // Player one wins.
        printf("%s à gagné !\n",player_one);
        break;
    case TWO_WIN:
        // Player two wins.
        printf("%s à gagné !\n",player_two);
        break;
    case NONE_WIN:
        // Nobody two wins.
        printf("EGALITE !\n");
        break;
    
    default:
        printf("error while deciding wich player won.");
        break;
    }
    printf("\n---------------------- GAME OVER ! --------------------\n");
    return 0;
}

/**
 * Test if a hand is a valid hand or an error.
 * Valid hands are the following constants
 * 1 - ROCK
 * 2 - PAPER
 * 3 - SCISOR
 * 
 * @return 1 if the hand is valid or 0 if none.
 * 
 */
int is_valid_hand(int hand){
    return hand == ROCK || hand == PAPER || hand == SCISOR;
}

/**
 * Ask the player to choose a hand to play and return the response.
 * If the hand is not a valid hand, ask again until the response is valid (see is_valid_hand() function)
 */
int get_hand(char* player_name){
    int hand = ROCK-PAPER-SCISOR; // Affect a wrong value.
    while (!is_valid_hand(hand)){
        printf("%s ?\n 1.pierre\n2.feuille\n3.iso\n",player_name);
        char player_input[3];
        memset(player_input,0,sizof(player_input)); // Initialize all array values to 0
        fgets(player_input,sizeof(player_input),stdin);
        hand = atoi(player_input);
    }
    return hand;
}

/**
 * Define wich hand won from the two hands passed as arguments
 * @return constants ONE_WIN(-1), TWO_WIN(1) or NONE_WIN(0)
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
            
            default:
                printf("Error in wich_hand_won default switch case reach");
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
            
            default:
                printf("Error in wich_hand_won default switch case reach");
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
            
            default:
                printf("Error in wich_hand_won default switch case reach");
            break;
            }
        break;

        default:
            printf("Error in wich_hand_won default switch case reach");
        break;
    }
    return -2;
}