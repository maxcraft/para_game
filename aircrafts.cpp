#include "aircrafts.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>

namespace Game
{
    Aircraft::Aircraft( float speed
        , const Vector2 &position
        , const Vector2 &dimentions
        , RenderTexture2D &texture )
    : m_speed( { speed, 0 } )
    , m_position( position )
    , m_dimentions( dimentions )
    , m_state( 0 )
    , m_texture( texture )
    {
    }

    Aircraft::~Aircraft()
    {
    }

    // bool Aircraft::draw( float time )
    // {
    //     return false;
    // }

    bool Aircraft::advance( float time )
    {
        m_position.x += m_speed.x * time;
        return m_position.x > ( 0.0 - m_dimentions.x / 2.0f )
            && m_position.x < ( GetScreenWidth() + m_dimentions.x / 2.0f );
    }

    bool Aircraft::down( float time )
    {
        m_speed.y += 9.82 * time * m_dimentions.y;
        m_position.y += m_speed.y * time;
        return m_position.y < ( GetScreenHeight() + m_dimentions.y / 2.0f );
    }

    void Aircraft::do_draw( float angle )
    {
        // DrawRectangle( m_position.x - m_dimentions.x / 2.0f
        //     , m_position.y - m_dimentions.y / 2.0f
        //     , m_dimentions.x
        //     , m_dimentions.y
        //     , Fade( GRAY, 0.5f ) );

        float sign = 1 + ( -2 * std::signbit( m_speed.x ) );
        float textureWidth = static_cast< float >( m_texture.texture.width );

        DrawTexturePro( m_texture.texture
            , { 0.0f
                , 0.0f
                ,  sign * textureWidth
                , -static_cast< float >( m_texture.texture.height ) }
            , { m_position.x //- m_dimentions.x / 2.0f
                , m_position.y //- m_dimentions.y / 2.0f
                , m_dimentions.x
                , m_dimentions.y }
            , { m_dimentions.x / 2.0f , m_dimentions.y / 2.0f }
            , angle
            , WHITE );
    }

    static bool copterAdvanceNormal( Copter &copter, float time )
    {
        return copter.advance( time );
    }

    static bool copterAdvanceDowned( Copter &copter, float time )
    {
        return copter.advance( time ) && copter.down( time );
    }

    static constexpr bool( *copterAdvance[] )( Copter &, float )
    {
        copterAdvanceNormal,
        copterAdvanceDowned
    };

    Copter::Copter( float speed, const Vector2 &position, const Vector2 &dimentions, RenderTexture2D &texture )
    : Aircraft( speed, position, dimentions, texture )
    {
    }

    Copter::~Copter()
    {
    }

    bool Copter::draw( float time )
    {
        if( !copterAdvance[ m_state ]( *this, time ) ) return false;

        // DrawText( text.c_str(), 100, 200, 10, GREEN );
        // TraceLog( LOG_INFO, text.c_str() );

        // DrawRectangle( m_position.x - m_dimentions.x / 2.0f
        //     , m_position.y - m_dimentions.y / 2.0f
        //     , m_dimentions.x
        //     , m_dimentions.y
        //     , Fade( GRAY, 0.5f ) );

        // float sign = 1 + ( -2 * std::signbit( m_speed.x ) );
        // float textureWidth = static_cast< float >( m_texture.texture.width );

        // DrawTexturePro( m_texture.texture
        //     , { 0.0f
        //         , 0.0f
        //         ,  sign * textureWidth
        //         , -static_cast< float >( m_texture.texture.height ) }
        //     , { m_position.x - m_dimentions.x / 2.0f
        //         , m_position.y - m_dimentions.y / 2.0f
        //         , m_dimentions.x
        //         , m_dimentions.y }
        //     , { 0.0f, 0.0f }
        //     , 0.0f
        //     , WHITE );

        do_draw();

        return true;
    }

    void Copter::downed()
    {
        m_state = 1;
    }

    bool Copter::isHit( const Vector2 &position, float radius )
    {
        return CheckCollisionCircleRec( position, radius, { m_position.x - m_dimentions.x / 2
            , m_position.y - m_dimentions.y / 2
            , m_dimentions.x
            , m_dimentions.y} );
    }

