// SpriteManager.h

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class SpriteManager
{
public:
	static SpriteManager &	Get();
	static void				Destroy();

	int						LoadSprites();

	Sprite &				GetTitle()				{ return title; }
	Sprite &				GetBackground()			{ return background; }
	Sprite &				GetBoid()				{ return boid; }
	Sprite &				GetPlayer()				{ return player; }
	Sprite &				GetMinusIdle()			{ return minusIdle; }
	Sprite &				GetMinusPress()			{ return minusPress; }
	Sprite &				GetPlusIdle()			{ return plusIdle; }
	Sprite &				GetPlusPress()			{ return plusPress; }
	Sprite &				GetFollowOn()			{ return followOn; }
	Sprite &				GetFollowOff()			{ return followOff; }
	Sprite &				GetAvoidOn()			{ return avoidOn; }
	Sprite &				GetAvoidOff()			{ return avoidOff; }

private:
	static SpriteManager *	m_theInstance;

	SpriteManager() {}
	~SpriteManager() {}
	
	Sprite					title;
	Sprite					background;
	Sprite					boid;
	Sprite					player;
	Sprite					minusIdle;
	Sprite					minusPress;
	Sprite					plusIdle;
	Sprite					plusPress;
	Sprite					followOn;
	Sprite					followOff;
	Sprite					avoidOn;
	Sprite					avoidOff;
};

#define						MAX_WIDTH		1280
#define						MAX_HEIGHT		720

#endif // SPRITEMANAGER_H