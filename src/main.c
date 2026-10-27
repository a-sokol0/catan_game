#include <stdio.h>
#include "game.h"


int main(void){

    GameState game;

    game_init(&game);

    int success = move_robber(&game, 1 );

    printf("Move result: %d\n", success);
    printf("Robber hex: %d\n", game.robber_hex_id);

    int create_road = build_road(&game, 1, 0);
    
    printf("Owner of edge: %d\n", game.edges[1].owner);


    return 0;

}
