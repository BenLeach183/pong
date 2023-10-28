#include <iostream>
#include "GameEngine.h"

//			PONG
// Control the left paddle, using W & S or Up & Down
//
// The current max score is set to 5
//
// Power ups spawn every 20 seconds, they currently do one of 2 things
// Drunk mode - will make the screen go wobbly, and distort the music
// Speedy mode - will make the ball and your paddle move fast, and speeds up the music 
//
// The power up has an animation when you hit it, and will show you an icon for
// the type of power up it is.
//
// The music gets louder when the game starts
//
// The shader code is in assets\shaders
//
// It can handle window resizing, it can't go smaller then (800, 600)

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong", sf::Style::Default);
	
	// create the game engine object
	GameEngine gameEngine(window);

	// call the run function
	gameEngine.run();
}