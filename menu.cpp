#include "menu.hpp"
#include <raylib.h>

namespace Game
{
    Menu::Menu( RayLib::Window &wnd, int defaultItem
            , float fontSize, float spacing )
    : Mode()
    , m_fontSize( fontSize )
    , m_spacing( spacing )
    , m_window( wnd )
    , m_selectedItem( defaultItem )
    {
        m_font = GetFontDefault();
    }

    Menu::~Menu()
    {}

    void Menu::drawBg()
    {
        ClearBackground( BLACK );
        int menuSize = static_cast< int >( size() );

        if( IsKeyPressed( KEY_UP ) || IsKeyPressedRepeat( KEY_UP ) )
        {
            m_selectedItem += menuSize - 1;
            m_selectedItem %= menuSize;
            // m_selectedItem = std::max( --m_selectedItem, 0 );
        }
        else if( IsKeyPressed( KEY_DOWN ) || IsKeyPressedRepeat( KEY_DOWN ) )
        {
            // m_selectedItem = std::min( ++m_selectedItem, static_cast< int >( size() ) - 1 );
            ++m_selectedItem;
            m_selectedItem %= menuSize;
        }
        else if( IsKeyDown( KEY_ENTER ) )
        {
            m_items[ m_selectedItem ].second();
        }
    }

    void Menu::draw()
    {
        float vertSpacing = m_fontSize / 4.0f;
        int menuHeight = m_fontSize * m_items.size() + vertSpacing * ( m_items.size() - 1 );

        auto scrSize = m_window.getRenderSize();
        Vector2 place = { .x = 0, .y = ( scrSize.height - menuHeight ) / 2.0f };

        for( int i = 0, c = m_items.size(); i < c; ++i )
        {
            Vector2 textSize = MeasureTextEx(
                m_font,
                m_items[ i ].first.c_str(),
                m_fontSize,
                m_spacing );

                place.x = ( scrSize.width - textSize.x ) / 2;

            if( i == m_selectedItem )
            {
                DrawRectangle( place.x - vertSpacing / 2
                , place.y - vertSpacing / 2
                , textSize.x + vertSpacing
                , textSize.y + vertSpacing
                , WHITE );

                DrawTextEx( m_font
                , m_items[ i ].first.c_str()
                , place
                , m_fontSize
                , m_spacing
                , DARKGRAY );
            }
            else
            {
                DrawTextEx( m_font
                , m_items[ i ].first.c_str()
                , place
                , m_fontSize
                , m_spacing
                , LIGHTGRAY );
            }

            place.y += vertSpacing + m_fontSize;
        }
    }

    Menu &Menu::appendMenu(const std::string &text, std::function<void()> action)
    {
        m_items.emplace_back( text, action );
        return *this;
    }

    size_t Menu::size()
    {
        return m_items.size();
    }
}