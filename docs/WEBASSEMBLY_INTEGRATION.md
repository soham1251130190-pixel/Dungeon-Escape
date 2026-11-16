# Dungeon Escape: WebAssembly Integration Guide

## 1. What is integrated

Dungeon Escape has two presentation layers:

- The original C console game in `main.c`, `src/`, and `include/`.
- A browser interface in `web/`, including the full-screen map at `web/map.html`.

The browser does **not** contact a remote backend API. Instead, selected C game logic is compiled to WebAssembly (`.wasm`) and runs directly inside the visitor's browser.

```text
Vercel HTTPS hosting
        │ serves static files
        ▼
map.html + map.js
        │ calls exported C functions
        ▼
dungeon-engine.js (Emscripten loader)
        │ loads
        ▼
dungeon-engine.wasm (compiled C)
        │ uses
        ▼
Player + Graph + Inventory C modules
```

HTTPS is only the delivery mechanism. WebAssembly is the local game engine.

## 2. Source of truth

The C WebAssembly bridge is `web/wasm/game_bridge.c`.

It imports and reuses these original C modules:

- `src/player/player.c` — health, attack, score, player lifecycle.
- `src/graph/graph.c` — dungeon graph construction and valid-move checks.
- `src/inventory/inventory.c` — linked-list item storage and potion removal.

`game_bridge.c` owns one in-memory C `Player` and one C `Graph`. The browser asks this C state for authoritative values instead of calculating health, score, attack, inventory, or graph validity independently.

## 3. C API exposed to the browser

| Export | Purpose |
|---|---|
| `wasm_init()` | Starts a fresh game state. |
| `wasm_restore(room, health, attack, score, flags)` | Restores a saved browser session. |
| `wasm_move(targetRoom)` | Validates and executes a graph move; triggers room pickup effects. |
| `wasm_use_potion()` | Heals the player and removes a Health Potion from the C linked list. |
| `wasm_start_combat(room)` | Starts a Monster Room or Boss Room encounter. |
| `wasm_attack_enemy()` | Applies the player attack, enemy retaliation, and victory score. |
| `wasm_enemy_health()` | Returns remaining enemy health. |
| `wasm_room()` / `wasm_health()` / `wasm_attack()` / `wasm_score()` | Returns core player state. |
| `wasm_item_count()` / `wasm_item_name(index)` | Reads the C linked-list inventory for display. |

The bridge marks pickups in the graph, equips the Armory sword, collects the Treasure Room key and gold, and refuses the Exit until the key exists.

## 4. Build process

Emscripten is installed locally under `.tools/emsdk/`. It is ignored by Git because it is a large toolchain, not project source.

Run this from the repository root whenever `game_bridge.c` or the linked C modules change:

```powershell
cmd /c "call .tools\emsdk\emsdk_env.bat && powershell -ExecutionPolicy Bypass -File web\wasm\build-wasm.ps1"
```

The build script compiles:

```text
web/wasm/game_bridge.c
src/player/player.c
src/graph/graph.c
src/inventory/inventory.c
```

It outputs these deployable files:

```text
web/wasm/dist/dungeon-engine.js
web/wasm/dist/dungeon-engine.wasm
```

Both generated files are committed because Vercel needs them at deploy time.

## 5. Browser loading flow

`web/map.html` loads the Emscripten loader before it loads the map controller:

```html
<script src="wasm/dist/dungeon-engine.js"></script>
<script src="map.js"></script>
```

In `web/map.js`, the generated loader is initialized:

```js
DungeonWasm().then((module) => {
  // module.cwrap() creates JavaScript wrappers for C exports.
});
```

For example, `wasm_move` is wrapped as a JavaScript function that accepts a room number and returns success (`1`) or failure (`0`). The UI then redraws from the returned C state.

## 6. Player movement flow

1. The user writes commands such as `hero.move(up);` in the map editor.
2. `map.js` moves the visual dot one map tile.
3. If the dot reaches a room marker, JavaScript requests `wasm_move(roomId)`.
4. The C graph checks whether that room is connected to the current room.
5. On success, C updates the player, room, and any room-specific pickup.
6. JavaScript reads the updated C values and redraws the map, inventory, health, attack, and score.

The visual dot is frontend animation; graph validation and item effects are C/WebAssembly logic.

## 7. Inventory and combat flow

The map's inventory panel calls C getters. It does not keep a separate authoritative item list.

- Entering Armory: C adds `Sword`, raises attack, and marks the item collected.
- Entering Potion Room: C adds `Health Potion`.
- Entering Treasure Room: C adds the Dungeon Key and Gold Treasure, enables the Exit, and awards score.
- Using a potion: browser calls `wasm_use_potion()`.
- Entering Monster or Boss Room: browser opens the combat interface and calls C combat exports.
- Attacking: browser calls `wasm_attack_enemy()` and then redraws from C state.

## 8. State transfer and persistence

When the user clicks **Open Full-Screen Map** from the main page, `web/app.js` writes the current browser game snapshot to `localStorage` as `dungeonEscapeState`.

When `map.html` opens, `map.js` reads that snapshot and calls `wasm_restore(...)` so the C/WebAssembly engine starts from the same room, health, attack, score, and items.

The full-screen map also writes its current state to `localStorage` after updates, allowing it to restore progress after a refresh or reopening the map in the same browser.

This is browser-local persistence. It is not cloud saving and does not synchronize between devices.

## 9. Vercel deployment

Vercel hosts the project as static files over HTTPS.

Recommended configuration:

1. Import the `Dungeon-Escape` GitHub repository.
2. Set **Root Directory** to `web`.
3. Select **Other** as the framework preset.
4. Leave the build command empty.
5. Deploy.

Vercel serves `map.html`, `map.js`, `wasm/dist/dungeon-engine.js`, and `wasm/dist/dungeon-engine.wasm`. Because WebAssembly files are loaded through HTTP(S), deploy through Vercel or another local HTTP server; do not expect direct `file:///` opening to work reliably.

## 10. Current limitations and next improvements

The current bridge proves the C-to-browser architecture and covers movement, pickups, inventory, potion usage, score, and a compact combat implementation. It is not yet a byte-for-byte port of every console menu feature.

Next improvements:

- Move all console combat queue/heap/circular-turn rules into exported bridge functions.
- Export BFS/DFS paths to render them visually on the map.
- Add a C-backed leaderboard persistence strategy suitable for browser storage or a server database.
- Load map state back into the main page as well as main-to-map transfer.
- Add automated browser tests using an HTTP server in CI.
