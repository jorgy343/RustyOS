#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Graphics
    {
        enum class ConsoleTextColor : uint8_t
	    {
		    Black = 0x0,
		    Blue,
		    Green,
		    Cyan,
		    Red,
		    Magenta,
		    Brown,
		    LightGrey,
		    DarkGrey,
		    LightBlue,
		    LightGreen,
		    LightCyan,
		    LightRed,
		    LightMagenta,
		    LightBrown,
		    White
	    };

	    enum class ConsoleBackgroundColor : uint8_t
	    {
		    Black = 0x00,
		    Blue = 0x10,
		    Green = 0x20,
		    Cyan = 0x30,
		    Red = 0x40,
		    Magenta = 0x50,
		    Brown = 0x60,
		    LightGrey = 0x70,
		    DarkGrey = 0x80,
		    LightBlue = 0x90,
		    LightGreen = 0xA0,
		    LightCyan = 0xB0,
		    LightRed = 0xC0,
		    LightMagenta = 0xD0,
		    LightBrown = 0xE0,
		    White = 0xF0
	    };
    }
}