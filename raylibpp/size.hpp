#pragma once

namespace RayLib
{
    struct Size
    {
        int width;
        int height;

        Size( int width, int height );
        Size( const Size &size );
    };

}