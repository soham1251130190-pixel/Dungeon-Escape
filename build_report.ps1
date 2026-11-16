Add-Type -AssemblyName System.IO.Compression.FileSystem
Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.Xml.Linq

$InputDocx = Join-Path $PSScriptRoot 'Dungeon Escape Data Structures Report.docx'
$OutputDocx = Join-Path $PSScriptRoot 'Dungeon Escape Course Project Report.docx'
Copy-Item -LiteralPath $InputDocx -Destination $OutputDocx -Force

$w = [System.Xml.Linq.XNamespace]'http://schemas.openxmlformats.org/wordprocessingml/2006/main'
function Esc([string]$s) { return [Security.SecurityElement]::Escape($s) }
function XP([string]$xml) { return [System.Xml.Linq.XElement]::Parse($xml) }
function Para([string]$text, [string]$style = '', [bool]$bold = $false, [bool]$code = $false) {
  $safe = Esc $text
  $ppr = ''
  $rpr = '<w:rPr><w:rFonts w:ascii="Times New Roman" w:hAnsi="Times New Roman"/>'
  if ($bold) { $rpr += '<w:b/>' }
  if ($code) { $rpr = '<w:rPr><w:rFonts w:ascii="Courier New" w:hAnsi="Courier New"/><w:sz w:val="18"/></w:rPr>' }
  else { $rpr += '</w:rPr>' }
  if ($style) { $ppr += '<w:pStyle w:val="' + $style + '"/>' }
  if ($style -like 'Heading*') { $ppr += '<w:keepNext/><w:spacing w:before="240" w:after="120"/>' }
  else { $ppr += '<w:jc w:val="both"/><w:spacing w:line="360" w:lineRule="auto" w:after="120"/>' }
  return XP ('<w:p xmlns:w="' + $w + '"><w:pPr>' + $ppr + '</w:pPr><w:r>' + $rpr + '<w:t xml:space="preserve">' + $safe + '</w:t></w:r></w:p>')
}
function Center([string]$text, [bool]$bold = $false, [int]$size = 24) {
  $safe = Esc $text; $b = if($bold){'<w:b/>'}else{''}
  return XP ('<w:p xmlns:w="' + $w + '"><w:pPr><w:jc w:val="center"/><w:spacing w:after="120"/></w:pPr><w:r><w:rPr><w:rFonts w:ascii="Times New Roman" w:hAnsi="Times New Roman"/>' + $b + '<w:sz w:val="' + $size + '"/></w:rPr><w:t>' + $safe + '</w:t></w:r></w:p>')
}
function PageBreak() { return XP ('<w:p xmlns:w="' + $w + '"><w:r><w:br w:type="page"/></w:r></w:p>') }
function Tbl([object[]]$rows) {
  $xml = '<w:tbl xmlns:w="' + $w + '"><w:tblPr><w:tblStyle w:val="TableGrid"/><w:tblW w:w="0" w:type="auto"/></w:tblPr><w:tblGrid>'
  $cols = $rows[0].Count; for($i=0;$i -lt $cols;$i++){ $xml += '<w:gridCol w:w="1800"/>' }; $xml += '</w:tblGrid>'
  for($ri=0;$ri -lt $rows.Count;$ri++){ $xml += '<w:tr>'; foreach($cell in $rows[$ri]) { $txt=Esc ([string]$cell); $shade=if($ri -eq 0){'<w:shd w:fill="D9EAF7"/>'}else{''}; $bold=if($ri -eq 0){'<w:b/>'}else{''}; $xml += '<w:tc><w:tcPr>' + $shade + '</w:tcPr><w:p><w:pPr><w:spacing w:after="60"/></w:pPr><w:r><w:rPr><w:rFonts w:ascii="Times New Roman" w:hAnsi="Times New Roman"/><w:sz w:val="20"/>' + $bold + '</w:rPr><w:t xml:space="preserve">' + $txt + '</w:t></w:r></w:p></w:tc>' }; $xml += '</w:tr>' }; $xml += '</w:tbl>'; return XP $xml
}

