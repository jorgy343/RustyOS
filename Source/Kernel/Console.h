#pragma once
#include "Global.h"
#include "PrintFormattedEnums.h"
#include "Convert.h"
#include "Ports.h"
#include "ConsoleEnums.h"
#include "ConsoleElement.h"

namespace Kernel
{
    namespace Graphics
    {
        class Console
        {
        public:
            static const int Width = 80;
            static const int Height = 25;

        private:
            int position = 0;
            ConsoleElement* elements = (ConsoleElement*)0xB8000;

            ConsoleTextColor textColor = ConsoleTextColor::LightGrey;
            ConsoleBackgroundColor backgroundColor = ConsoleBackgroundColor::Black;

        public:
            void Clear();
            void Clear(char character);
            void Clear(char character, uint8_t attribute);
            void Clear(char character, ConsoleTextColor textColor, ConsoleBackgroundColor backgroundColor);

            void Scroll();

            void SetCursor(int position);
            void SetCursor(int x, int y);

            void PrintLine();

            void Print(char character);
            void Print(const char* value);

            void PrintFormatted(const char* format);
            template<typename T, typename... TArgs>
            void PrintFormatted(const char* format, T value, TArgs... args);

        private:
            template<typename T>
            void FillConvertBuffer(char* buffer, LengthModifier lengthModifier, bool isSigned, int base, T value, bool isCapital = false);
        };
    }
}

#include "Console.template.h"