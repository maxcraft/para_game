#include "size.hpp"

namespace RayLib
{
    Size::Size( int width, int height )
    : width( width )
    , height( height )
    {}

    Size::Size( const Size &size )
    : width( size.width )
    , height( size.height )
    {}
}