$zip = [System.IO.Compression.ZipFile]::Open($OutputDocx, [System.IO.Compression.ZipArchiveMode]::Update)
$entry = $zip.GetEntry('word/document.xml')
$reader = [IO.StreamReader]::new($entry.Open()); [xml]$raw = $reader.ReadToEnd(); $reader.Close()
$xmlText = $raw.OuterXml
$replacements = @{
  'Project Title' = 'Dungeon Escape A Data Structures Driven Adventure Game'
  'Title of Project' = 'Dungeon Escape A Data Structures Driven Adventure Game'
  'Branch Name' = 'Information Technology'
  'Name (PRN)' = 'Soham (PRN: __________)'
  'Name of the students (PRN)' = 'Soham (PRN: __________)'
  'Project Title:   ' = 'Project Title: Dungeon Escape A Data Structures Driven Adventure Game'
  'Project Area:  ' = 'Project Area: Data Structures and Algorithms'
  'Academic Year:  ' = 'Academic Year: 2026-2027'
  'Group No :   ' = 'Group No: __________'
}
foreach($key in $replacements.Keys) { $xmlText = $xmlText.Replace($key, $replacements[$key]) }
$doc = [System.Xml.Linq.XDocument]::Parse($xmlText, [System.Xml.Linq.LoadOptions]::PreserveWhitespace)
$body = $doc.Root.Element($w + 'body')
function ReplaceParagraphText([System.Xml.Linq.XElement]$paragraph, [string]$newText) {
  $nodes = @($paragraph.Descendants($w + 't'))
  if ($nodes.Count -gt 0) {
    $nodes[0].Value = $newText
    for($i = 1; $i -lt $nodes.Count; $i++) { $nodes[$i].Remove() }
  }
}
foreach($paragraph in @($body.Descendants($w + 'p'))) {
  $existing = (($paragraph.Descendants($w + 't') | ForEach-Object { $_.Value }) -join '')
  if($existing -like 'We would like to express our sincere gratitude*') { ReplaceParagraphText $paragraph 'I express sincere gratitude to Dr. Pravin Futane, Head of the Department of Information Technology, for valuable guidance and encouragement throughout this project.' }
  elseif($existing -like 'We would also like to extend our heartfelt appreciation*') { ReplaceParagraphText $paragraph 'I sincerely thank Dr. Poonam Pawar, my subject teacher and internal guide, for continuous support, expert direction, and constructive suggestions during the design and implementation of this data structures project.' }
  elseif($existing -like 'Furthermore, we are grateful*') { ReplaceParagraphText $paragraph 'I am grateful to Vishwakarma Institute of Technology for the facilities, learning environment, and discussions that supported this work.' }
  elseif($existing -like 'Lastly, we extend our thanks*') { ReplaceParagraphText $paragraph 'I thank my family and friends for their encouragement and support.' }
}
$indexStart = $body.Elements($w + 'p') | Where-Object { (($_.Descendants($w+'t') | ForEach-Object {$_.Value}) -join '') -eq 'INDEX' } | Select-Object -First 1
if($indexStart) { $remove = $false; foreach($node in @($body.Elements())) { if($node -eq $indexStart){$remove=$true}; if($remove -and $node.Name -ne ($w+'sectPr')){$node.Remove()} } }

