#include "Console.h"

namespace Kernel
{
    namespace Graphics
    {
        void Console::Clear()
        {
            for (int i = 0; i < Width * Height; ++i)
            {
                elements[i].Character = 0;
                elements[i].Attribute = 0;
            }
        }

        void Console::Clear(char character)
        {
            for (int i = 0; i < Width * Height; ++i)
                elements[i].Character = character;
        }

        void Console::Clear(char character, uint8_t attribute)
        {
            for (int i = 0; i < Width * Height; ++i)
            {
                elements[i].Character = character;
                elements[i].Attribute = attribute;
            }
        }

        void Console::Clear(char character, ConsoleTextColor textColor, ConsoleBackgroundColor backgroundColor)
        {
            Clear(character, (uint8_t)textColor | (uint8_t)backgroundColor);
        }

        void Console::Scroll()
        {
            for (int y = 0; y < Height - 1; ++y)
            {
                for (int x = 0; x < Width; ++x)
                {
                    elements[(y * Width) + x] = elements[((y + 1) * Width) + x];
                }
            }

            position -= Width;
        }

        void Console::SetCursor(int position)
        {
            uint8_t lowByte = (uint8_t)position;
            uint8_t highByte = (uint8_t)(position >> 8);

            outb((uint8_t)14, 0x3D4);
            outb(highByte, 0x3D5);
            outb((uint8_t)15, 0x3D4);
            outb(lowByte, 0x3D5);
        }

        void Console::SetCursor(int x, int y)
        {
            int position = (y * Width) + x;
            uint8_t lowByte = (uint8_t)position;
            uint8_t highByte = (uint8_t)(position >> 8);

            outb((uint8_t)14, 0x3D4);
            outb(highByte, 0x3D5);
            outb((uint8_t)15, 0x3D4);
            outb(lowByte, 0x3D5);
        }

        void Console::PrintLine()
        {
            position += Width - (position % Width);

            if (position > Width * Height)
                Scroll();
        }

        void Console::Print(char character)
        {
            if (character == '\n')
            {
                position += Width - (position % Width);

                if (position > Width * Height)
                    position = 0;
            }
            else
            {
                elements[position].Character = character;
                elements[position].Attribute = (uint8_t)textColor | (uint8_t)backgroundColor;
                position++;
            }
        }

        void Console::Print(const char* value)
        {
            while (*value)
                Print(*value++);
        }

        void Console::PrintFormatted(const char* format)
        {
            while (*format != 0)
            {
                char character = *format++;

                if (character != '%')
                {
                    // If we have any character other than '%' just print it.
                    Print(character);
                }
                else
                {
                    character = *format++;

                    if (character == '%')
                    {
                        // This is an escape sequence ("%%") so print a '%'.
                        Print('%');
                        continue;
                    }
                    else
                    {
                        // Error: not enough arguments given.
                        return;
                    }
                }
            }
        }
    }
}