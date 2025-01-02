#pragma once

#include <functional>
#include <vector>

#include <raylib.h>

#include "mode.hpp"
#include "raylibpp/window.hpp"

namespace Game
{
    class Menu : public Mode
    {
        public:
            Menu( RayLib::Window &wnd, int defaultItem = 0
            , float fontSize = 20, float spacing = 1.0 );
            virtual ~Menu();

            virtual void drawBg() override;
            virtual void draw() override;

            Menu &appendMenu( const std::string &text, std::function< void()> action );
            size_t size();

            inline bool empty()
            {
                return ( size() == 0 );
            }

        private:
            Font m_font;
            float m_fontSize;
            float m_spacing;
            RayLib::Window &m_window;
            int m_selectedItem;
            std::vector< std::pair< std::string, std::function< void()> > > m_items;
    };
}