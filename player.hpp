#pragma once

#include <raylib.h>
#include "raylibpp/size.hpp"

namespace Game
{
    class Player
    {
        public:
            Player();
            ~Player();
            void reset();
            void draw( const RayLib::Size &windowSize );
            void left( float time );
            void right( float time );
            bool ready();
            bool ready( float time );

            struct ShotInfo
            {
                Vector2 position;
                float angle;
            };

            ShotInfo shoot();

        private:
            float m_cannonAngle;
            float m_coolDownTime;
            float m_endX, m_endY;
    };
}