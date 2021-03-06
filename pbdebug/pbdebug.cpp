// pbdebug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdint.h>
#include <iostream>

using namespace std;

void write_error(const char *msg)
{
    std::cerr << msg << std::endl;
    std::cerr << "GetLastError: " << GetLastError() << std::endl;
    ExitProcess(-1);
}

int main()
{
    if (!OpenClipboard(nullptr))
    {
        write_error("Unable to open system clipboard!");
    }

    std::cout << "Clipboard formats: " << std::endl;

    uint32_t format = 0;
    while (true)
    {
        format = EnumClipboardFormats(format);

        if (format == 0)
        {
            //no more formats
            break;
        }

        TCHAR name[MAX_PATH];
        if (GetClipboardFormatName(format, name, _countof(name)) == 0)
        {
            _tcscpy_s(name, _T("PREDEFINED"));
        }

        std::wcout << L"* " << format << L": " << name << std::endl;
    }

    if (!CloseClipboard())
    {
        write_error("Could not close system clipboard!");
    }
    return 0;
}

