namespace Kernel
{
    namespace Graphics
    {
        template<typename T>
        void Console::FillConvertBuffer(char* buffer, LengthModifier lengthModifier, bool isSigned, int base, T value, bool isCapital)
        {
            if (isSigned)
            {
                switch (lengthModifier)
                {
                case LengthModifier::Char:
                    Utility::Convert::ToString(buffer, base, (signed char)value, isCapital);
                    break;

                case LengthModifier::Short:
                    Utility::Convert::ToString(buffer, base, (signed short)value, isCapital);
                    break;

                case LengthModifier::Int:
                    Utility::Convert::ToString(buffer, base, (signed int)value, isCapital);
                    break;

                case LengthModifier::Long:
                    Utility::Convert::ToString(buffer, base, (signed long)value, isCapital);
                    break;

                case LengthModifier::LongLong:
                    Utility::Convert::ToString(buffer, base, (signed long long)value, isCapital);
                    break;

                case LengthModifier::IntMax:
                    Utility::Convert::ToString(buffer, base, (intmax_t)value, isCapital);
                    break;

                case LengthModifier::PointerSize:
                    Utility::Convert::ToString(buffer, base, (signed size_t)value, isCapital);
                    break;

                case LengthModifier::PointerDifference:
                    Utility::Convert::ToString(buffer, base, (signed ptrdiff_t)value, isCapital);
                    break;

                case LengthModifier::LongDouble:
                    break;
                }
            }
            else
            {
                switch (lengthModifier)
                {
                case LengthModifier::Char:
                    Utility::Convert::ToString(buffer, base, (unsigned char)value, isCapital);
                    break;

                case LengthModifier::Short:
                    Utility::Convert::ToString(buffer, base, (unsigned short)value, isCapital);
                    break;

                case LengthModifier::Int:
                    Utility::Convert::ToString(buffer, base, (unsigned int)value, isCapital);
                    break;

                case LengthModifier::Long:
                    Utility::Convert::ToString(buffer, base, (unsigned long)value, isCapital);
                    break;

                case LengthModifier::LongLong:
                    Utility::Convert::ToString(buffer, base, (unsigned long long)value, isCapital);
                    break;

                case LengthModifier::IntMax:
                    Utility::Convert::ToString(buffer, base, (uintmax_t)value, isCapital);
                    break;

                case LengthModifier::PointerSize:
                    Utility::Convert::ToString(buffer, base, (size_t)value, isCapital);
                    break;

                case LengthModifier::PointerDifference:
                    Utility::Convert::ToString(buffer, base, (ptrdiff_t)value, isCapital);
                    break;

                case LengthModifier::LongDouble:
                    break;
                }
            }
        }

        template<typename T, typename... TArgs>
        void Console::PrintFormatted(const char* format, T value, TArgs... args)
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
                    char buffer[33];
                    LengthModifier lengthModifier = LengthModifier::Int;

                    character = *format++;

                    if (character == '%')
                    {
                        // This is an escape sequence ("%%") so print a '%'.
                        Print('%');
                        continue;
                    }

                    // Check to see if a size modifier is present.
                    switch (character)
                    {
                    case 'h':
                        character = *format++;

                        if (character == 'h')
                        {
                            character = *format++;
                            lengthModifier = LengthModifier::Char;
                        }
                        else
                        {
                            lengthModifier = LengthModifier::Short;
                        }
                        break;

                    case 'l':
                        character = *format++;

                        if (character == 'l')
                        {
                            character = *format++;
                            lengthModifier = LengthModifier::LongLong;
                        }
                        else
                        {
                            lengthModifier = LengthModifier::Long;
                        }
                        break;

                    case 'j':
                        character = *format++;
                        lengthModifier = LengthModifier::IntMax;
                        break;

                    case 'z':
                        character = *format++;
                        lengthModifier = LengthModifier::PointerSize;
                        break;

                    case 't':
                        character = *format++;
                        lengthModifier = LengthModifier::PointerDifference;
                        break;

                    case 'L':
                        character = *format++;
                        lengthModifier = LengthModifier::LongDouble;
                        break;
                    }

                    long long newValue = (long long)value;

                    // Figure out which conversion specifier we have, convert and print the value.
                    switch (character)
                    {
                    case 'c':
                        Print((char)newValue);
                        break;

                    case 's':
                        Print((const char* )newValue);
                        break;

                    case 'd':
                    case 'i':
                        FillConvertBuffer(buffer, lengthModifier, true, 10, newValue);
                        Print(buffer);
                        break;

                    case 'u':
                        FillConvertBuffer(buffer, lengthModifier, false, 10, newValue);
                        Print(buffer);
                        break;

                    case 'o':
                        FillConvertBuffer(buffer, lengthModifier, false, 8, newValue);
                        Print(buffer);
                        break;

                    case 'x':
                        FillConvertBuffer(buffer, lengthModifier, false, 16, newValue);
                        Print(buffer);
                        break;

                    case 'X':
                        FillConvertBuffer(buffer, lengthModifier, false, 16, newValue, true);
                        Print(buffer);
                        break;

                    case 'p':
                        FillConvertBuffer(buffer, lengthModifier, false, 16, newValue, true);
                        Print('0');
                        Print('x');
                        Print(buffer);
                        break;
                    }

                    PrintFormatted(format, args...);
                    return;
                }
            }
        }
    }
}