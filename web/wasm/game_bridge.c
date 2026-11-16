#include <string.h>
#include "player.h"
#include "graph.h"
#include "inventory.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define API EMSCRIPTEN_KEEPALIVE
#else
#define API
#endif

static Player player;
static Graph dungeon;
static int initialized = 0;
static int enemy_health = 0;
static int enemy_attack = 0;

static void enter_room(int id) {
    if (id == 1 && dungeon.rooms[1].hasItem) {
        addItem(&player.inventory, "Sword", ITEM_WEAPON, 50);
        player.attack += 50;
        dungeon.rooms[1].hasItem = 0;
    } else if (id == 4 && dungeon.rooms[4].hasItem) {
        addItem(&player.inventory, "Health Potion", ITEM_POTION, 50);
        dungeon.rooms[4].hasItem = 0;
    } else if (id == 6 && dungeon.rooms[6].hasItem) {
        addItem(&player.inventory, "Dungeon Key", ITEM_KEY, 0);
        addItem(&player.inventory, "Gold Treasure", ITEM_TREASURE, 100);
        player.hasKey = 1;
        player.score += 250;
        dungeon.rooms[6].hasItem = 0;
    }
}

API void wasm_init(void) {
    if (initialized) { freePlayer(&player); freeGraph(&dungeon); }
    initializePlayer(&player, "Web Hero");
    initializeGraph(&dungeon);
    initialized = 1;
}

/* flags: 1=Sword, 2=Potion, 4=Key, 8=Treasure */
API void wasm_restore(int room, int health, int attack, int score, int flags) {
    wasm_init();
    if (room >= 0 && room < MAX_ROOMS) player.currentRoom = room;
    player.health = health > 0 && health <= player.maxHealth ? health : player.maxHealth;
    player.attack = attack >= 20 ? attack : 20;
    player.score = score >= 0 ? score : 0;
    if (flags & 1) { addItem(&player.inventory, "Sword", ITEM_WEAPON, 50); dungeon.rooms[1].hasItem = 0; }
    if (flags & 2) { addItem(&player.inventory, "Health Potion", ITEM_POTION, 50); dungeon.rooms[4].hasItem = 0; }
    if (flags & 4) { addItem(&player.inventory, "Dungeon Key", ITEM_KEY, 0); player.hasKey = 1; dungeon.rooms[6].hasItem = 0; }
    if (flags & 8) { addItem(&player.inventory, "Gold Treasure", ITEM_TREASURE, 100); dungeon.rooms[6].hasItem = 0; }
}

API int wasm_move(int target_room) {
    if (!initialized) wasm_init();
    if (target_room < 0 || target_room >= MAX_ROOMS) return 0;
    if (!isValidMove(&dungeon, player.currentRoom, target_room)) return 0;
    if (target_room == 8 && !player.hasKey) return 0;
    player.currentRoom = target_room;
    dungeon.rooms[target_room].isExplored = 1;
    enter_room(target_room);
    if (target_room == 8) player.score += 500;
    return 1;
}

API int wasm_use_potion(void) {
    ItemNode *potion = searchItem(&player.inventory, "Health Potion");
    if (!potion) return 0;
    healPlayer(&player, potion->value);
    removeItem(&player.inventory, "Health Potion");
    return 1;
}

API int wasm_start_combat(int room) {
    if (!initialized || (room != 5 && room != 7)) return 0;
    enemy_health = room == 7 ? 120 : 60;
    enemy_attack = room == 7 ? 40 : 20;
    return enemy_health;
}

API int wasm_attack_enemy(void) {
    if (enemy_health <= 0) return 0;
    enemy_health -= player.attack;
    if (enemy_health <= 0) {
        player.score += enemy_attack == 40 ? 200 : 100;
        enemy_health = 0;
        return 0;
    }
    takeDamage(&player, enemy_attack);
    return enemy_health;
}

API int wasm_enemy_health(void) { return enemy_health; }

API int wasm_room(void) { return player.currentRoom; }
API int wasm_health(void) { return player.health; }
API int wasm_attack(void) { return player.attack; }
API int wasm_score(void) { return player.score; }
API int wasm_has_key(void) { return player.hasKey; }
API int wasm_item_count(void) { return player.inventory.count; }
API const char *wasm_item_name(int index) {
    ItemNode *node = player.inventory.head;
    while (node && index-- > 0) node = node->next;
    return node ? node->name : "";
}
