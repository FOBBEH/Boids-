//-----------------------------------------------------------------------------
// Joseph Khanh Dat Ho
// GAM302 AI Technique: Boids
// QANTM College Melbourne
//
// Desc: ᕼEᒪᒪO TᗯITᑕᕼ ᑕᕼᗩT, ᗪOᑎ ᑭEᑭᑭEᖇOᑎI ᕼEᖇE, ᑕᗩᑭTᗩIᑎ Oᖴ TᕼE 
//		 ᗩᑎTI-ᖇIOT ᑭOᒪIᑕE. ᔕTOᑭ ᖇIOTIᑎG ᖇIGᕼT ᑎOᗯ, Oᖇ YOᑌ ᗯIᒪᒪ ᗷE 
//		 TOᑭᗪEᑕKEᗪ. YOᑌ ᕼᗩᐯE ᗷEEᑎ ᗯᗩᖇᑎEᗪ. ᑎO ᑭᑌEᖇTO ᖇIᑕO ᑭᗩᔕTEᖇIᑎO 
//		 ᗪE ᑎIᖇO TᗩᖇEᑎTIᑎO .
//
//       Copyright (C) Dat Corporation. Pls no coperino pastarino.
//-----------------------------------------------------------------------------

#include "SFML/Audio.hpp" 
#include "cmath" 
#include "kf/kf_log.h" 
#include "qgf2d/system.h"
#include "qgf2d/anim.h"

#include <fstream>

#include "GameStateManager.h"
#include "SpriteManager.h"
#include "AssetLoader.h"
#include "Player.h"
#include "Boids.h"
#include "UI.h"

using namespace std; 
using namespace qgf; 
using namespace kf; 
using namespace sf; 

std::vector<Boids>	boidList;
std::vector<UI>		UIList;

void Initialise()
{
	InitialiseBoids(boidList);
	InitialiseUI(UIList);
}

void Update(RenderWindow &window, Player &p, bool &followOn, bool &avoidOn, float deltaT)
{
	// Update player and boid positions
	p.UpdatePlayer(window);
	for (int i = 0; i < boidList.size(); ++i)
	{
		boidList[i].UpdateBoid(window, boidList, p.GetPlayerPosition(), followOn, avoidOn, deltaT);
	}
	SpriteManager::Get().GetTitle().SetPosition( MAX_WIDTH/2.0f, MAX_HEIGHT/2.0f );
	SpriteManager::Get().GetBackground().SetPosition( 0.0f, 0.0f );
}

void Render(RenderWindow &window, bool &drawTitle, Player &p, Drawable &a, Drawable &b)
{
	// Draw everything to the screen:
	window.Clear();
	
	// Draw title/background first:
	if (drawTitle)		window.Draw( SpriteManager::Get().GetTitle() );
	else				window.Draw( SpriteManager::Get().GetBackground() );
	
	// Layer the rest on top:
	for (int i = 0; i < UIList.size(); ++i)
	{
		UIList[i].RenderUI(window);
	}
	for (int i = 0; i < boidList.size(); ++i)
	{
		boidList[i].RenderBoid(window);
	}
	p.RenderPlayer(window);
	window.Draw(a);
	window.Draw(b);

	window.Display();
}

