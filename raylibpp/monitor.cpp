#include "monitor.hpp"
#include <raylib.h>

namespace RayLib
{
    Monitor::Monitor( int monitor )
    : m_monitor( monitor )
    {
    }
    
    Monitor::~Monitor()
    {
    }

    int Monitor::count()
    {
        return GetMonitorCount();
    }

    Monitor Monitor::current()
    {
        return { GetCurrentMonitor() };
    }

    Vector2 Monitor::position()
	{
        return GetMonitorPosition( m_monitor );
	}

    int Monitor::width()
	{
        return GetMonitorWidth( m_monitor );
	}

    int Monitor::height()
	{
        return GetMonitorHeight( m_monitor );
	}

    int Monitor::physWidth()
	{
        return GetMonitorPhysicalWidth( m_monitor );
	}

    int Monitor::physHeight()
	{
        return GetMonitorPhysicalHeight( m_monitor );
	}

    int Monitor::rate()
	{
        return GetMonitorRefreshRate( m_monitor );
	}

    std::string Monitor::name()
	{
        return { GetMonitorName( m_monitor ) };
	}

} // namespace RayLib
