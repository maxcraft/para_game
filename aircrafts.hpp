#pragma once

#include <raylib.h>

namespace Game
{
    class Aircraft
    {
        public:
            Aircraft( float speed
                , const Vector2 &position
                , const Vector2 &dimentions
                , RenderTexture2D &texture );
            virtual ~Aircraft();
            virtual bool draw( float time ) = 0;
            virtual void downed() = 0;
            virtual bool isHit( const Vector2 &position, float radius ) = 0;
            virtual bool advance( float time );
            virtual bool down( float time );

        protected:
            Vector2 m_speed;
            Vector2 m_position;
            Vector2 m_dimentions;
            int m_state;
            RenderTexture2D m_texture;

            void do_draw( float angle = 0.0f );
    };

    class Copter : public Aircraft
    {
        public:
            Copter( float speed
                , const Vector2 &position
                , const Vector2 &dimentions
                , RenderTexture2D &texture );
            virtual ~Copter();
            virtual bool draw( float time ) override;
            virtual void downed() override;
            virtual bool isHit( const Vector2 &position, float radius );
            static RenderTexture2D drawTexture( Vector2 dimentions );
        
    };

    class Plane : public Aircraft
    {
        public:
            Plane( float speed
                , const Vector2 &position
                , const Vector2 &dimentions
                , float dragCoef
                , RenderTexture2D &render );
            virtual ~Plane();
            virtual bool draw( float time ) override;
            virtual void downed() override;
            virtual bool isHit( const Vector2 &position, float radius );
            virtual bool down( float time ) override;
            static RenderTexture2D drawTexture( Vector2 dimentions );
        private:
            float m_dragCoef;
    };

} // namespace Game
