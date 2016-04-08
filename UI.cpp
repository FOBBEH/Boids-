#include "UI.h"

void UI::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

sf::Vector2f UI::GetPosition()
{
	return position;
}

void UI::RenderUI(RenderWindow &window)
{
	if (isMinus)
	{
		if (!isPressed)
		{
			SpriteManager::Get().GetMinusIdle().SetPosition( position );
			window.Draw( SpriteManager::Get().GetMinusIdle() );
		}
		else if (isPressed)
		{
			SpriteManager::Get().GetMinusPress().SetPosition( position );
			window.Draw( SpriteManager::Get().GetMinusPress() );
		}
	}
	else if (!isMinus)
	{
		if (!isPressed)
		{
			SpriteManager::Get().GetPlusIdle().SetPosition( position );
			window.Draw( SpriteManager::Get().GetPlusIdle() );
		}
		else if (isPressed)
		{
			SpriteManager::Get().GetPlusPress().SetPosition( position );
			window.Draw( SpriteManager::Get().GetPlusPress() );
		}
	}
	if (followButton)
	{
		if (!isPressed)
		{
			SpriteManager::Get().GetFollowOff().SetPosition( position );
			window.Draw( SpriteManager::Get().GetFollowOff() );
		}
		else if (isPressed)
		{
			SpriteManager::Get().GetFollowOn().SetPosition( position );
			window.Draw( SpriteManager::Get().GetFollowOn() );
		}
	}
	if (avoidButton)
	{
		if (!isPressed)
		{
			SpriteManager::Get().GetAvoidOff().SetPosition( position );
			window.Draw( SpriteManager::Get().GetAvoidOff() );
		}
		else if (isPressed)
		{
			SpriteManager::Get().GetAvoidOn().SetPosition( position );
			window.Draw( SpriteManager::Get().GetAvoidOn() );
		}
	}
}

void InitialiseUI(std::vector<UI> &manyUI)
{
	for (int i = 0; i < MAX_UI; ++i)
	{
		if (i % 2 == 0)
		{
			UI minusUI;
			minusUI.SetPosition( (MAX_WIDTH - 100.0f), (i * 25.0f) + 25.0f );
			minusUI.isMinus = true;
			minusUI.isPressed = false;
			minusUI.followButton = false;
			minusUI.avoidButton = false;
			manyUI.push_back(minusUI);
		}
		else if (i % 2 == 1)
		{
			UI plusUI;
			plusUI.SetPosition( (MAX_WIDTH - 50.0f), ((i - 1) * 25.0f) + 25.0f );
			plusUI.isMinus = false;
			plusUI.isPressed = false;
			plusUI.followButton = false;
			plusUI.avoidButton = false;
			manyUI.push_back(plusUI);
		}
	}

	UI followButton;
	followButton.SetPosition( (MAX_WIDTH - 100.0f), 125.0f );
	followButton.isMinus = false;
	followButton.isPressed = false;
	followButton.followButton = true;
	followButton.avoidButton = false;
	manyUI.push_back(followButton);

	UI avoidButton;
	avoidButton.SetPosition( (MAX_WIDTH - 100.0f), 175.0f );
	avoidButton.isMinus = false;
	avoidButton.isPressed = false;
	avoidButton.followButton = false;
	avoidButton.avoidButton = true;
	manyUI.push_back(avoidButton);
}