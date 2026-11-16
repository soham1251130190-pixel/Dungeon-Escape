$ErrorActionPreference = 'Stop'
$projectRoot = (Resolve-Path "$PSScriptRoot\..\..").Path
New-Item -ItemType Directory -Force -Path "$PSScriptRoot\dist" | Out-Null
emcc "$PSScriptRoot\game_bridge.c" `
  "$projectRoot\src\player\player.c" `
  "$projectRoot\src\graph\graph.c" `
  "$projectRoot\src\inventory\inventory.c" `
  -I "$projectRoot\include" `
  -O2 -s MODULARIZE=1 -s EXPORT_NAME=DungeonWasm `
  -s EXPORTED_FUNCTIONS='["_wasm_init","_wasm_restore","_wasm_move","_wasm_use_potion","_wasm_start_combat","_wasm_attack_enemy","_wasm_enemy_health","_wasm_room","_wasm_health","_wasm_attack","_wasm_score","_wasm_has_key","_wasm_item_count","_wasm_item_name"]' `
  -s EXPORTED_RUNTIME_METHODS='["cwrap","UTF8ToString"]' `
  -o "$PSScriptRoot\dist\dungeon-engine.js"
