#include "screen.hpp"
#include <raylib.h>

namespace RayLib
{
    int Screen::width()
    {
        return GetScreenWidth();
    }

    int Screen::height()
    {
        return GetScreenHeight();
    }

} // namespace RayLib
