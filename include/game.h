#ifndef GAME_H
#define GAME_H

typedef enum {
    FOREST,
    HILLS,
    PASTURE,
    FIELDS,
    MOUNTAINS,
    DESERT
} Terrain;

typedef enum {
    BUILDING_NONE,
    BUILDING_SETTLEMENT,
    BUILDING_CITY
} BuildingType;

typedef struct {
    Terrain terrain;
    int number;
    int edge_ids[6];
} Hex;

typedef struct{
    int owner;
    int vertex_ids[2]; 
} Edge;

typedef struct{
    int owner;
    BuildingType building;
    int hex_ids[3];
} Vertex;

typedef struct {
    Hex hexes[19];
    Edge edges[72];
    Vertex vertices[54];
    int robber_hex_id;
} GameState;

void game_init(GameState *state);

int move_robber(GameState *state, int hex_id);

int build_road(GameState *state, int edge_id, int player_id);

int build_settlement(GameState *state, int vertex_id, int player_id);

int upgrade_settelment(GameState *state, int vertex_id, int player_id);

int count_building_points(const GameState *state, int player_id);

int count_roads(const GameState *state, int player_id);

int count_buildings(const GameState *state, int player_id, BuildingType type);

#endif