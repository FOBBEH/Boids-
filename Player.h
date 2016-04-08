#ifndef PLAYER_H
#define PLAYER_H

#include "SpriteManager.h"

class Player
{
public:
	void			SetPlayerPosition(float x, float y);
	sf::Vector2f	GetPlayerPosition();

	void			UpdatePlayer(RenderWindow &window);
	void			RenderPlayer(RenderWindow &window);

private:
	sf::Vector2f	position;
};

#endif // PLAYER_H