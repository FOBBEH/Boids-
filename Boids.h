#ifndef BOIDS_H
#define BOIDS_H

#include <vector>

#include "SpriteManager.h"

class Boids
{
public:
	void			SetPosition(const sf::Vector2f &p);				// To set the initial position
	void			SetPosition(float deltaT);						// Adjusts position from velocity
	void			SetVelocity(const sf::Vector2f &v);				// To set the initial velocity
	void			SetVelocity(std::vector<Boids> &manyBoids,
								sf::Vector2f &playerPos );			// Adjusts velocity from Separation/Alignment/Cohesion functions
	void			SetRotation();
	void			SetMaxVelocity(float f);
	void			SetMaxSeparation(float f);
	void			SetMaxDistance(float f);
	void			SetAlpha(float f);
	void			SetAvoidPlayer(bool b);
	void			SetFollowPlayer(bool b);

	void			SetOpacity();

	sf::Vector2f	GetPosition()			{ return m_position; }
	sf::Vector2f	GetVelocity()			{ return m_velocity; }
	float			GetMaxVelocity()		{ return m_maxVelocity; }
	float			GetMaxSeparation()		{ return m_maxSeparation; }
	float			GetMaxDistance()		{ return m_maxDistance; }
	unsigned int	GetAlpha()				{ return m_alpha; }
	bool			GetAvoidPlayer()		{ return m_avoidPlayer; }
	bool			GetFollowPlayer()		{ return m_followPlayer; }

	void			CreateRestrictions();
	void			LimitVelocity();

	sf::Vector2f	Separation(std::vector<Boids> &manyBoids);
	sf::Vector2f	Alignment(std::vector<Boids> &manyBoids);
	sf::Vector2f	Cohesion(std::vector<Boids> &manyBoids);
	sf::Vector2f	Follow(sf::Vector2f &playerPos);
	sf::Vector2f	Avoid(sf::Vector2f &playerPos);

	void			UpdateBoid(RenderWindow &window, 
							   std::vector<Boids> &manyBoids, 
							   sf::Vector2f &playerPos, 
							   bool &followOn, 
							   bool &avoidOn,
							   float deltaT );
	void			RenderBoid(RenderWindow &window);

private:
	sf::Vector2f	m_position, m_velocity;
	float			m_maxVelocity, m_maxSeparation, m_maxDistance;
	unsigned int	m_alpha;
	bool			m_avoidPlayer, m_followPlayer;
};

void				InitialiseBoids(std::vector<Boids> &manyBoids);
float				GetMagnitude(const sf::Vector2f &v);

#define				MAX_BOIDS		1000
#define				MAX_AVOID		150.0f



#endif // BOIDS_H