# CIS-190-PROJECT


## Project Description

```console
foo@bar:CIS-190-PROJECT$ make
foo@bar:CIS-190-PROJECT$ ./dinogame
```

We are planning to implement an interactive dinasour game on the terminal. We use the ncurses Library to be able to interactively draw on the terminal. We will clear the terminal at each game tick and redraw it again. We will use getch function to immediatly capture keyboard entries and take actions based on that. The user can press S/Space, A or D to jump obstacles. Obstacles are generated randomly. The game will keep track of the users score. If the user collides with an obstacles, the game is over and the user has the options to restart or to quit the game.

Some of the features that we expect to use are the following:

- Class hierachy & Templating: 
The project implements the following classes, with the following hierachy:

Drawable (Template): Base class for all drawable entities such as character and obstacles. Provides functions to draw, update and detect collisions. The Drawable class will take one template argument which a struct of the image of the object to be drawn. 
Animable (Template): A class that allows a entitiy to be animated by providing an series of drawables with different images and it will draw a different image everytime.
Character (Extends from Drawable): The main charachter that the user will control (The dinasour).
Birds (Extends from Drawable): Birds are on the background and do not collide with the character (just for the visuals)
Obstacles (Extends from Drawable): Obstacles that the character have to jump over

- Variants: We will use variants for two class, animable and drawable collection. The animable class will take variants of multiple drawables. This will allow us to use a vector to held multiple drawables (which are of different classes becasue of templating) and be able to call std::visit to draw these drawables. We will use it for a similar purpose on drawable collection to be able to maintain a list of multiple drawables of diffrent classes such as obstacles which are of diffrent classes because of templating.



The structure of the application will be to have a main function, that will control the logic of the game. The main function will instantiate the character and the collections for drawables (birds, obstacles and ground). The main function will have a loop for game ticks. In each tick, it will be draw the objects in the game, update their location and generate new items if applicable(obstacle, birds ground marks). The rest of the application will consist of the classes previously mentioned.
