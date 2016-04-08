#include "Player.h"

void Player::SetPlayerPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

sf::Vector2f Player::GetPlayerPosition()
{
	return position;
}

void Player::UpdatePlayer(RenderWindow &window)
{
	SetPlayerPosition( window.GetInput().GetMouseX(), window.GetInput().GetMouseY() );
	
	SpriteManager::Get().GetPlayer().SetPosition( GetPlayerPosition() );
}

void Player::RenderPlayer(RenderWindow &window)
{
	window.Draw( SpriteManager::Get().GetPlayer() );
}