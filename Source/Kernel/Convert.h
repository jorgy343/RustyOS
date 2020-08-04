#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Utility
    {
        /// Contains static methods for converting to and from strings and other types. This class
        /// cannot be inherited.
        class Convert final
        {
        public:
            /// Converts a @c char value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 5.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, char value, bool isCapital = false);

            /// Converts a @c signed @c char value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 5.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, signed char value, bool isCapital = false);

            /// Converts an @c unsigned @c char value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 4.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, unsigned char value, bool isCapital = false);

            /// Converts a @c short value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 7.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, short value, bool isCapital = false);

            /// Converts an @c unsigned @c short value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 6.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, unsigned short value, bool isCapital = false);

            /// Converts an @c int value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 12.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, int value, bool isCapital = false);

            /// Converts an @c unsigned @c int value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 11.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, unsigned int value, bool isCapital = false);

            /// Converts a @c long value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 12.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, long value, bool isCapital = false);

            /// Converts an @c unsigned @c long value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 11.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, unsigned long value, bool isCapital = false);

            /// Converts a @c long @c long value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 21.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, long long value, bool isCapital = false);

            /// Converts an @c unsigned @c long @c long value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 20.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            static void ToString(char* buffer, int base, unsigned long long value, bool isCapital = false);

            /// Converts a @c bool value to its corresponding string representation and stores the
            /// result in @p buffer.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion. The minimum length of the array should be 6.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the first letter of the conversion should be uppercase or lowercase. The default value is @c false.
            static void ToString(char* buffer, bool value, bool isCapital = false);

            /// Converts a string of characters contained in @p buffer to a @c char value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a @c char representation of the string of characters contained in @p buffer.
            static char ToChar(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to a @c signed @c char value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a @c signed @c char representation of the string of characters contained in @p buffer.
            static signed char ToSignedChar(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to an @c unsigned @c char value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns an @c unsigned @c char representation of the string of characters contained in @p buffer.
            static unsigned char ToUnsignedChar(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to a @c short value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a @c short representation of the string of characters contained in @p buffer.
            static short ToShort(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to an @c unsigned @c short value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns an @c unsigned @c short representation of the string of characters contained in @p buffer.
            static unsigned short ToUnsignedShort(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to a @c int value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a @c int representation of the string of characters contained in @p buffer.
            static int ToInt(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to an @c unsigned @c int value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns an @c unsigned @c int representation of the string of characters contained in @p buffer.
            static unsigned int ToUnsignedInt(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to a @c long value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a @c long representation of the string of characters contained in @p buffer.
            static long ToLong(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to an @c unsigned @c long value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns an @c unsigned @c long representation of the string of characters contained in @p buffer.
            static unsigned long ToUnsignedLong(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to a @c long @c long value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a @c long @c long representation of the string of characters contained in @p buffer.
            static long long ToLongLong(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to an @c unsigned @c long @c long value. If there
            /// are any letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns an @c unsigned @c longn @c long representation of the string of characters contained in @p buffer.
            static unsigned long long ToUnsignedLongLong(const char* buffer, int base);

            /// Converts a string of characters contained in @p buffer to a @c bool  value. It does not matter
            /// if the letters are uppercase, lowercase or a mix of both.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// 
            /// @return Returns a @c bool representation of the string of characters contained in @p buffer.
            static bool ToBool(const char* buffer);

        private:
            /// Converts any numeral type to a string representation.
            /// 
            /// @tparam T The type of the numeral to convert.
            /// 
            /// @param[out] buffer A pointer to an array of characters to hold the result of the conversion.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// @param[in] value The value to convert to a string representation.
            /// @param[in] isCapital An optional parameter that specifies whether the conversion should use uppercase letters or lowercase letters. The default value is @c false.
            template<typename T>
            static void ToStringFromNumeral(char* buffer, int base, T value, bool isCapital = false);

            /// Converts a string of characters contained in @p buffer to a numeral type. If there are any
            /// letters present in @p buffer than those characters can be uppercase or lowercase.
            /// 
            /// @tparam T The type of the numeral that results fromt he conversion.
            /// 
            /// @param[in] buffer A pointer to a string of characters to convert to a value. The string must be null terminated.
            /// @param[in] base The numeric base to use for the conversion. The alphabet will be used to represent numbers greater than nine. The minimum accepted inclusive value is 2 and the maximum accepted inclusive value is 36.
            /// 
            /// @return Returns a numeral representation of the string of characters contained in @p buffer.
            template<typename T>
            static T ToNumeralFromString(const char* buffer, int base);
        };
    }
}