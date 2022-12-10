# CIS-190-PROJECT


## Project Description

```console
foo@bar:CIS-190-PROJECT$ make
foo@bar:CIS-190-PROJECT$ ./dinogame
```

We are planning to implement an interactive dinasour game on the terminal. We will clear the terminal at each game tick and redraw it again. We will use getch function to immediatly capture keyboard entries.

Some of the features that we expect to use are the following:

- Class hierachy: Our game will have class heirarchy for game objects such as the dinasour and the obstacles, these will have overloaded functionalites such as moving and jumping.
- Threading: to make sure the game is responsive to user input, we plan to utilize threads in the game to handle different parts. We are mainly considering a thread to display the game state and a thread to listen to user input from stdin.
- Arrays and smarts pointers to represent the game grid.