$content = New-Object System.Collections.Generic.List[System.Xml.Linq.XElement]
$content.Add((PageBreak))
$content.Add((Center 'INDEX' $true 28))
$content.Add((Tbl @(
  @('Chapter','Title'),
  @('1','Introduction'), @('2','Literature Review and Requirements'), @('3','Proposed System and Design'),
  @('4','Selection and Justification of Data Structures'), @('5','Source Code and Core Functions'),
  @('6','Testing and Output'), @('7','Conclusion'), @('8','References')
)))
$content.Add((PageBreak))
$content.Add((Para '1. INTRODUCTION' 'Heading1' $true))
$content.Add((Para '1.1 Project Overview' 'Heading2' $true))
$content.Add((Para 'Dungeon Escape is a console-based adventure game written in C99. The player navigates a nine-room dungeon, gathers weapons and items, fights enemies, locates a key, defeats a guardian, and reaches an exit. The game is deliberately designed as an integrated demonstration of data structures rather than as a game with structures added afterwards. Each major gameplay action is mapped to an abstract data type: movement uses a graph, undo uses a stack, inventory uses a linked list, combat arrivals use a queue, combat priority uses a max heap, and item lookup uses a hash table.'))
$content.Add((Para 'The program is modular. Header files declare structures and operations; source files provide independent implementations; main.c only starts the game loop. This separation makes the data-structure operations visible, testable, and reusable. Dynamic structures allocate nodes with malloc and release them with free during cleanup.'))
$content.Add((Para '1.2 Objectives' 'Heading2' $true))
$content.Add((Tbl @(
  @('No.','Objective'),
  @('1','Implement core linear and non-linear data structures manually in C.'),
  @('2','Relate each data structure to a meaningful gameplay requirement.'),
  @('3','Demonstrate traversal, searching, sorting, hashing, priority handling, and path finding.'),
  @('4','Use modular ADT interfaces, dynamic memory management, and defensive checks.'),
  @('5','Compare the time and space behavior of the chosen operations.')
)))
$content.Add((Para '1.3 Scope' 'Heading2' $true))
$content.Add((Para 'The current version is a local, single-player terminal application. It includes a fixed nine-room dungeon, a weapon array, an item database, an inventory, a persistent text-file leaderboard, and displays that make each structure visible during play. It does not require external libraries or a graphical interface.'))
$content.Add((PageBreak))
$content.Add((Para '2. LITERATURE REVIEW AND REQUIREMENTS' 'Heading1' $true))
$content.Add((Para '2.1 Literature Review' 'Heading2' $true))
$content.Add((Para 'The design follows standard algorithmic principles. Dijkstra established the shortest-path foundation used for route reasoning in graphs. Tarjan demonstrated linear-time depth-first search techniques. Williams introduced the heap as a practical structure for priority sorting. Fredman and Tarjan developed efficient heap-based priority-queue ideas. Knuth and Cormen et al. provide the broader analysis used for arrays, linked structures, hashing, trees, sorting, and asymptotic notation. In this project, the algorithms are intentionally kept appropriate for an undergraduate C implementation: BFS is used for an unweighted shortest route, DFS demonstrates recursive exploration, and a binary max heap prioritizes combat threats.'))
$content.Add((Para '2.2 Functional Requirements' 'Heading2' $true))
$content.Add((Tbl @(
  @('Requirement','Data-structure response'),
  @('Navigate only through legal room connections','Adjacency-list graph and move validation'),
  @('Undo the most recent movement','Linked stack using push and pop'),
  @('Keep an inventory with changing size','Singly linked list'),
  @('Process enemy arrivals in order','FIFO linked queue'),
  @('Choose strongest enemy first','Array-based max heap'),
  @('Rotate combat turns fairly','Circular queue using modulo indexing'),
  @('Find an item by name quickly','Separate-chaining hash table'),
  @('Show a shortest route to exit','BFS queue with parent reconstruction'),
  @('Rank saved scores','Array plus manual sorting algorithms')
)))
$content.Add((Para '2.3 Software and Tools Used' 'Heading2' $true))
$content.Add((Tbl @(
  @('Tool','Purpose'), @('C99','Core implementation language'), @('GCC or MinGW','Compilation with warning checks'), @('Standard C library','Input/output, strings, allocation, and file handling'), @('Text file','Persistent leaderboard storage'), @('Windows terminal','Execution of the console game')
)))
$content.Add((PageBreak))
$content.Add((Para '3. PROPOSED SYSTEM AND DESIGN' 'Heading1' $true))
$content.Add((Para '3.1 System Architecture' 'Heading2' $true))
$content.Add((Para 'The game loop coordinates Player, Graph, Inventory, Stack, Queue, CircularQueue, MaxHeap, HashTable, BinaryTree, weapon array, and Leaderboard ADTs. A player action is checked against the dungeon graph. Successful movement is recorded on the stack. Entering rooms may add an item node, enqueue enemies, or trigger a combat cycle. The item database remains indexed by hash table while the player inventory remains a separate linked list, because their query and update patterns differ.'))
$content.Add((Para 'Input -> Game Controller -> Graph movement validation -> Player state update -> Inventory or Combat event -> Structure-specific display -> Persistent leaderboard output' '' $true))
$content.Add((Para '3.2 Data Structures Used' 'Heading2' $true))
$content.Add((Tbl @(
  @('Structure','Representation','Project role'),
  @('Array','Fixed contiguous storage','Weapon database, BFS arrays, leaderboard, heap storage'),
  @('Linked list','Heap-allocated nodes','Inventory items, graph adjacency nodes, hash chains'),
  @('Stack','Linked nodes with top pointer','Last-in first-out movement undo'),
  @('Queue','Linked nodes with front/rear','First-in first-out waiting enemies'),
  @('Circular queue','Fixed array with modulo indices','Repeated battle turns'),
  @('Max heap','Array-backed complete binary tree','Highest-attack enemy selection'),
  @('Binary tree','Nodes with left/right children','Hierarchical dungeon-zone display'),
  @('Graph','Array of adjacency lists','Navigable dungeon map and path finding'),
  @('Hash table','Bucket array plus chained nodes','Item database lookup')
)))
$content.Add((Para '3.3 Data Flow and Logic' 'Heading2' $true))
$content.Add((Para 'A new game initializes all ADTs. The graph creates rooms and bidirectional corridors. The binary tree provides a conceptual hierarchy while the graph remains the authoritative movement model. When the player moves, the previous room is pushed onto the movement stack. The inventory list receives collected items. Enemies first enter the FIFO queue, then are inserted into the max heap for threat-based action selection; the circular queue cycles entities through turns. At any time, the player can inspect the structures or request BFS/DFS analysis of the graph.'))
$content.Add((PageBreak))
$content.Add((Para '4. SELECTION AND JUSTIFICATION OF DATA STRUCTURES' 'Heading1' $true))
$content.Add((Para '4.1 Core Data Structures' 'Heading2' $true))
$content.Add((Para 'Arrays are used when capacity is known and index access is valuable. The weapon catalogue and leaderboard benefit from compact contiguous storage, while BFS uses small fixed arrays for visited flags, parent links, distances, and its internal queue. This is appropriate because MAX_ROOMS is fixed at nine.'))
$content.Add((Para 'The inventory is a singly linked list because its size changes during play. addItem allocates an ItemNode and links it at the end; removeItem adjusts predecessor links and frees the removed node. The tradeoff is linear traversal for a name lookup, but this is acceptable for a small, player-owned collection and makes pointer manipulation explicit.'))
$content.Add((Para 'The movement history is a stack because undo must reverse the latest successful move. push places the current room at top; pop returns the most recently recorded room. This gives O(1) insertion and removal and directly matches the LIFO rule.'))
$content.Add((Para 'The waiting-enemy queue represents arrival order fairly. A linked implementation permits enqueue at rear and dequeue at front in O(1), without shifting elements. The circular queue is different: it is bounded and rotates turns using (rear + 1) % MAX_TURNS, so a vacated array position can be reused.'))
$content.Add((Para 'The max heap is selected for threat-based combat. Its root is always the enemy with greatest attack value, so peekMax and removeMax are O(1) and O(log n) respectively. Insertion uses sift-up and removal restores order through heapify. A sorted array would make one operation expensive; the heap balances repeated priority updates.'))
$content.Add((Para 'The graph uses adjacency lists, which are more space-efficient than an adjacency matrix for the sparse dungeon. Each RoomVertex owns a linked list of adjacent rooms. BFS explores this graph level by level and reconstructs the route from parent[]; DFS recursively explores connected rooms.'))
$content.Add((Para 'The hash table stores the global item encyclopedia, not the mutable inventory. It uses a polynomial DJB2-style hash, reduces the value modulo ten buckets, and resolves collisions with separate chaining. Average lookup is O(1), while a worst-case crowded bucket is O(n).'))
$content.Add((Para '4.2 Algorithm Choices and Complexity Analysis' 'Heading2' $true))
$content.Add((Tbl @(
  @('Operation','Structure / algorithm','Time complexity','Reason'),
  @('Add inventory item','Linked list tail traversal','O(n)','Simple dynamic collection; can be O(1) with a tail pointer'),
  @('Remove or search inventory','Linked list','O(n)','Sequential traversal by name'),
  @('Undo movement','Stack pop','O(1)','Top pointer removal'),
  @('Enemy arrival / service','Linked queue','O(1)','Rear insertion and front removal'),
  @('Schedule next combat threat','Max heap','O(log n) remove, O(1) peek','Maintains strongest enemy at root'),
  @('Find database item','Hash table','O(1) average','Bucket lookup with chaining'),
  @('Find weapon in sorted array','Binary search','O(log n)','Halves search interval'),
  @('Shortest unweighted route','BFS','O(V + E)','Visits each room and corridor at most once'),
  @('Full connected exploration','DFS','O(V + E)','Recursively traverses adjacency lists'),
  @('Leaderboard ordering','Bubble/selection/insertion sort','O(n^2)','Pedagogical comparison for small n')
)))
$content.Add((Para '4.3 Space Complexity' 'Heading2' $true))
$content.Add((Para 'The adjacency-list graph consumes O(V + E) space. BFS requires O(V) additional arrays for visited, parent, distance, and queue. DFS requires O(V) visited storage plus recursion-stack space up to O(V). The inventory, stack, queue, adjacency lists, and hash chains consume O(n) nodes proportional to stored entries. The fixed heap, circular queue, and leaderboard consume bounded array space set by constants in their headers.'))
$content.Add((PageBreak))
$content.Add((Para '5. SOURCE CODE AND CORE FUNCTIONS' 'Heading1' $true))
$content.Add((Para '5.1 Graph Initialization and BFS' 'Heading2' $true))
$content.Add((Para 'initializeGraph creates nine named vertices and adds bidirectional corridors through addEdge. Each corridor is stored as an AdjListNode. BFS initializes visited[] to zero, sets parent[] and dist[] to -1, enqueues the start room, and records a parent when it discovers an unvisited neighbor. The parent chain is then followed backwards from the exit to print the shortest route.'))
$content.Add((Para 'void addEdge(Graph *g, int src, int dest, int weight, int bidirectional) {\n    AdjListNode *node = createAdjNode(dest, weight);\n    node->next = g->rooms[src].head;\n    g->rooms[src].head = node;\n    if (bidirectional) { /* insert reverse edge */ }\n}' '' $false $true))
$content.Add((Para '5.2 Linked List Inventory' 'Heading2' $true))
$content.Add((Para 'The ItemNode structure holds item name, type, value, and a next pointer. addItem allocates a node, copies bounded strings, attaches it to the list, increments count, and checks allocation failure. removeItem correctly handles deletion at the head and in the middle/tail, then frees the removed node.'))
$content.Add((Para '5.3 Stack and Queue Operations' 'Heading2' $true))
$content.Add((Para 'The stack uses a top pointer. push links a new node before the old top; pop stores the top node, advances top, copies requested output values, and frees the old node. The FIFO queue maintains both front and rear pointers. Its enqueue and dequeue functions avoid array shifting and explicitly report empty-queue conditions.'))
$content.Add((Para '5.4 Heap and Hash Functions' 'Heading2' $true))
$content.Add((Para 'insertHeap places a new enemy at the next free array location and repeatedly compares it with parent index (current - 1) / 2. heapify compares an index with 2*i+1 and 2*i+2, swaps with the largest child, and recurses. hashFunction normalizes characters to lowercase and applies hash = hash * 33 + c before modulo reduction; each bucket points to a chain of HashNode values.'))
$content.Add((Para '5.5 Modular Program Organization' 'Heading2' $true))
$content.Add((Tbl @(
  @('Module','Responsibility'), @('graph.c / graph.h','Adjacency lists, move validation, BFS, DFS'), @('inventory.c / inventory.h','Singly linked inventory'), @('stack.c / stack.h','Movement history and undo'), @('queue.c / queue.h','Enemy waiting line'), @('circular_queue.c / circular_queue.h','Round-robin battle turns'), @('heap.c / heap.h','Priority combat queue'), @('hashing.c / hashing.h','Item database and separate chaining'), @('sorting.c and searching.c','Leaderboard ordering and search demonstrations')
)))
$content.Add((PageBreak))
$content.Add((Para '6. TESTING AND OUTPUT' 'Heading1' $true))
$content.Add((Para '6.1 Test Cases' 'Heading2' $true))
$content.Add((Tbl @(
  @('Test','Input / action','Expected result'),
  @('Valid movement','Move from Entrance to Dark Hall','Graph confirms edge and movement stack records the prior room'),
  @('Invalid movement','Attempt to move between unconnected rooms','Move is rejected; room state remains unchanged'),
  @('Undo movement','Select undo after two successful moves','Stack pop returns the latest previous room'),
  @('Inventory insertion','Collect Sword and Health Potion','Linked list prints HEAD -> [Sword] -> [Health Potion] -> NULL'),
  @('Inventory deletion','Use a Health Potion','Matching node is unlinked, freed, and count decreases'),
  @('Hash lookup','Search for Dungeon Key','Hash bucket is computed and matching chained node is reported'),
  @('Priority combat','Insert Goblin, Orc, Dragon','Max heap places highest attack enemy at root'),
  @('Shortest path','BFS from Entrance to Exit','Route is printed with minimum room-step count'),
  @('Leaderboard sort','Load multiple scores','Scores are displayed in descending order')
)))
$content.Add((Para '6.2 Representative Output' 'Heading2' $true))
$content.Add((Para 'SHORTEST PATH SEARCH (BFS)\nOrigin : [0] Entrance\nTarget : [8] Exit\nShortest Path: [0] Entrance -> [3] Dark Hall -> [6] Treasure Room -> [7] Boss Room -> [8] Exit\nTotal Rooms / Steps Distance: 4' '' $false $true))
$content.Add((Para 'The visible structure displays are deliberate testing aids. For example, the inventory prints the linked chain from HEAD to NULL, the stack prints from TOP to BOTTOM, the heap prints its array and parent-child interpretation, and the hash table prints every bucket. These outputs allow the user and evaluator to validate the internal representation rather than only observing the gameplay result.'))
$content.Add((Para '6.3 Memory and Boundary Checks' 'Heading2' $true))
$content.Add((Para 'The program checks null structure pointers before operations, detects empty stack/queue/heap cases, detects a full heap or circular queue, bounds copied strings, and releases allocated nodes in freeInventory, freeStack, freeQueue, freeGraph, and freeHashTable. These checks make underflow, allocation failure, and invalid room IDs explicit rather than silently corrupting state.'))
$content.Add((PageBreak))
$content.Add((Para '7. CONCLUSION' 'Heading1' $true))
$content.Add((Para '7.1 Summary of Learnings' 'Heading2' $true))
$content.Add((Para 'Dungeon Escape demonstrates that data structures are selected because of the operations a problem requires. The project uses a graph for connectivity, a stack for reversal, queues for order and cyclic scheduling, a heap for priority, linked lists for changing collections, a hash table for fast key-based access, and arrays when fixed indexed storage is appropriate. BFS and DFS turn the graph into meaningful navigational analysis, while searching and sorting expose algorithmic tradeoffs.'))
$content.Add((Para 'Implementing each ADT manually in C strengthened understanding of node linking, pointer ownership, dynamic allocation, modular interfaces, recursion, and asymptotic analysis. The project also shows why one structure should not be used for every task: the global item database and player inventory, for example, have different update and lookup needs and are better represented by a hash table and linked list respectively.'))
$content.Add((Para '7.2 Future Improvements' 'Heading2' $true))
$content.Add((Tbl @(
  @('Improvement','Data-structure impact'), @('Dynamic dungeon generator','Resizable graph and randomized adjacency construction'), @('Save/load game state','Serialization of all ADTs'), @('Balanced search tree for leaderboard','Faster ordered insertion for larger score sets'), @('Dijkstra algorithm for weighted corridors','Priority queue based shortest paths'), @('Hash-table resizing','Lower collision chains as item count grows'), @('Graphical interface','Separate view layer while preserving ADT model')
)))
$content.Add((PageBreak))
$content.Add((Para '8. REFERENCES' 'Heading1' $true))
$content.Add((Para '[1] E. W. Dijkstra, “A note on two problems in connexion with graphs,” Numerische Mathematik, vol. 1, pp. 269-271, 1959.'))
$content.Add((Para '[2] R. E. Tarjan, “Depth-first search and linear graph algorithms,” SIAM Journal on Computing, vol. 1, no. 2, pp. 146-160, 1972.'))
$content.Add((Para '[3] J. W. J. Williams, “Algorithm 232: Heapsort,” Communications of the ACM, vol. 7, no. 6, pp. 347-348, 1964.'))
$content.Add((Para '[4] M. L. Fredman and R. E. Tarjan, “Fibonacci heaps and their uses in improved network optimization algorithms,” Journal of the ACM, vol. 34, no. 3, pp. 596-615, 1987.'))
$content.Add((Para '[5] D. E. Knuth, The Art of Computer Programming, Vol. 3: Sorting and Searching, 2nd ed. Reading, MA: Addison-Wesley, 1998.'))
$content.Add((Para '[6] T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, Introduction to Algorithms, 3rd ed. Cambridge, MA: MIT Press, 2009.'))
$content.Add((Para '[7] Project source code: Dungeon Escape, C99 course project, 2026.'))
$sectPr = $body.Element($w + 'sectPr')
foreach($item in $content) { [void]$sectPr.AddBeforeSelf($item) }

$entry.Delete()
$newEntry = $zip.CreateEntry('word/document.xml')
$writer = [IO.StreamWriter]::new($newEntry.Open(), [Text.UTF8Encoding]::new($false))
$doc.Save($writer); $writer.Close(); $zip.Dispose()
Write-Output "Created $OutputDocx"