    RenderTexture2D Copter::drawTexture( Vector2 dimentions )
    {
        RenderTexture2D texture = LoadRenderTexture( dimentions.x, dimentions.y );
        BeginTextureMode( texture );
        ClearBackground( Fade( BLACK, 0.0f ) );

        Vector2 position = { dimentions.x / 2.0f, dimentions.y / 2.0f };

        // body
        float length = dimentions.x / 1.8f;
        float height = dimentions.y / 2.0f + dimentions.y / 8.0f;
        float x = position.x + dimentions.x / 2.0f - length;
        float y = position.y + dimentions.y / 2.0f - height;

        DrawRectangleRounded( { x
            , y
            , length
            , height
        }
        , 1.0f
        , 0
        , GREEN );

        //tail
        length = dimentions.x / 2.0f;
        height = dimentions.y / 8.0f;
        x = position.x - dimentions.x / 2.0f;
        y = position.y;// - height;
        
        DrawRectangle( x
            , y
            , length
            , height
            , GREEN );

        DrawLineEx( { position.x - dimentions.x / 2.1f
            , position.y - dimentions.y / 3.0f }
        , { position.x - dimentions.x / 2.5f 
            , position.y + dimentions.y / 8.0f }
        , dimentions.x / 8.0f
        , GREEN );
        
        //rotor
        length = dimentions.x / 1.3f;
        height = dimentions.y / 12.0f;
        x = position.x + dimentions.x / 2.0f - length;
        y = position.y - dimentions.y / 2.0f;
        
        DrawRectangle( x
            , y
            , length
            , height
            , Fade( GREEN, 0.7f ) );
        
        //rotor shaft
        // use rotor center as x position
        x = position.x + dimentions.x / 2.0f - length / 2.0f;
        length = dimentions.x / 15.0f;
        height = dimentions.y / 3.0f;
        y = position.y - dimentions.y / 2.0f;
        
        DrawRectangle( x
            , y
            , length
            , height
            , Fade( GREEN, 0.7f ) );


        EndTextureMode();
        return texture;
    }

    static bool planeAdvanceNormal( Plane &plane, float time )
    {
        return plane.advance( time );
    }

    static bool planeAdvanceDowned( Plane &plane, float time )
    {
        return plane.advance( time ) && plane.down( time );
    }

    static constexpr bool( *planeAdvance[] )( Plane &, float )
    {
        planeAdvanceNormal,
        planeAdvanceDowned
    };

    
    Plane::Plane( float speed
        , const Vector2 &position
        , const Vector2 &dimentions
        , float dragCoef
        , RenderTexture2D &texture )
    : Aircraft( speed, position, dimentions, texture )
    , m_dragCoef( dragCoef )
    {
    }
    
    Plane::~Plane()
    {
    }

    bool Plane::draw( float time )
    {
        if( !planeAdvance[ m_state ]( *this, time ) ) return false;
        
        float sign = 1 + ( -2 * std::signbit( m_speed.x ) );

        float angle = sign * std::atan2( m_speed.y, std::abs( m_speed.x ) ) * 180.0f / M_PIf;

        // DrawRectanglePro( { m_position.x //- m_dimentions.x / 2.0f
        //     , m_position.y //- m_dimentions.y / 2.0f
        //     , m_dimentions.x
        //     , m_dimentions.y}
        //     , { m_dimentions.x / 2.0f, m_dimentions.y / 2.0f } /*m_position*/
        //     , angle
        //     , Fade( LIGHTGRAY, 0.1f ) );

        do_draw( angle );

        return true;
    }

    void Plane::downed()
    {
        m_state = 1;
    }

    bool Plane::isHit( const Vector2 &position, float radius )
    {
        return CheckCollisionCircleRec( position, radius, { m_position.x - m_dimentions.x / 2
            , m_position.y - m_dimentions.y / 2
            , m_dimentions.x
            , m_dimentions.y} );
    }

    bool Plane::down( float time )
    {
        m_speed.x -= m_dragCoef * time;

        return Aircraft::down( time );
    }

    RenderTexture2D Plane::drawTexture( Vector2 dimentions) 
    {
        RenderTexture2D texture = LoadRenderTexture( dimentions.x, dimentions.y );
        BeginTextureMode( texture );
        ClearBackground( Fade( BLACK, 0.0f ) );

        float height = dimentions.y / 2.5f;
        DrawRectangleRec( { 0.0f
            , dimentions.y - height
            , dimentions.x / 1.5f
            , height }
            , LIGHTGRAY );

        DrawCircleSector( dimentions //{ 0.0f, 0.0f }
            , dimentions.x / 2.5f
            , 210.0f
            , 180.0f
            , 10
            , LIGHTGRAY );

        DrawLineEx( { 0.0f, 0.0f }
            , { dimentions.x / 5.0f, dimentions.y }
            , dimentions.x / 7.0f
            , LIGHTGRAY );

        EndTextureMode();
        return texture;
    }
}
