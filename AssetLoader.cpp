#include "assetloader.h"
#include "core.h"
#include <assert.h>

// Define static variables:
AssetLoader *AssetLoader::m_instance = NULL;


AssetLoader::AssetLoader()
{
}

AssetLoader::AssetLoader(const AssetLoader &other)
{
	// This should never happen!
	assert(false);
	exit(0);
}

AssetLoader::~AssetLoader()
{
	// Probably should go through dictionaries and delete everything!
	m_imageDict.clear();
}

AssetLoader & AssetLoader::GetInst()
{
	if (m_instance == NULL)
	{
		m_instance = new AssetLoader;
	}

	return *m_instance;
}

void AssetLoader::DestroyInst()
{
	del_ptr( m_instance );
}

std::shared_ptr<sf::Image> AssetLoader::GetImage( const std::string &filename )
{
	// The job of this function is twofold:
	// 1. check if image is already loaded
	// 2. return existing or new image based on point 1.

	// Check if loaded:
	if ( m_imageDict.find( filename ) != m_imageDict.end() )
	{
		return m_imageDict[ filename ];
	}

	// Didn't find the image; load it and add to dictionary, then return it.
	m_imageDict[ filename ] = std::shared_ptr<sf::Image>( new sf::Image() );
	m_imageDict[ filename ]->LoadFromFile( filename );
	return m_imageDict[ filename ];
}

void AssetLoader::UnloadImage( const std::string &filename )
{
	// Unload a specific image:
	m_imageDict.erase( filename );
}