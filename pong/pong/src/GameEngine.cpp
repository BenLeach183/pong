#include "GameEngine.h"
#include <SFML/Audio.hpp>

// !!! BRIEF DESCRIPTION IS IN MAIN.CPP

GameEngine::GameEngine(sf::RenderWindow& window)
	// Initialise the objects with constructors
	: m_window(window), 
	m_paddle1(sf::Vector2f(20, window.getSize().y / 2.f), 10, 100, "paddle.png"),
	m_paddle2(sf::Vector2f(window.getSize().x - 20.f, window.getSize().y - 100.f), 10, 100, "paddle.png"),
	m_ball(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), 8, 400.f, sf::Color::White),
	m_enemy(window, m_ball, m_paddle2),
	m_powerUp(m_powerUp.Drunk, sf::Vector2f(0, 0), 40.f, 40.f, "powerup_anim.png", m_shader, m_paddle1, m_ball, m_music)
{
	// seed the pseudo random number generator
	srand(time(NULL));

	// set starting scores to 0
	m_p1Score = 0;
	m_p2Score = 0;

	// set initial game state to intro
	m_gStates = GameStates::intro;

	// set text styles
	m_font.loadFromFile(".\\assets\\fonts\\digital-7.ttf");
	m_hud.setFont(m_font);
	m_hud.setCharacterSize(50);
	m_hud.setFillColor(sf::Color::White);

	// set hud position
	m_hud.setPosition((m_window.getSize().x / 2.f) - 45.f, 10);

	// set default paddle speeds
	m_paddle1.setSpeed(800.0);
	m_paddle2.setSpeed(800.0);
	
	// load the shaders, if they fail display error
	if (!loadShaders()) {
		std::cout << "Shaders failed to load!" << std::endl;
	}

	// create the render texture,  if they fail display error
	if (!m_renderTexture.create(window.getSize().x, window.getSize().y)) {
		std::cout << "Failed to create render texture!" << std::endl;
	}

	// load the sound effects and music,  if they fail display error
	if (!loadSound()) {
		std::cout << "Audio failed to load!" << std::endl;
	}

	// spawn an initial power up, as time uniform isn't passed in until playing it will remain grey
	spawnPowerUp();
}

void GameEngine::draw()
{
	// clear renders
	m_window.clear();
	m_renderTexture.clear(sf::Color::Color(23, 23, 23, 255));

	// draw paddles and ball to render texture
	m_paddle1.draw(m_renderTexture);
	m_paddle2.draw(m_renderTexture);
	m_ball.draw(m_renderTexture);

	// pass the power up shader into power up draw
	m_powerUp.draw(m_renderTexture, &m_powerUpShader);

	// draw the render texture to window
	sf::Sprite windowSprite(m_renderTexture.getTexture());
	// use the shader to render the texture to the window
	// the shader has a uniform called drunk that can enable drunk mode
	m_window.draw(windowSprite, &m_shader);

	// draw hud to window and display
	m_window.draw(m_hud);
	m_window.display();
}

void GameEngine::update()
{
	// update hud
	std::stringstream ss;
	switch (m_gStates)
	{

	// game intro state
	case GameEngine::intro:
		// display prompt to start game
		ss << "Press the Space\nkey to start";
		break;

	// game playing state
	case GameEngine::playing:
		// display the current score
		ss << m_p1Score << " - " << m_p2Score;
		break;

	// game over state
	case GameEngine::gameOver:
		// display the winner
		if (m_bIsP1Winner) {
			ss << "Player 1 wins";
		}
		else {
			ss << "Player 2 wins";
		}

		// display prompt to play again
		ss << "\n\nPress the Space\nkey to start again.";
		break;
	default:
		break;
	}
		
	// display the string stream
	m_hud.setString(ss.str());
}

