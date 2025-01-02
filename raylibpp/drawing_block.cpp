#include "drawing_block.hpp"
#include <raylib.h>

namespace RayLib
{
    DrawingBlock::DrawingBlock()
    {
        BeginDrawing();

    }

    DrawingBlock::~DrawingBlock()
    {
        EndDrawing();
    }

} // namespace RayLib
