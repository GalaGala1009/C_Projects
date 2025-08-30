# C_Projects
---
This repo is created to record my C projects.

### Crushit

In this project, you match letter tiles (A to Z) on a 5x6 grid. Tiles match if there are 3 or more of the same letter in a horizontal or vertical line, and those tiles are removed, letting others fall into the gaps. Unmatched tiles are hidden from the player.

Key rules:
The board is 5 tiles wide and 6 tiles tall, with extra tiles above that drop into the bottom six rows.
Maximum horizontal or vertical matches are 20 tiles.
Matching is "parallel": if a tile is part of two matches (e.g., in a 3x3 or 3x4 pattern), both matches are removed.
Goal: Find the smallest board (5 tiles wide, 6 tiles tall) with the longest possible match.

### T27

The Dictionary Abstract Data Type (ADT) stores words for later spell-checking. It can be implemented in various ways, like binary trees or hash tables. Here, we use a 27-Way Tree, which has 27 links per node—one for each letter (a to z) and one for the apostrophe ('), similar to a trie structure.



### MatchDrop

In Match Drop, a 2D grid of tiles is labeled with letters (A to Z) or a special "hawk" tile. The hawk tile pushes down one column, making all tiles in that column the same letter as the hawk tile.

For example, if the hawk tile pushes down the first column, the board updates accordingly. Columns that are fully matched (all same letter) are completed and fixed. The goal is to use the hawk tile to complete the entire board. An example is provided.