// runs every tick - called from main
void GameEngine::run()
{
	// value for delta time
	float dt;

	// game loop, runs whilst window is open
	while (m_window.isOpen())
	{
		// calculate delta time
		dt = m_frameClock.restart().asSeconds();
		m_timeTrack += dt;

		// manage inputs
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// manage all inputs other then close window
			manageInputs(event);

			// check for window close or esc pressed to delete the power up objects, close window and return out of run()
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				m_powerUp.deleteObjects();
				m_window.close();
				return;
			}
		}

		// game state machine
		switch (m_gStates)
		{
		// intro state
		case GameEngine::intro:

			// reset the clock for spawning in power ups
			m_powerUpClock.restart();
			break;

		// playing state
		case GameEngine::playing:
			// increase the background music when playing game
			m_music.setVolume(50.0f);

			// pass total elapsed time into the shaders as a uniform
			m_shader.setUniform("time", (float)m_clock.getElapsedTime().asSeconds());
			m_powerUpShader.setUniform("time", (float)m_clock.getElapsedTime().asSeconds());

			// move the ball
			m_ball.move(dt, m_window);

			// check for collisions
			checkCollisions();

			// if no power up is enabled, and the pwoer up respawn clock hits 20s spawn a new power up
			if (!m_powerUp.getEnabled() && m_powerUpClock.getElapsedTime().asSeconds() >= 20.0f) spawnPowerUp();

			// Check for if the inputs are pressed and move the paddle
			if (m_bIsUpPressed && !m_bIsDownPressed) {
				// move towards top of screen
				m_paddle1.move(dt, 0);
			}
			else if (m_bIsDownPressed && !m_bIsUpPressed) {
				// move towards bottom of screen
				m_paddle1.move(dt, m_window.getSize().y);
			}

			// update the enemy ai
			updateAi(dt);

			// check if anyone has won
			checkScores();

			break;

		// Game over state
		case GameEngine::gameOver:
			// set the background music to lower volume
			m_music.setVolume(25.0f);

			// disable any current power up
			m_powerUp.disable();

			// reset the player scores
			m_p1Score = 0;
			m_p2Score = 0;
			break;
		default:
			break;
		}

		// update hud
		update();
		// draw shapes to screen
		draw();
		// update power ups
		m_powerUp.update();
	}
}

// load shader files into shader variables
bool GameEngine::loadShaders() {
	// if they fail to load return false
	if (!m_shader.loadFromFile(".\\assets\\shaders\\drunk.vs", ".\\assets\\shaders\\drunk.fs")) return false;
	if (!m_powerUpShader.loadFromFile(".\\assets\\shaders\\powerup.vs", ".\\assets\\shaders\\powerup.fs")) return false;

	return true;
}

// load sound effects
bool GameEngine::loadSound() {
	// load the sound effects into buffers, if they fail return false
	if (!m_ballBuffer.loadFromFile(".\\assets\\audio\\beep.ogg")) return false;
	if (!m_ballWallBuffer.loadFromFile(".\\assets\\audio\\wall.ogg")) return false;
	if (!m_lossBuffer.loadFromFile(".\\assets\\audio\\loss.ogg")) return false;
	if (!m_winBuffer.loadFromFile(".\\assets\\audio\\win.ogg")) return false;
	if (!m_powerUpBuffer.loadFromFile(".\\assets\\audio\\powerup.ogg")) return false;

	// set the buffers for the sounds
	m_ballSound.setBuffer(m_ballBuffer);
	m_ballWallSound.setBuffer(m_ballWallBuffer);
	m_lossSound.setBuffer(m_lossBuffer);
	m_winSound.setBuffer(m_winBuffer);
	m_powerUpSound.setBuffer(m_powerUpBuffer);

	// load the background music and play it on loop, if it fails to load return false
	if (!m_music.openFromFile(".\\assets\\audio\\music_loop.ogg")) return false;
	m_music.play();
	m_music.setVolume(20.0f);
	m_music.setLoop(true);

	return true;
}

// spawn power up in a random position on the screen, with a random power type, and enable them
void GameEngine::spawnPowerUp() {
	m_powerUp.setType();
	m_powerUp.setEnabled(true);
	m_powerUp.setPosition(sf::Vector2f(50 + (rand() % (m_window.getSize().x - 100)), 50 + (rand() % (m_window.getSize().y - 100))));
}

