#include "game.h"

void game_init(GameState *state){
       
    *state = (GameState){0};

    state->robber_hex_id = -1;

    for (int i = 0; i < 72; i++) {
        state->edges[i].owner = -1;
        state->edges[i].vertex_ids[0] = -1;
        state->edges[i].vertex_ids[1] = -1;
    }
    
    for (int i = 0; i < 54; i++) {
        state->vertices[i].owner = -1;
        state->vertices[i].building = BUILDING_NONE;
        for (int j = 0; j < 3; j++) {
        state->vertices[i].hex_ids[j] = -1;
        }
    }

    for (int i = 0; i < 19; i++) {
        state->hexes[i].number = 0;
        state->hexes[i].terrain = DESERT;
        for (int j = 0; j < 6; j++) {
            state->hexes[i].edge_ids[j] = -1;
        }
    }

}

int move_robber(GameState *state, int hex_id){
    if (hex_id < 0 || hex_id >= 19) {
        return 0;
    }

    state->robber_hex_id = hex_id;
    return 1;
}

int build_road(GameState *state, int edge_id, int player_id){

    if(edge_id < 0 || edge_id >= 72){
        return 0;
    }

    if(player_id < 0 || player_id >=4){
        return 0;
    }

    if(state->edges[edge_id].owner != -1){
        return 0;
    }
    
    if (count_roads(state, player_id) >= 15) {
        return 0;
    }

    state->edges[edge_id].owner = player_id;
    return 1;
}
int build_settlement(GameState *state, int vertex_id, int player_id){
 
    if (count_buildings(state, player_id, BUILDING_SETTLEMENT) >= 5) {
        return 0;
    }
    if (vertex_id < 0 || vertex_id >= 54) {
        return 0;
    }

    if (player_id < 0 || player_id >= 4) {
        return 0;
    }

    if (state->vertices[vertex_id].building != BUILDING_NONE) {
        return 0;
    }

    state->vertices[vertex_id].owner = player_id;
    state->vertices[vertex_id].building = BUILDING_SETTLEMENT;

    return 1;
}
int upgrade_settelment(GameState *state, int vertex_id, int player_id){

    if (count_buildings(state, player_id, BUILDING_CITY) >= 4) {
        return 0;
    }    
    
    if (vertex_id < 0 || vertex_id >= 54) {
        return 0;
    }

    if (player_id < 0 || player_id >= 4 || player_id != state->vertices[vertex_id].owner) {
        return 0;
    }

    if (state->vertices[vertex_id].building != BUILDING_SETTLEMENT) {
        return 0;
    }

    state->vertices[vertex_id].building = BUILDING_CITY;
    return 1;
}

int count_building_points(const GameState *state, int player_id)
{
    if (player_id < 0 || player_id >= 4) {
        return -1;
    }

    int points = 0;

    for (int i = 0; i < 54; i++) {
        if (state->vertices[i].owner != player_id) {
            continue;
        }

        if (state->vertices[i].building == BUILDING_SETTLEMENT) {
            points += 1;
        } else if (state->vertices[i].building == BUILDING_CITY) {
            points += 2;
        }
    }

    return points;

}
int count_roads(const GameState *state, int player_id){

    if (player_id < 0 || player_id >= 4) {
        return -1;
    }

    int road_counter = 0;

    for (int i = 0; i < 72; i++) {
        if(state->edges[i].owner != player_id){
            continue;
        }

        road_counter += 1;
    }
    return road_counter;
}

int count_buildings(const GameState *state, int player_id, BuildingType type){

    int building_counter = 0;

    if (player_id < 0 || player_id >= 4) {
        return -1;
    }

    if (type != BUILDING_SETTLEMENT && type != BUILDING_CITY) {
        return -1;
    }

    for (int i = 0; i < 54; i++) {
        if (state->vertices[i].owner == player_id && state->vertices[i].building == type) {
            building_counter += 1;
        }
    }
    return building_counter;
}