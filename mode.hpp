#pragma once

namespace Game
{
    class Mode
    {
        public:
            virtual void drawBg() = 0;
            virtual void draw() = 0;
    };
}