// manage the inputs
void GameEngine::manageInputs(sf::Event event) {
	// check for window resize event to update view and render texture
	if (event.type == sf::Event::Resized)
	{
		// get new window width and height, minimum size is 800, 600
		int width = (event.size.width < 800) ? 800 : event.size.width;
		int height = (event.size.height < 600) ? 600 : event.size.height;

		// set window size (in case the values were below the cap)
		m_window.setSize(sf::Vector2u(width, height));

		// create a new render texture with new dimensions
		m_renderTexture.create(width, height);

		// create a new view with the new window dimensions
		sf::FloatRect visibleArea(0, 0, width, height);
		m_window.setView(sf::View(visibleArea));

		// move the right hand paddle
		m_paddle2.setHorizontalPosition(width - 20.f);
	}

	// check for space input to move game state to playing
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		m_gStates = GameStates::playing;

	// check for input for up and down, set up and down flags when pressed and released
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) m_bIsUpPressed = true;
		if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) m_bIsDownPressed = true;
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) m_bIsUpPressed = false;
		if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) m_bIsDownPressed = false;
	}
}

void GameEngine::updateAi(float dt) {
	// move ai when ball is moving right
	// check velocity to see if it's positive
	if (m_ball.getVelocity().x > 0) {
		m_enemy.move(dt);
	}

	// update the target for ai to move to randomly
	// after a random period of time
	if (m_timeTrack >= m_targetTime) {
		// update the target position for ai
		m_enemy.updateTarget();

		// reset the the variable keeping track of time
		m_timeTrack = 0.0f;

		// calculate a new random period of time for next check
		m_targetTime = (float)(rand() % 100) / 250.0f;
	}
}

void GameEngine::checkScores() {
	// test if either score has reached the max score
	if (m_p1Score >= m_maxScore || m_p2Score >= m_maxScore) {
		// calculate the winner
		if (m_p1Score > m_p2Score)
		{
			// play win sound and set win flag to true
			m_winSound.play();
			m_bIsP1Winner = true;
		}
		else {
			// play loss sound and set win flag to false
			m_lossSound.play();
			m_bIsP1Winner = false;
		}

		// move the game state to gameOver
		m_gStates = GameEngine::gameOver;
	}
}

void GameEngine::checkCollisions() {
	// check if ball collides with far right
	if (m_ball.getPosition().x + m_ball.getRadius() * 2 >= m_window.getSize().x)
	{
		// move the ball back to centre
		m_ball.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

		// update velocity to move ball left
		m_ball.updateVelocity(-1);

		// play the hit wall sound
		m_ballWallSound.play();

		// award player 1 a point
		m_p1Score++;
	}
	// check if ball collides with far left
	else if (m_ball.getPosition().x <= 0)
	{
		// move ball to centre
		m_ball.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
		
		// update velocity moving ball right
		m_ball.updateVelocity(1);

		// play the hit wall sound
		m_ballWallSound.play();

		// award player 2 a point
		m_p2Score++;
	}

	// check if ball hits right paddle
	if (m_paddle2.getBounds().intersects(m_ball.getBounds())) {
		// reverse ball direction
		m_ball.updateVelocity(-1);

		// play ball hit paddle sound
		m_ballSound.play();
	}

	// check if ball hits left paddle
	if (m_paddle1.getBounds().intersects(m_ball.getBounds())) {
		// reverse ball direction
		m_ball.updateVelocity(1);

		// play ball hit paddle sound
		m_ballSound.play();
	}

	// check if ball collides with power up
	if (m_powerUp.getBounds().intersects(m_ball.getBounds())) {
		// if power up isn't enabled ignore
		if (!m_powerUp.getEnabled()) return;

		// reset the power up respawn clock
		m_powerUpClock.restart();
		m_powerUpSound.play();

		// run the hit function in power up class
		m_powerUp.hit();
	}
}