// [assetloader.h]
// this is a class to manage our assets
#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <cstdlib>
#include <map>
#include <memory>
#include "SFML/Graphics.hpp"

class AssetLoader
{
public:
	// Singleton functions
	static AssetLoader &		GetInst();
	static void					DestroyInst();

	std::shared_ptr<sf::Image>	GetImage( const std::string &filename );
	void						UnloadImage( const std::string &filename );

private:
	AssetLoader();
	AssetLoader(const AssetLoader &other);
	~AssetLoader();

	std::map<std::string, std::shared_ptr<sf::Image> > m_imageDict;

	static AssetLoader *m_instance;
};

#endif // ASSETLOADER