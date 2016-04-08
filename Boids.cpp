#include "Boids.h"

#include <math.h>
#include <time.h>

void Boids::SetPosition(const sf::Vector2f &p)
{
	m_position = p;
}

void Boids::SetPosition(float deltaT)
{
	m_position += m_velocity * deltaT;
}

void Boids::SetVelocity(const sf::Vector2f &v)
{
	m_velocity = v;
}

void Boids::SetVelocity(std::vector<Boids> &manyBoids, sf::Vector2f &playerPos)
{
	sf::Vector2f a(0.0f, 0.0f), 
				 b(0.0f, 0.0f), 
				 c(0.0f, 0.0f), 
				 d(0.0f, 0.0f);

	a = Separation(manyBoids);
	b = Alignment(manyBoids);
	c = Cohesion(manyBoids);
	if (m_followPlayer && !m_avoidPlayer)			d = Follow(playerPos);
	else if (!m_followPlayer && m_avoidPlayer)		d = Avoid(playerPos);
	
	m_velocity = m_velocity + a + b + c + d;

	CreateRestrictions();
	LimitVelocity();
}

void Boids::SetRotation()
{
	// Rotation is based on the direction the boid is traveling:
	float theta = atan2( m_velocity.x, m_velocity.y );

	SpriteManager::Get().GetBoid().SetRotation( (-theta * 180 / 3.14f) + 90 );
}

void Boids::SetMaxVelocity(float f)
{
	m_maxVelocity = f;
}

void Boids::SetMaxSeparation(float f)
{
	m_maxSeparation = f;
}

void Boids::SetMaxDistance(float f)
{
	m_maxDistance = f;
}

void Boids::SetAlpha(float f)
{
	m_alpha = f;
}

void Boids::SetAvoidPlayer(bool b)
{
	m_avoidPlayer = b;
}

void Boids::SetFollowPlayer(bool b)
{
	m_followPlayer = b;
}

void Boids::SetOpacity()
{
	// Aqua colour as well!
	SpriteManager::Get().GetBoid().SetColor(sf::Color(0,255,255,m_alpha));
}

void Boids::CreateRestrictions()
{
	if ( m_position.x < 0 )				m_velocity.x += 10;
	if ( m_position.x > MAX_WIDTH )		m_velocity.x -= 10;
	if ( m_position.y < 0 )				m_velocity.y += 10;
	if ( m_position.y > MAX_HEIGHT )	m_velocity.y -= 10;
}

void Boids::LimitVelocity()
{
	float velMag = GetMagnitude(m_velocity);		// Magnitude of the velocity

	if ( velMag > m_maxVelocity && velMag > 0.0f )
	{
		m_velocity = (m_velocity / velMag) * m_maxVelocity;
	}
}

// Boids try to keep a small distance away from other objects (including other boids).
sf::Vector2f Boids::Separation(std::vector<Boids> &manyBoids)
{
	sf::Vector2f ret(0.0f, 0.0f);
	
	for (int i = 0; i < manyBoids.size(); ++i)
	{
		// Make sure that the boid isn't checking itself
		if ( m_position != manyBoids[i].m_position )
		{
			sf::Vector2f lengthV;
			//lengthV = position - manyBoids[i].position;
			lengthV = manyBoids[i].m_position - m_position;

			float lengthF = GetMagnitude( lengthV );

			if ( lengthF < m_maxSeparation )
			{
				ret -= lengthV;
			}
		}
	}

	return ret;
}

// Boids try to match velocity with near boids.
sf::Vector2f Boids::Alignment(std::vector<Boids> &manyBoids)
{
	sf::Vector2f ret(0.0f, 0.0f);
	//int nearBoids = 0;

	for (int i = 0; i < manyBoids.size(); ++i)
	{
		// Make sure that the boid isn't checking itself
		if ( m_position != manyBoids[i].m_position )
		{
			sf::Vector2f lengthV;
			lengthV = m_position - manyBoids[i].m_position;

			float lengthF = GetMagnitude( lengthV );

			//if ( lengthF < m_maxDistance )
			//{
				ret += manyBoids[i].m_velocity;
				//nearBoids++;
			//}
		}
	}

	// Average velocity
	ret = ret / ( (float)manyBoids.size() - 1.0f );
	//if ( nearBoids > 0 )		ret = ret / ( nearBoids - 1.0f );

	// Add 12.5% of perceived velocity to current boid's
	ret -= m_velocity;
	ret.x /= 8.0f;
	ret.y /= 8.0f;

	return ret;
}

