#include "window.hpp"
#include <raylib.h>

namespace RayLib
{
    Window::Window( int width, int height, const std::string &title )
    : m_title( title )
    {
        InitWindow( width, height, m_title.c_str() );
    }

    Window::Window( const Size &size, const std::string &title )
    : m_title( title )
    {
        InitWindow( size.width, size.height, m_title.c_str() );
    }

    Window::~Window()
    {
        CloseWindow();
    }

    bool Window::shouldClose()
    {
        return WindowShouldClose();
    }

    bool Window::isReady()
    {
        return IsWindowReady();
    }

    bool Window::isFullScreen()
	{
        return IsWindowFullscreen();
	}

    bool Window::isHidden()
	{
        return IsWindowHidden();
	}

    bool Window::isMinimized()
	{
        return IsWindowMinimized();
	}

    bool Window::isMaximized()
	{
        return IsWindowMaximized();
	}

    bool Window::isFocused()
	{
        return IsWindowFocused();
	}

    bool Window::isResized()
	{
        return IsWindowResized();
	}

    bool Window::isState( unsigned int flag )
	{
        return IsWindowState( flag );
	}

    void Window::setState( unsigned int flag )
	{
        SetWindowState( flag );
	}

    void Window::clearState( unsigned int flag )
	{
        ClearWindowState( flag );
	}


    void Window::toggleFullscreen()
	{
        ToggleFullscreen();
	}

    void Window::toggleBorderlessWindowed()
	{
        ToggleBorderlessWindowed();
	}

    void Window::maximize()
	{
        MaximizeWindow();
	}

    void Window::minimize()
	{
        MinimizeWindow();
	}

    void Window::restore()
	{
        RestoreWindow();
	}


    void Window::setIcon()
	{
	}

    void Window::setIcons()
	{
	}

    void Window::setTitle( const std::string &title )
	{
        m_title = title;
        SetWindowTitle( m_title.c_str() );
	}

    void Window::setPosition( int x, int y )
	{
        SetWindowPosition( x,  y );
	}

    // void SetWindowIcon(Image image);                            // Set icon for window (single image, RGBA 32bit)
    // void SetWindowIcons(Image *images, int count);              // Set icon for window (multiple images, RGBA 32bit)


    void Window::setMonitor( int monitor )
	{
        SetWindowMonitor( monitor );
	}

    void Window::setMinSize( int width, int height )
	{
        SetWindowMinSize( width, height );
	}

    void Window::setMaxSize( int width, int height )
	{
        SetWindowMaxSize( width, height );
	}

    void Window::setSize( int width, int height )
	{
        SetWindowSize( width, height );
	}

    void Window::setOpacity( float opacity )
	{
        SetWindowOpacity( opacity );
	}

    void Window::setFocused()
	{
        SetWindowFocused();
	}

    void *Window::getHandle()
	{
        return GetWindowHandle();
	}


    int Window::getRenderWidth()
	{
        return GetRenderWidth();
	}

    int Window::getRenderHeight()
	{
        return GetRenderHeight();
	}

}