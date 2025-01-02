#include "game.hpp"
#include <cmath>
#include <string>

namespace Game
{
    Game::Game( RayLib::Window &wnd )
    : m_window( wnd )
    , m_player()
    , m_projectiles( 100, 1 )
    , m_copters( 50, 2 )
    , m_planes( 10, 2 )
    , m_sparks( 10000, 1 )
    , m_timeToNextPhase( GetRandomValue( 100, 500 ) / 10.0f )
    , m_timeToNextAircraft( 1.0f )
    , m_phase( 0 )
    , m_score( 0 )
    {
        auto windowSize = m_window.getRenderSize();
        m_copterTexture = Copter::drawTexture(
            { windowSize.width / 20.0f, windowSize.height / 25.0f } );
        
        m_planeTexture = Plane::drawTexture(
            { windowSize.width / 20.0f, windowSize.height / 30.0f }
        );

        reset();
    }

    Game::~Game()
    {
        UnloadRenderTexture( m_copterTexture );
        UnloadRenderTexture( m_planeTexture );
    }

    void Game::reset()
    {
        m_player.reset();
    }

    static void do_copters( Game &game, float time )
    {
        game.spawnCopters( time );
    }

    static void do_planes( Game &game, float time )
    {
        game.spawnPlanes( time );
    }

    static void wait_copters( Game &game, float time )
    {

    }

    static void wait_planes( Game &game, float time )
    {

    }

    static constexpr void( *phases[] )( Game &, float )
    {
        do_copters,
        //wait_copters,
        do_planes,
        //wait_planes
    };

    constexpr size_t phasesSize = sizeof( phases ) / sizeof( phases[ 0 ] );

    void Game::drawBg()
    {
        ClearBackground( BLACK );
        auto windowSize = m_window.getRenderSize();

        float time = GetFrameTime();

        if( IsKeyDown( KEY_LEFT ) ) m_player.left( time );
        if( IsKeyDown( KEY_RIGHT ) ) m_player.right( time );

        if( m_player.ready( time ) && ( IsKeyDown( KEY_SPACE ) || IsKeyDown( KEY_UP ) ) )
        {
            auto shotInfo = m_player.shoot();
            m_projectiles.spawn( shotInfo.position
                , windowSize.width / 2.5f
                , shotInfo.angle
                , windowSize.width / 400.0f );

            if( m_score ) --m_score;
        }

        m_timeToNextPhase -= time;
        // phase code

        if( m_timeToNextPhase <= 0.0f )
        {
            m_timeToNextPhase = GetRandomValue( 100, 500 ) / 10.0f;
            m_phase = ( m_phase + 1 ) % phasesSize;
            m_timeToNextAircraft = 10.0f;
        }

        phases[ m_phase ]( *this, time );
    }

    void Game::draw()
    {
        float time = GetFrameTime();
        auto windowSize = m_window.getRenderSize();
        
        m_copters.draw( time );
        m_planes.draw( time );
        m_projectiles.draw( time, [this]( const Vector2 &position, float radius ) -> bool
            {
                return collideCopters( position, radius ) || collidePlanes( position, radius );
            } );
        m_sparks.draw( time );
        m_player.draw( windowSize );

        std::string scoreStr = std::to_string( m_score );

        Font font = GetFontDefault();
        Vector2 textSize = MeasureTextEx( font, scoreStr.c_str(), 20.0f, 1.0f );
        DrawTextEx( font
            , scoreStr.c_str()
            , { ( windowSize.width - textSize.x ) / 2.0f, 0.0 }
            , 20.0f
            , 1.0f
            , GREEN );
    }

    void Game::spawnCopters( float time )
    {
        m_timeToNextAircraft -= time;

        // DrawText( std::to_string( m_timeToNextAircraft ).c_str(),100, 100, 20, GREEN );

        if( m_timeToNextAircraft <= 0.0f )
        {
            auto windowSize = m_window.getRenderSize();
            // TraceLog( LOG_INFO, "Ready to spawn a copter...\n" );
            m_timeToNextAircraft = GetRandomValue( 5, 20 ) / 10.0f;
            // m_timeToNextAircraft = 10000.0f;
            int direction = GetRandomValue( 0, 1 );

            float padding = windowSize.height / 100.0f;
            Vector2 size = { windowSize.width / 20.0f, windowSize.height / 25.0f };
            
            Vector2 position[] = {
                { windowSize.width + size.x / 2.0f, size.y + padding },
                { 0.0f - size.x / 2.0f, ( size.y + padding ) * 2.0f } };
            
            float speed[] = {-windowSize.width / 8.0f, windowSize.width / 8.0f };
            
            m_copters.spawn( speed[ direction ]
            , position[ direction ]
            , size
            , m_copterTexture );
        }
    }

    void Game::spawnPlanes( float time )
    {
        m_timeToNextAircraft -= time;

        // DrawText( std::to_string( m_timeToNextAircraft ).c_str(),100, 100, 20, GREEN );

        if( m_timeToNextAircraft <= 0.0f )
        {
            auto windowSize = m_window.getRenderSize();
            // TraceLog( LOG_INFO, "Ready to spawn a copter...\n" );
            m_timeToNextAircraft = GetRandomValue( 10, 20 ) / 10.0f;
            // m_timeToNextAircraft = 10000.0f;
            int direction = GetRandomValue( 0, 1 );

            float padding = windowSize.height / 100.0f;
            Vector2 size = { windowSize.width / 20.0f, windowSize.height / 30.0f };
            
            Vector2 position[] = {
                { windowSize.width + size.x / 2.0f, size.y + padding },
                { 0.0f - size.x / 2.0f, ( size.y + padding ) * 2.0f } };
            
            float speed[] = {-windowSize.width / 5.0f, windowSize.width / 5.0f };
            
            m_planes.spawn( speed[ direction ]
            , position[ direction ]
            , size
            , 1.2f
            , m_planeTexture );
        }
    }

    bool Game::collideCopters(const Vector2 &position, float radius)
    {
        auto copter = m_copters.detectHit( position, radius );

        if( !copter ) return false;

        m_copters.change( copter, 1 );
        copter->downed();

        indicateHit( position, radius );
        m_score += 10;
        return true;
    }

    bool Game::collidePlanes(const Vector2 &position, float radius)
    {
        auto plane = m_planes.detectHit( position, radius );

        if( !plane ) return false;

        m_planes.change( plane, 1 );
        plane->downed();

        indicateHit( position, radius );
        m_score += 10;
        return true;
    }

    void Game::indicateHit(const Vector2 &position, float radius)
    {
            auto windowSize = m_window.getRenderSize();
            //spawn sparks
            for( int i = 0, c = GetRandomValue( 20, 30 ); i < c; ++i )
            {
                int angle = GetRandomValue( 0, 359 );
                float speed = ( GetRandomValue( 0, 400 ) / 400.0 ) * windowSize.width / 7.0f;
                float lifeSpan = 2.0f + ( GetRandomValue( 0, 400 ) / 400.0 ) * 5.0f;

                m_sparks.spawn( position
                    , speed
                    , angle * M_PI / 180.0f
                    , windowSize.width / 800.0f
                    , lifeSpan );
            }
    }
}
