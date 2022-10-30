# Merry Music Memory
Winter-themed memory game that uses music instead of images

## Build
Exectue the following commands to build raylib.
```
cmake -S. -B_build -DCMAKE_INSTALL_PREFIX=<raylib-install-dir> -DBUILD_SHARED_LIBS=ON
cmake --build _build
cmake --install _build
```
> It is important to set -DBUILD_SHARED_LIBS=ON and not use the external glfw library.

Exectue  the following commands to build the game.
```
cmake -S. -B_build -DRAYLIB_INSTALL_DIR=<raylib-install-dir>
cmake --build _build
```

Run the game with the following command:
```
./_build/music
```

## Gameplay
At the start of the game, players must select the number of players. Up to 8 players are supported. Subsequently, the game starts.
![Player selection at game start](/screenshots/game_start.png)

In a player's turn each player can select two music cards on the game board. Card selection plays a short snippet of a song. If the selected cards match, the cards disappear and one point is added to the current player's score. It's again the current player's turn. If the selected cards do not match, it's the next player's turn. 
![The game board after game start](/screenshots/game_board.png)

The green score at the top indicates the current player. In the following screenshot, it's player two's turn. Player 2 has already found a match and selects another two cards. The progress bar on the bottom shows that a music snippet is playing. 
![Turn of player 2](/screenshots/player_2_mismatch.png)


When all cards have been matched and disappeared, the player with the highest score wins. 
![End of game](/screenshots/game_end.png)

