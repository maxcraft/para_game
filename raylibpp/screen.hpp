#pragma once
#include "size.hpp"

namespace RayLib
{
    class Screen
    {
        public:
            static int width();
            static int height();
            
            inline static Size size()
            {
                return { width(), height() };
            }

    };
} // namespace RayLib
