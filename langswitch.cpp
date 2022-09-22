#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout
            << "langswitch.exe [-l] layout\n"
            << "options:\n"
            << "layout      layout to activate e.g. en-US\n"
            << "-l          list available layouts\n";
        return 1;
    }

    HKL list[256]{ 0 };

    GetKeyboardLayoutList(256, list);

    HKL* lst = list;

    char countrybuf[32];
    char locbuf[32];

    while (*lst != 0) {

        GetLocaleInfoA(MAKELCID(((UINT)*lst & 0xffffffff),
            SORT_DEFAULT), LOCALE_SISO639LANGNAME, locbuf, 32);
        GetLocaleInfoA(MAKELCID(((UINT)*lst & 0xffffffff),
            SORT_DEFAULT), LOCALE_SISO3166CTRYNAME, countrybuf, 32);

        std::ostringstream oss;
        oss << locbuf << '-' << countrybuf;
        auto str = oss.str();

        if (argv[1] == std::string("-l")) {
            std::cout << str << std::endl;
        }

        else if (str == argv[1]) {
            std::ostringstream lkid_oss;
            lkid_oss << std::setw(8) << std::setfill('0') << std::hex << ((UINT)*lst & 0xffff);
            HKL hkl = LoadKeyboardLayoutA(lkid_oss.str().c_str(), KLF_ACTIVATE);

            if (!hkl) {
                return 2;
            }

            HWND wind = GetForegroundWindow();
            if (!wind || !IsWindowVisible(wind)) {
                wind = GetDesktopWindow();
            }

            PostMessage(wind, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hkl);
            return 0;
        }

        lst++;
    }

    return 0;
}

