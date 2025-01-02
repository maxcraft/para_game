#pragma once
#include "raylibpp/raylibpp.hpp"
#include "mode.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "aircrafts.hpp"

namespace Game
{
    class Game : public Mode
    {
        public:
            Game( RayLib::Window &wnd );
            ~Game();
            void reset();

            virtual void drawBg() override;
            virtual void draw() override;

            void spawnCopters( float time );
            void spawnPlanes( float time );

        private:
            RayLib::Window &m_window;
            Player m_player;
            //Projectiles m_projectiles;
            Entities< Projectile > m_projectiles;
            Entities< Copter > m_copters;
            Entities< Plane > m_planes;
            Entities< Projectile > m_sparks;
            float m_timeToNextPhase;
            float m_timeToNextAircraft;
            int m_phase;
            size_t m_score;

            RenderTexture2D m_copterTexture;
            RenderTexture2D m_planeTexture;

            bool collideCopters( const Vector2 &position, float radius );
            bool collidePlanes( const Vector2 &position, float radius );
            void indicateHit( const Vector2 &position, float radius );
    };
}
