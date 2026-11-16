# DUNGEON ESCAPE 🏰🗡️
**A College-Level Data Structures & Algorithms Adventure Game in C**

---

## 1. Project Description
**Dungeon Escape** is an interactive, console-based terminal adventure game developed entirely in standard C (C99). The project is specifically engineered to demonstrate the real-world application, manual implementation, and theoretical concepts of foundational **Data Structures and Algorithms** taught in college computer science curricula.

There are **zero external dependencies** and **no C++ STL**. Every data structure and algorithm is manually implemented with dynamic memory management, pointer manipulation, and rigorous error handling.

---

## 2. Game Objective
The player wakes up trapped inside an ancient, perilous dungeon. The objective is to:
1. Explore connected rooms using the **Dungeon Graph**.
2. Scavenge for weapons and consumable items stored in a dynamic **Linked List Inventory**.
3. Defeat hostile monsters in turn-based combat governed by a **FIFO Waiting Queue**, **Max Heap Attack Priority**, and **Circular Turn Queue**.
4. Use **Undo Movement** powered by a **LIFO Stack** if a wrong turn is taken.
5. Search for items via **Hash Table (Separate Chaining)** and weapons via **Binary Search (O(log n))**.
6. Find the **Dungeon Key** hidden in the Treasure Room.
7. Compute the shortest route to freedom using **Breadth-First Search (BFS)**.
8. Slay the guardian dragon, unlock the **Exit Portal**, and escape with the highest score to claim a top rank on the **Leaderboard**!

---

## 3. Data Structures & Game Usage Table

| # | Data Structure | Source / Header Files | Role & Usage in Dungeon Escape |
|---|---|---|---|
| 1 | **Array** | `weapons.c`, `leaderboard.c` | Stores the static weapon database sorted by attack value, and the active leaderboard records. |
| 2 | **Strings** | `player.c`, `weapons.c`, etc. | Handles textual representations of player names, room descriptions, items, and enemy lore. |
| 3 | **Linked List** | `inventory.c` / `inventory.h` | Singly linked list for player inventory (`ItemNode`), dynamically growing with `malloc()` and shrinking with `free()`. |
| 4 | **Stack** | `stack.c` / `stack.h` | LIFO (Last-In First-Out) movement history stack enabling the player to "Undo Last Move". |
| 5 | **Queue** | `queue.c` / `queue.h` | FIFO (First-In First-Out) enemy line managing incoming monsters waiting to engage in combat. |
| 6 | **Circular Queue** | `circular_queue.c` / `circular_queue.h` | Array-based circular queue with modulo indexing `(rear + 1) % MAX` for turn rotations between player and enemies. |
| 7 | **Heap / Priority Queue** | `heap.c` / `heap.h` | Max Heap where enemies are prioritized by attack damage; strongest enemy attacks first. |
| 8 | **Binary Tree** | `binary_tree.c` / `binary_tree.h` | Hierarchical tree structure representing dungeon zones from Entrance down to the Exit Portal. |
| 9 | **Graph** | `graph.c` / `graph.h` | Adjacency List graph representing actual navigable corridors and room connectivity. |
| 10 | **Hashing** | `hashing.c` / `hashing.h` | Hash table using a polynomial hash function and **Separate Chaining** for $O(1)$ average item dictionary lookups. |
| 11 | **Linear Search** | `searching.c` / `searching.h` | Sequentially traverses unsorted items and linked list inventory nodes. |
| 12 | **Binary Search** | `searching.c` / `searching.h` | Logarithmic $O(\log n)$ search on the sorted weapon arsenal array by attack power. |
| 13 | **Sorting** | `sorting.c` / `sorting.h` | Manual Bubble Sort, Selection Sort, and Insertion Sort to sort leaderboard scores descendingly. |
| 14 | **Recursion** | `binary_tree.c`, `graph.c` | Recursive Preorder, Inorder, and Postorder tree traversals, and recursive Depth-First Search (DFS). |

---

## 4. Algorithms Used
- **Breadth-First Search (BFS)**: Computes the unweighted shortest path from the player's current room to the Exit Room with distance and step-by-step path reconstruction.
- **Depth-First Search (DFS)**: Recursively explores all reachable rooms from the current position.
- **Tree Traversals**: Recursive Preorder (Root-L-R), Inorder (L-Root-R), and Postorder (L-R-Root) traversals of the dungeon tree.
- **Binary Search**: $O(\log n)$ divide-and-conquer search on sorted arrays.
- **Separate Chaining Hash Collision Resolution**: Linked list bucket chaining for duplicate hash indices.
- **Max-Heapify & Sift-Up**: Maintains the heap order property for combat priority.
- **Bubble / Selection / Insertion Sort**: Demonstrates $O(n^2)$ comparison-based sorting for leaderboard persistence.

---

