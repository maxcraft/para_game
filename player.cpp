#include "player.hpp"
#include <cmath>

#include <raylib.h>
#include "raylibpp/size.hpp"

namespace Game
{
    constexpr float coolDownTime = 0.1f;
    constexpr float cannonSpeed = M_PI_2;

    Player::Player()
    {
    }

    Player::~Player()
    {
    }

    void Player::reset()
    {
        m_cannonAngle = M_PI_2;
    }

    void Player::draw( const RayLib::Size &windowSize )
    {
        int side = windowSize.width / 20;
        int x = ( windowSize.width - side ) / 2;
        int y = ( windowSize.height - side );

        float gunLenght = side / 3.0f * 2.0f;
        m_endX = windowSize.width / 2 - gunLenght * std::cos( m_cannonAngle );
        m_endY = y - side / 2 - gunLenght  * std::sin( m_cannonAngle );


        DrawRectangle( x, y, side, side, BEIGE );
        DrawLineEx( { windowSize.width / 2.0f, y - side / 2.0f }, { m_endX, m_endY }, side / 8.0f,  DARKGRAY );
        DrawRectangle( x + side / 4, y - side / 2, side / 2, side / 2, PINK );
        DrawCircle( x + side / 2, y - side / 2, side / 4, PINK );
    }

    void Player::left( float time )
    {
        constexpr float minAngle = 0;
        m_cannonAngle = std::max( m_cannonAngle - cannonSpeed * time, minAngle );
    }

    void Player::right( float time )
    {
        constexpr float maxAngle = M_PI;
        m_cannonAngle = std::min( m_cannonAngle + cannonSpeed * time, maxAngle );
    }

    bool Player::ready()
    {
        return 0.0f == m_coolDownTime;
    }

    bool Player::ready( float time )
    {
        m_coolDownTime = std::max( m_coolDownTime - time, 0.0f );
        return ready();
    }

    Player::ShotInfo Player::shoot()
    {
        if( !ready() ) return {0,0};

        m_coolDownTime = coolDownTime;
        return { { m_endX, m_endY }, m_cannonAngle };
    }
}
