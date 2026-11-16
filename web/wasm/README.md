# WebAssembly game engine

Install the Emscripten SDK, activate it in PowerShell, then run:

```powershell
.\build-wasm.ps1
```

This produces `dist/dungeon-engine.js` and `dist/dungeon-engine.wasm`. The bridge reuses the C player, graph, and linked-list inventory modules. Its exported API is `wasm_init`, `wasm_move`, `wasm_use_potion`, and state getters.
