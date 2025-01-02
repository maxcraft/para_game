#pragma once
#include <raylib.h>
#include "size.hpp"
#include <string>

namespace RayLib
{
    class Monitor
    {
    private:
        int m_monitor;
    public:
        Monitor( int monitor );
        ~Monitor();

    static int count();
    static Monitor current();

    Vector2 position();
    int width();
    int height();
    inline Size size()
    {
        return { width(), height() };
    }

    int physWidth();
    int physHeight();
    inline Size physSize()
    {
        return { physWidth(), physHeight() };
    }

   int rate();
    std::string name();

    };
    

} // namespace RayLib