int main() 
{ 
    // This will initialise the QGF2D folders: 
    //initDirectory();
  
    // Set up logging: 
    Log::getDefault().addCout(); 
    Log::getDefault().addFile("Boids.log"); 
    kf_log("AI Technique: Boids");

	ShowCursor(false);

    // Set up window resolution and title: 
    RenderWindow window(VideoMode(MAX_WIDTH, MAX_HEIGHT, 32), "AI Technique: Boids");

	// Set up window icon:
	Image icon;
	icon.LoadFromFile( "data/icon.jpg" );
	window.SetIcon( icon.GetWidth(), icon.GetHeight(), icon.GetPixelsPtr() );

    // Creating our sprite objects: 
	SpriteManager::Get().LoadSprites();

	// Set game state and variables:
	GameState myGameState;
	myGameState = Title;

	// Create the player:
	Player myPlayer;
	
	bool filler = false;			// FILLER, JUST TO FILL IN THE GAP FOR MISSING UILIST
	bool drawTitle = true;			// Draw title (on) or background (off)
	bool timeBuffer = false;		// Buffer for follow/avoid buttons so they don't go nuts

	while (window.IsOpened()) 
	{  
		Event ev; 
		while (window.GetEvent(ev)) 
		{ 
			if ((ev.Type == Event::Closed)) 
			{ 
			    window.Close(); 
			    break; 
			} 
		}

		// Delta time:
		//float deltaT = window.GetFrameTime();			// Getting slow results
		float deltaT = 1.0f;

		// Text:
		std::stringstream separationStream, velocityStream;
		String separation, velocity;
		char separationStr[256], velocityStr[256];

		if (boidList.size() > 0)
		{
			separationStream << "Separation: " << boidList[0].GetMaxSeparation();
			separationStream.getline(separationStr, 256);
			separation.SetPosition(1000, 25);
			separation.SetText(separationStr);
			separation.SetSize(20);

			velocityStream << "Velocity: " << boidList[0].GetMaxVelocity();
			velocityStream.getline(velocityStr, 256);
			velocity.SetPosition(1000, 75);
			velocity.SetText(velocityStr);
			velocity.SetSize(20);
		}
		
		switch (myGameState)
		{
		case Title:
			Update(window, myPlayer, filler, filler, deltaT);
			Render(window, drawTitle, myPlayer, separation, velocity);

			if ( window.GetInput().IsMouseButtonDown(Mouse::Left) )
			{
				myGameState = Game;
				drawTitle = false;
				Initialise();
			}
			break;
		case Game:
			Update(window, myPlayer, UIList[4].isPressed, UIList[5].isPressed, deltaT);		// UI[4] follow, UI[5] avoid
			Render(window, drawTitle, myPlayer, separation, velocity);

			// Change the UI when the buttons are pressed:
			if ( window.GetInput().IsMouseButtonDown(Mouse::Left) )
			{
				if ( myPlayer.GetPlayerPosition().x >= 1180.0f && myPlayer.GetPlayerPosition().x <= 1255.0f )
				{
					// Arrow buttons
					if ( myPlayer.GetPlayerPosition().x <= 1205.0f )
					{
						// Minus values
						if ( myPlayer.GetPlayerPosition().y >= 25.0f && myPlayer.GetPlayerPosition().y <= 50.0f )		UIList[0].isPressed = true;
						if ( myPlayer.GetPlayerPosition().y >= 75.0f && myPlayer.GetPlayerPosition().y <= 100.0f )		UIList[2].isPressed = true;
					}
					else if ( myPlayer.GetPlayerPosition().x >= 1230.0f )
					{
						// Plus values
						if ( myPlayer.GetPlayerPosition().y >= 25.0f && myPlayer.GetPlayerPosition().y <= 50.0f )		UIList[1].isPressed = true;
						if ( myPlayer.GetPlayerPosition().y >= 75.0f && myPlayer.GetPlayerPosition().y <= 100.0f )		UIList[3].isPressed = true;
					}

					// Follow button
					if ( myPlayer.GetPlayerPosition().y >= 125.0f && myPlayer.GetPlayerPosition().y <= 150.0f )
					{
						if ( !timeBuffer )
						{
							if (UIList[4].isPressed)			UIList[4].isPressed = false;
							else if (!UIList[4].isPressed)		UIList[4].isPressed = true;
							timeBuffer = true;
						}
					}

					// Avoid button
					if ( myPlayer.GetPlayerPosition().y >= 175.0f && myPlayer.GetPlayerPosition().y <= 200.0f )
					{
						if ( !timeBuffer )
						{
							if (UIList[5].isPressed)			UIList[5].isPressed = false;
							else if (!UIList[5].isPressed)		UIList[5].isPressed = true;
							timeBuffer = true;
						}
					}
				}
			}
			if ( !window.GetInput().IsMouseButtonDown(Mouse::Left) )
			{
				// Reset stuff when the mouse button is released
				for (int i = 0; i < UIList.size(); ++i)
				{
					// ONLY the arrow buttons
					if (!UIList[i].followButton && !UIList[i].avoidButton)
					{
						UIList[i].isPressed = false;
					}
				}
				timeBuffer = false;
			}

			break;
		}
    }
	
	SpriteManager::Get().Destroy();
	return 0;
}