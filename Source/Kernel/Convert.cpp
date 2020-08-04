#include "Convert.h"

namespace Kernel
{
    namespace Utility
    {
        void Convert::ToString(char* buffer, int base, char value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, signed char value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, unsigned char value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, short value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, unsigned short value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, int value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, unsigned int value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, long value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, unsigned long value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, long long value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, int base, unsigned long long value, bool isCapital)
        {
            ToStringFromNumeral(buffer, base, value, isCapital);
        }

        void Convert::ToString(char* buffer, bool value, bool isCapital)
        {
            if (value)
            {
                if (isCapital)
                    *buffer++ = 'T';
                else
                    *buffer++ = 't';

                *buffer++ = 'r';
                *buffer++ = 'u';
                *buffer++ = 'e';
                *buffer++ = 0;
            }
            else
            {
                if (isCapital)
                    *buffer++ = 'F';
                else
                    *buffer++ = 'f';

                *buffer++ = 'a';
                *buffer++ = 'l';
                *buffer++ = 's';
                *buffer++ = 'e';
                *buffer++ = 0;
            }
        }

        char Convert::ToChar(const char* buffer, int base)
        {
            return ToNumeralFromString<char>(buffer, base);
        }

        signed char Convert::ToSignedChar(const char* buffer, int base)
        {
            return ToNumeralFromString<signed char>(buffer, base);
        }

        unsigned char Convert::ToUnsignedChar(const char* buffer, int base)
        {
            return ToNumeralFromString<unsigned char>(buffer, base);
        }

        short Convert::ToShort(const char* buffer, int base)
        {
            return ToNumeralFromString<short>(buffer, base);
        }

        unsigned short Convert::ToUnsignedShort(const char* buffer, int base)
        {
            return ToNumeralFromString<unsigned short>(buffer, base);
        }

        int Convert::ToInt(const char* buffer, int base)
        {
            return ToNumeralFromString<int>(buffer, base);
        }

        unsigned int Convert::ToUnsignedInt(const char* buffer, int base)
        {
            return ToNumeralFromString<unsigned int>(buffer, base);
        }

        long Convert::ToLong(const char* buffer, int base)
        {
            return ToNumeralFromString<long>(buffer, base);
        }

        unsigned long Convert::ToUnsignedLong(const char* buffer, int base)
        {
            return ToNumeralFromString<unsigned long>(buffer, base);
        }

        long long Convert::ToLongLong(const char* buffer, int base)
        {
            return ToNumeralFromString<long long>(buffer, base);
        }

        unsigned long long Convert::ToUnsignedLongLong(const char* buffer, int base)
        {
            return ToNumeralFromString<unsigned long long>(buffer, base);
        }

        bool Convert::ToBool(const char* buffer)
        {
            if (*buffer != 't' && *buffer != 'T')
                return false;

            buffer++;
            if (*buffer != 'r' && *buffer != 'R')
                return false;

            buffer++;
            if (*buffer != 'u' && *buffer != 'U')
                return false;

            buffer++;
            if (*buffer != 'e' && *buffer != 'E')
                return false;
            
            return true;
        }

        template<typename T>
        void Convert::ToStringFromNumeral(char* buffer, int base, T value, bool isCapital)
        {
            // Only if the base is 10 (decimal) and the value is indeed less then zero should we
            // output a negative sign. If T is an unsigned integer, then this if statement will
            // always evaluates to false thereby not outputting a negative sign.
            if (base == 10 && value < 0)
            {
                // We want to work with positives numbers from here on out.
                value = -value;
                *buffer++ = '-';
            }

            // Convert the value to the largest integer supported (64-bit integer) and kill the
            // sign extension if any.
            uint64_t unsignedValue = (uint64_t)value;
            unsignedValue = (unsignedValue << (64 - sizeof(T) * 8)) >> (64 - sizeof(T) * 8);

            // We don't care about properly printing negative hex values.
            if (base != 10 && unsignedValue < 0)
                unsignedValue = -unsignedValue;

            // We need to preserve the original buffer pointer.
            char* bufferPointer = buffer;

            do
            {
                char remainder = (char)(unsignedValue % base);
                *bufferPointer++ = remainder < 10 ? '0' + remainder : (isCapital ? 'A' : 'a') + remainder - 10;
            } while (unsignedValue /= base);

            *bufferPointer-- = 0;
            while (buffer < bufferPointer)
            {
                char tmp = *buffer;
                *buffer = *bufferPointer;
                *bufferPointer = tmp;

                buffer++;
                bufferPointer--;
            }
        }

        template<typename T>
        T Convert::ToNumeralFromString(const char* buffer, int base)
        {
            T result = 0;
            bool isNegative = false;

            if (*buffer == '+')
            {
                buffer++;
            }
            else if (*buffer == '-')
            {
                buffer++;
                isNegative = true;
            }

            while ((*buffer >= '0' && *buffer <= '9') || (*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z'))
            {
                result = result * base;

                if (*buffer >= '0' && *buffer <= '9')
                    result += *buffer++ - '0';
                else if (*buffer >= 'a' && *buffer <= 'z')
                    result += *buffer++ - 'a' + 10;
                else if (*buffer >= 'A' && *buffer <= 'Z')
                    result += *buffer++ - 'A' + 10;
            }

            if (isNegative)
                result = -result;

            return result;
        }
    }
}