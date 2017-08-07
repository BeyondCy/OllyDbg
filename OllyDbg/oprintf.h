#pragma once

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>

static inline void oprintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    static char dprintf_msg[66000];
    *dprintf_msg = 0;
    vsnprintf_s(dprintf_msg, sizeof(dprintf_msg), format, args);
    auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD w;
    WriteFile(hOut, dprintf_msg, strlen(dprintf_msg), &w, nullptr);
}

static inline void oputs(const char* text)
{
    oprintf("%s\n", text);
}

static inline void oprintf_args(_In_z_ _Printf_format_string_ const char* Format, va_list Args)
{
    char buffer[16384];
    vsnprintf_s(buffer, _TRUNCATE, Format, Args);
    oprintf("%s", buffer);
}