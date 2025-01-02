#pragma once
#include "size.hpp"

#include <string>

namespace RayLib
{
    class Window
    {
        public:
            Window( int width, int height, const std::string &title );
            Window( const Size &size, const std::string &title );
           ~Window();

            bool shouldClose();
            bool isReady();
            bool isFullScreen();
            bool isHidden();
            bool isMinimized();
            bool isMaximized();
            bool isFocused();
            bool isResized();
            bool isState( unsigned int flag );
            void setState( unsigned int flag );
            void clearState( unsigned int flag );

            void toggleFullscreen();
            void toggleBorderlessWindowed();
            void maximize();
            void minimize();
            void restore();

            void setIcon();
            void setIcons();
            void setTitle( const std::string &title );
            void setPosition( int x, int y );

            void setMonitor( int monitor );
            void setMinSize( int width, int height );
            
            inline void setMinSize( const Size &size )
            {
                setMinSize( size.width, size.height );
            }

            void setMaxSize( int width, int height );
            
            inline void setMaxSize( const Size &size )
            {
                setMaxSize( size.width, size.height );
            }

            void setSize( int width, int height );
            
            inline void setSize( const Size &size )
            {
                setSize( size.width, size.height );
            }

            void setOpacity( float opacity );
            void setFocused();
            void *getHandle();

            int getRenderWidth();
            int getRenderHeight();

            inline Size getRenderSize()
            {
                return { getRenderWidth(), getRenderHeight() };
            }


        private:
            std::string m_title;
    };
    // Vector2 GetWindowPosition();                            // Get window position XY on monitor
    // Vector2 GetWindowScaleDPI();                            // Get window scale DPI factor
    // void SetClipboardText(const char *text);                    // Set clipboard text content
    // const char *GetClipboardText();                         // Get clipboard text content
    // Image GetClipboardImage();                              // Get clipboard image
    // void EnableEventWaiting();                              // Enable waiting for events on EndDrawing(), no automatic event polling
    // void DisableEventWaiting();                             // Disable waiting for events on EndDrawing(), automatic events polling

}