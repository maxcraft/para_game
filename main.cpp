#include <iostream>
#include <vector>
#include <memory>
#include <stack>

#include "raylibpp/raylibpp.hpp"
#include "raylibpp/drawing_block.hpp"
#include "mode.hpp"
#include "menu.hpp"
#include "game.hpp"

constexpr int modeMenu = 1;
constexpr int modeGame = 0;

static void do_nothing()
{

}

int main( int argc, char **argv )
{
	RayLib::Window wnd( 800, 600, "raylib [core] example - basic window" );
	RayLib::Size scrSize = RayLib::Monitor::current().size();
	wnd.setSize( scrSize );
	wnd.toggleFullscreen();
	SetTargetFPS( 100 );


	volatile bool shouldClose = false;
	std::stack< int > modeHistory;
	modeHistory.push( modeMenu );

	std::vector< std::unique_ptr< Game::Mode > > modes;

	auto &game = modes.emplace_back( new Game::Game( wnd ) );
	Game::Game *gamePtr = static_cast< Game::Game *>( game.get() );

	auto &menu = modes.emplace_back( new Game::Menu( wnd ) );
	Game::Menu *menuPtr = static_cast< Game::Menu * >( menu.get() );
	menuPtr->appendMenu( "New Game", [ &modeHistory, &gamePtr ]()
						{
							// clear history
							while( 0 != modeHistory.size() )
							{
								modeHistory.pop();
							}
							modeHistory.push( modeGame );
							gamePtr->reset();
							HideCursor();
							DisableCursor();
						})
		.appendMenu( "Settings", do_nothing )
		.appendMenu( "Credits", do_nothing )
		.appendMenu( "Exit", [ &shouldClose ]()
					{
						shouldClose = true;
					});

	while( !shouldClose )
	{
		if( IsKeyPressed( KEY_ESCAPE ) )
		{
			// show menu
			if( modeHistory.size() > 1 )
			{
				modeHistory.pop();
				if( modeGame == modeHistory.top() )
				{
					DisableCursor();
					HideCursor();
				}
			}
			else
			{
				modeHistory.push( modeMenu );
				EnableCursor();
				ShowCursor();
			}
		}

		int mode = modeHistory.top();
		RayLib::DrawingBlock blk;

		modes[ mode ]->drawBg();
		modes[ mode ]->draw();

		DrawFPS( 0, 0 );

		// end of drawing block.
	}

	// CloseWindow();

	return 0;

}