// Boids try to fly towards the centre of mass of neighbouring boids.
sf::Vector2f Boids::Cohesion(std::vector<Boids> &manyBoids)
{
	sf::Vector2f ret(0.0f, 0.0f);
	//int nearBoids = 0;

	for (int i = 0; i < manyBoids.size(); ++i)
	{
		// Make sure that the boid isn't checking itself
		if ( m_position != manyBoids[i].m_position )
		{
			sf::Vector2f lengthV;
			lengthV = m_position - manyBoids[i].m_position;

			float lengthF = GetMagnitude( lengthV );

			//if ( lengthF < m_maxDistance )
			//{
				ret += manyBoids[i].m_position;
				//nearBoids++;
			//}
		}
	}

	// Average position
	ret = ret / ( (float)manyBoids.size() - 1.0f );
	//if ( nearBoids > 0 )		ret = ret / ( nearBoids - 1.0f );

	// Scale to 2%
	return ( ret - m_position ) / 200.0f;
}

sf::Vector2f Boids::Follow(sf::Vector2f &playerPos)
{
	// Scale to 0.25%
	return ( playerPos - m_position ) / 400.0f;
}

sf::Vector2f Boids::Avoid(sf::Vector2f &playerPos)
{
	sf::Vector2f ret(0.0f, 0.0f);

	sf::Vector2f lengthV;
	lengthV = m_position - playerPos;

	float lengthF = GetMagnitude( lengthV );

	if ( lengthF < MAX_AVOID )
	{
		// RUN AWAY!
		return lengthV;
	}
	else
	{
		// Return nothing if it's out of the distance
		return ret;
	}
}

void Boids::UpdateBoid(RenderWindow &window, std::vector<Boids> &manyBoids, sf::Vector2f &playerPos, bool &followOn, bool &avoidOn, float deltaT )
{
	SetVelocity( manyBoids, playerPos );
	SetPosition(deltaT);
	SetRotation();
	
	// Changing the alpha based on distance:	
	if ( GetMagnitude( sf::Vector2f( playerPos - m_position ) ) > 100.0f )	m_alpha--;
	else																	m_alpha += 25;
	if ( m_alpha >= 255 )													m_alpha = 255;
	if ( m_alpha <= 100 )													m_alpha = 100;

	if ( window.GetInput().IsMouseButtonDown(Mouse::Left) )
	{
		if ( playerPos.x >= 1180.0f && playerPos.x <= 1255.0f )
		{
			// Arrow buttons
			if ( playerPos.x <= 1205.0f )
			{
				// Minus values
				if ( playerPos.y >= 25.0f && playerPos.y <= 50.0f )			m_maxSeparation--;
				if ( playerPos.y >= 75.0f && playerPos.y <= 100.0f )		m_maxVelocity--;
			}
		
			else if ( playerPos.x >= 1230.0f )
			{
				// Plus values
				if ( playerPos.y >= 25.0f && playerPos.y <= 50.0f )			m_maxSeparation++;
				if ( playerPos.y >= 75.0f && playerPos.y <= 100.0f )		m_maxVelocity++;
			}

			// Follow button
			if ( playerPos.y >= 125.0f && playerPos.y <= 150.0f )
			{
				if (followOn)				m_followPlayer = true;
				else if (!followOn)			m_followPlayer = false;
			}

			// Avoid button
			if ( playerPos.y >= 175.0f && playerPos.y <= 200.0f )
			{
				if (avoidOn)				m_avoidPlayer = true;
				else if (!avoidOn)			m_avoidPlayer = false;
			}
		}
	}
}

void Boids::RenderBoid(RenderWindow &window)
{
	SpriteManager::Get().GetBoid().SetPosition( m_position );
	SetOpacity();
	window.Draw( SpriteManager::Get().GetBoid() );
}

void InitialiseBoids(std::vector<Boids> &manyBoids)
{
	// Seed the random generator
	srand( time(NULL) );
	
	for (int i = 0; i < MAX_BOIDS; ++i)
	{
		Boids myBoid;
		
		// Randomise position
		float randomPosX = rand() % ( MAX_WIDTH + 1 );
		float randomPosY = rand() % ( MAX_HEIGHT + 1 );
		myBoid.SetPosition( sf::Vector2f(randomPosX, randomPosY) );
		
		// Randomise velocity
		float randomVelX = rand() % 200 / 100 - 1;		// -1 to 1
		float randomVelY = rand() % 200 / 100 - 1;
		myBoid.SetVelocity( sf::Vector2f(randomVelX, randomVelY) );

		myBoid.SetMaxSeparation( 10.0f );
		myBoid.SetMaxVelocity( 10.0f );
		myBoid.SetMaxDistance( 20.0f );
		myBoid.SetAlpha( 255 );
		myBoid.SetAvoidPlayer( false );
		myBoid.SetFollowPlayer( false );

		manyBoids.push_back( myBoid );
	}
}

// Magnitude function
float GetMagnitude(const sf::Vector2f &v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}