#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>

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
float aleatoire(float from, float to);
char* handtostr(int hand);

char* handtostr(int hand){
    switch (hand)
    {
    case PAPER:
        return "Papier";
        break;
    
    case ROCK:
        return "Pierre";
        break;

    case SCISOR:
        return "SCISOR";
        break;
    default:
        return "";
        break;
    }
}
int main(int argc,char**argv){
    /**
     * Defining players names
     */
    char* player_one;
    char* player_two;
    // Si les nom des 2 joueurs sont donnés
    if(argc > 2){
        player_one = argv[1];
        player_two = argv[2];
    }else{
        player_one = "Massinissa";
        player_two = "Amazir";
    }
    

    printf("\n---------------------- ShiFuMi ! --------------------\n");
    printf("\n%s Vs %s !\n",player_one,player_two);
    printf("\n-----------------------------------------------------\n");

    while(1){
        /*
        * Ask both players to choose a hand.
        */
        int hand_one = get_hand(player_one);
        int hand_two = get_hand(player_two);
        printf("%s à fait %s\n",player_one,handtostr(hand_one));
        printf("%s à fait %s\n",player_two,handtostr(hand_two));
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
    }
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
    // test if player_name == IA
    if(strcmp(player_name,"IA") == 0){
        // randomise hand
        hand = (int)aleatoire(ROCK,SCISOR);
    }

    while (!is_valid_hand(hand)){
        printf("%s ?\n 1.pierre\n2.feuille\n3.iso\n",player_name);
        char player_input[3];
        memset(player_input,0,sizeof(player_input)); // Initialize all array values to 0
        fgets(player_input,sizeof(player_input),stdin);
        hand = atoi(player_input);
    }
    return hand;
}
/**
 * Generating a random value between from and to
 * @dependecies : stdlib.h, sys/random.h
 */
float aleatoire(float from, float to){
    // Generating a random buf of bytes
    int buf[255];
    getentropy(buf,sizeof(buf));
    
    // Generating a random seed with the sum of all random bytes.
    int seed = 0;
    for (int i = 0; i < sizeof(buf); i++)
    {
        seed+=buf[i];
    }
    // Give the seed to srand
    srand(seed);
    // Generating random value
    int valeur_random = rand();

    return (to-from)*((float)valeur_random/RAND_MAX)+from;
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