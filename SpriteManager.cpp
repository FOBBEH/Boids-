#include <iostream>
#include <cstdlib>

#include "SpriteManager.h"
#include "AssetLoader.h"

SpriteManager *SpriteManager::m_theInstance = NULL;

SpriteManager &SpriteManager::Get()
{
	if (m_theInstance == NULL)
	{
		m_theInstance = new SpriteManager;
	}

	return *m_theInstance;
}

void SpriteManager::Destroy()
{
	AssetLoader::GetInst().UnloadImage( "data/title.png" );
	AssetLoader::GetInst().UnloadImage( "data/background.png" );
	AssetLoader::GetInst().UnloadImage( "data/boids.png" );
	AssetLoader::GetInst().UnloadImage( "data/ui.png" );

	delete m_theInstance;
	m_theInstance = NULL;
}

int SpriteManager::LoadSprites()
{
	// Prepare our images:
	shared_ptr<Image> titleImage = AssetLoader::GetInst().GetImage( "data/title.png" );
	shared_ptr<Image> backgroundImage = AssetLoader::GetInst().GetImage( "data/background.png" );
	shared_ptr<Image> boidImage = AssetLoader::GetInst().GetImage( "data/boids.png" );
	shared_ptr<Image> uiImage = AssetLoader::GetInst().GetImage( "data/ui.png" );

	// Set the sprites to the images:
	title			= *titleImage.get();
	background		= *backgroundImage.get();
	boid			= *boidImage.get();
	player			= *boidImage.get();
	minusIdle		= *uiImage.get();
	minusPress		= *uiImage.get();
	plusIdle		= *uiImage.get();
	plusPress		= *uiImage.get();
	followOn		= *uiImage.get();
	followOff		= *uiImage.get();
	avoidOn			= *uiImage.get();
	avoidOff		= *uiImage.get();

	title.SetSubRect(IntRect(0,0,320,180));			// Co-ordinates to select sprite TOP LEFT, BOTTOM RIGHT
	title.SetCenter(160,90);						// Co-ordinates to set the center of the sprite

	background.SetSubRect(IntRect(0,0,1280,720));
	background.SetCenter(0,0);

	boid.SetSubRect(IntRect(0,0,5,5));
	boid.SetCenter(2.5,2.5);

	player.SetSubRect(IntRect(5,0,10,5));
	player.SetCenter(2.5,2.5);

	plusIdle.SetSubRect(IntRect(0,0,25,25));
	plusIdle.SetCenter(0,0);

	plusPress.SetSubRect(IntRect(0,25,25,50));
	plusPress.SetCenter(0,0);

	minusIdle.SetSubRect(IntRect(25,0,50,25));
	minusIdle.SetCenter(0,0);

	minusPress.SetSubRect(IntRect(25,25,50,50));
	minusPress.SetCenter(0,0);

	followOn.SetSubRect(IntRect(50,0,125,25));
	followOn.SetCenter(0,0);

	followOff.SetSubRect(IntRect(50,25,125,50));
	followOff.SetCenter(0,0);

	avoidOn.SetSubRect(IntRect(125,0,200,25));
	avoidOn.SetCenter(0,0);

	avoidOff.SetSubRect(IntRect(125,25,200,50));
	avoidOff.SetCenter(0,0);

	return EXIT_SUCCESS;
}