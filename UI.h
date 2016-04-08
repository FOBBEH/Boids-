#ifndef UI_H
#define UI_H

#include <vector>

#include "SpriteManager.h"

class UI
{
public:
	bool			isMinus;
	bool			isPressed;
	bool			followButton;
	bool			avoidButton;
	
	void			SetPosition(float x, float y);
	sf::Vector2f	GetPosition();

	void			UpdateUI(RenderWindow &window);
	void			RenderUI(RenderWindow &window);

private:
	sf::Vector2f	position;
};

void				InitialiseUI(std::vector<UI> &manyUI);

#define				MAX_UI	4

#endif // UI_H