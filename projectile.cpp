#include "projectile.hpp"
#include <cstdlib>
#include <new>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <raymath.h>


namespace Game
{
    Projectile::Projectile( const Vector2 startPos
        , float speed, float angle
        , float radius
        , float projectileLifespan )
    : m_position( startPos )
    , m_remainingTime( projectileLifespan )
    , m_radius( radius )
    {
        m_speed.x = speed * std::cos( angle );
        m_speed.y = speed * std::sin( angle );
    }

    Projectile::~Projectile()
    {
    }

    bool Projectile::draw( float time )
    {
        m_remainingTime = std::max( m_remainingTime - time, 0.0f );
        m_speed.y -= 9.82f * time * GetScreenHeight() / 200.0f;
        m_position.x -= m_speed.x * time;
        m_position.y -= m_speed.y * time;
        Vector2 oldPos = Vector2Add( m_position, Vector2Scale( m_speed, 0.06f ));

        // std::string txt = "Position: " + std::to_string( m_position.x ) + 'x' + std::to_string( m_position.y );
        //DrawText( txt.c_str(), 0, 20, 20, WHITE );
        //std::cerr << txt << std::endl;
        // TraceLog( LOG_INFO, txt.c_str() );

        DrawLineEx( m_position, oldPos, m_radius *1.6f, RED );

        DrawCircle( m_position.x
            , m_position.y
            , m_radius
            , WHITE );

        return 0.0f != m_remainingTime;
    }

    bool Projectile::draw( float time
        , std::function< bool( const Vector2 &position, const float radius ) > collide )
    {
        return draw( time ) && !collide( m_position, m_radius );
    }
} // namespace Game
