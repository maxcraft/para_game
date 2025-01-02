#pragma once
#include <raylib.h>
#include <cstddef>
#include <functional>

#include "entities.hpp"

namespace Game
{
    class Projectile
    {
    private:
        Vector2 m_speed;
        Vector2 m_position;
        float m_remainingTime;
        float m_radius;

    public:
        Projectile( const Vector2 startPos
            , float speed
            , float angle
            , float radius
            , float projectileLifespan = 3.5f );
        ~Projectile();
        bool draw( float time );
        bool draw( float time,
            std::function< bool( const Vector2 &position, const float radius )> collide );
    };
} // namespace Game
