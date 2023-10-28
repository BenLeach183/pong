#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Enemy.h"
#include "PowerUpObject.h"

class GameEngine
{
private:
	// create the variables for display
	sf::RenderWindow& m_window;
	sf::Font m_font;
	sf::Text m_hud;
	sf::Shader m_powerUpShader;
	sf::Shader m_shader;
	sf::RenderTexture m_renderTexture;

	// create the sound effect buffers
	sf::SoundBuffer m_ballBuffer;
	sf::SoundBuffer m_ballWallBuffer;
	sf::SoundBuffer m_lossBuffer;
	sf::SoundBuffer m_winBuffer;
	sf::SoundBuffer m_powerUpBuffer;

	// create the sound effects
	sf::Sound m_ballSound;
	sf::Sound m_ballWallSound;
	sf::Sound m_lossSound;
	sf::Sound m_winSound;
	sf::Sound m_powerUpSound;

	// create the background music variable
	sf::Music m_music;

	// create the clocks
	// frameClock - used to calculate delta time (dt)
	// powerUpClock - used to measure period between power up respawns
	// clock - used for total game time to pass into shaders
	sf::Clock m_frameClock;
	sf::Clock m_powerUpClock;
	sf::Clock m_clock;

	// game objects
	Paddle m_paddle1;
	Paddle m_paddle2;
	Ball m_ball;
	PowerUpObject m_powerUp;

	// enemy ai controller
	Enemy m_enemy;

	// track the scores
	int m_p1Score;
	int m_p2Score;
	static const int m_maxScore = 5;

	// enum for game states
	enum GameStates {intro, playing, gameOver};
	GameStates m_gStates;

	// inputs
	bool m_bIsDownPressed = false;
	bool m_bIsUpPressed = false;

	// winner flag
	bool m_bIsP1Winner = false;

	// reaction times for ai
	float m_timeTrack = 0.0f;
	float m_targetTime = 0.0f;

	// setting up functions
	bool loadShaders();
	bool loadSound();

	// respawn power up
	void spawnPowerUp();

	// called in playing state
	void manageInputs(sf::Event event);
	void checkCollisions();
	void updateAi(float dt);
	void checkScores();

public:
	// constructor, takes in the window created in main
	GameEngine(sf::RenderWindow& window);

	// calls each draw function for each game object
	void draw();

	// update the hud
	void update();

	// runs each tick
	void run();
};