## 5. Folder Structure
```text
Dungeon-Escape/
│
├── main.c                          # Application entry point
├── README.md                       # Project documentation
│
├── include/                        # Header files with prototypes & struct definitions
│   ├── player.h                    # Player attributes & stats
│   ├── game.h                      # Central Game Controller & Loop
│   ├── inventory.h                 # Singly Linked List inventory
│   ├── stack.h                     # LIFO Undo movement stack
│   ├── queue.h                     # FIFO Enemy waiting line
│   ├── circular_queue.h            # Battle turn circular queue
│   ├── heap.h                      # Enemy threat Max Heap
│   ├── binary_tree.h               # Hierarchical dungeon tree
│   ├── graph.h                     # Room network adjacency list, BFS & DFS
│   ├── hashing.h                   # Separate chaining Hash Table
│   ├── searching.h                 # Linear and Binary search
│   ├── sorting.h                   # Bubble, Selection, Insertion Sort
│   ├── weapons.h                   # Weapon arsenal array
│   └── leaderboard.h               # Leaderboard array & file handling
│
├── src/                            # Implementation files
│   ├── player/player.c
│   ├── game/game.c
│   ├── inventory/inventory.c
│   ├── stack/stack.c
│   ├── queue/queue.c
│   ├── circular_queue/circular_queue.c
│   ├── heap/heap.c
│   ├── binary_tree/binary_tree.c
│   ├── graph/graph.c
│   ├── hashing/hashing.c
│   ├── searching/searching.c
│   ├── sorting/sorting.c
│   ├── weapons/weapons.c
│   └── leaderboard/leaderboard.c
│
└── data/
    └── leaderboard.txt             # Persistent high score records
```

---

## 6. How to Compile

Compile using any standard GCC compiler (MinGW, Linux GCC, or Clang) with `-Wall -Wextra`:

```bash
gcc -Wall -Wextra -Iinclude \
    main.c \
    src/player/player.c \
    src/game/game.c \
    src/inventory/inventory.c \
    src/stack/stack.c \
    src/queue/queue.c \
    src/circular_queue/circular_queue.c \
    src/heap/heap.c \
    src/binary_tree/binary_tree.c \
    src/graph/graph.c \
    src/hashing/hashing.c \
    src/searching/searching.c \
    src/sorting/sorting.c \
    src/weapons/weapons.c \
    src/leaderboard/leaderboard.c \
    -o dungeon_escape
```

On Windows:
```powershell
gcc -Wall -Wextra -Iinclude main.c src/player/player.c src/game/game.c src/inventory/inventory.c src/stack/stack.c src/queue/queue.c src/circular_queue/circular_queue.c src/heap/heap.c src/binary_tree/binary_tree.c src/graph/graph.c src/hashing/hashing.c src/searching/searching.c src/sorting/sorting.c src/weapons/weapons.c src/leaderboard/leaderboard.c -o dungeon_escape.exe
```

---

## 7. How to Run

On Linux / macOS:
```bash
./dungeon_escape
```

On Windows:
```powershell
.\dungeon_escape.exe
```

---

## 8. Example Gameplay Walkthrough

### Main Menu & Start:
```text
========================================
           DUNGEON ESCAPE
========================================
1. Start Game
2. Instructions
3. Leaderboard
4. Exit
----------------------------------------
Enter choice: 1
Enter your name: Soham
```

### Visual Linked List Inventory:
```text
========================================
        INVENTORY (LINKED LIST)
========================================
Visual Chain:
HEAD -> [Sword] -> [Health Potion] -> [Dungeon Key] -> NULL

  No.   Item Name         Type        Value   
  -----------------------------------------------
  [1]   Sword             Weapon      +50      
  [2]   Health Potion     Potion      +50      
  [3]   Dungeon Key       Key         +0       
  Total items: 3
========================================
```

### Visual Movement Stack (LIFO Undo):
```text
========================================
         MOVEMENT STACK (LIFO)
========================================
  TOP
   |
   v
  [ 2] Dark Hall (Room ID: 3)
  [ 1] Entrance (Room ID: 0)
   |
  BOTTOM
  Total recorded moves: 2
========================================
```

### Shortest Path via BFS:
```text
========================================
      SHORTEST PATH SEARCH (BFS)
========================================
Origin : [0] Entrance
Target : [8] Exit
Shortest Path:
  [0] Entrance -> [3] Dark Hall -> [6] Treasure Room -> [7] Boss Room -> [8] Exit
Total Rooms / Steps Distance: 4
========================================
```

### Combat Structures Display:
```text
========================================
        ENEMY WAITING QUEUE (FIFO)
========================================
  FRONT -> [Goblin (HP:30)] -> [Orc (HP:60)] -> [Dragon (HP:120)] -> REAR

========================================
        ENEMY MAX HEAP (PRIORITY)
========================================
  Root -> Dungeon Dragon (80 ATK)
  Child of [Dungeon Dragon] -> Goblin (20 ATK)
  Child of [Dungeon Dragon] -> Orc Warrior (50 ATK)

========================================
       BATTLE TURNS (CIRCULAR QUEUE)
========================================
Turn Order (Wrap-Around Cycle):
  [Soham] -> [Dungeon Dragon] -> [Orc Warrior] -> [Goblin] -> (wraps to start)
```

---

## 9. Learning Outcomes
1. **Dynamic Memory & Pointer Safety**: Proficient use of `malloc()`, `free()`, pointer manipulation, and avoiding memory leaks or dangling pointers.
2. **Abstract Data Types (ADTs)**: Clean separation of interface (`.h`) and implementation (`.c`).
3. **Graph Theory & Pathfinding**: Implementing BFS queue-based shortest path search and recursive DFS graph exploration.
4. **Tree Hierarchies & Recursion**: Constructing binary trees and applying recursive traversal patterns.
5. **Efficiency & Asymptotics**: Practical comparison between $O(n)$ Linear Search, $O(\log n)$ Binary Search, and $O(1)$ Hash Table lookups.
6. **Robust Software Design**: Building an interactive terminal application with clean modularity and defense against invalid inputs and edge cases.

