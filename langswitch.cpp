#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#define LOW(n)  (n & 0x0000FFFF)
#define HIGH(n) ((n & 0xFFFF0000) >> 16)

struct Layout {
    static const size_t SHORT_NAME_LEN = 32;
    static const size_t FULL_NAME_LEN = 60;

    char short_name[SHORT_NAME_LEN];
    char full_name[FULL_NAME_LEN];
    uint32_t id_lkid;
    uint32_t id_hkl;

    const char* get_name(bool always_full = false) const {
        if (!always_full && strnlen(short_name, SHORT_NAME_LEN)) {
            return short_name;
        }
        else return full_name;
    }
};


// short name can be specified in 1st column
// sources: 
// https://learn.microsoft.com/en-us/windows-hardware/manufacture/desktop/windows-language-pack-default-values?view=windows-10 for id_lkid
// registry: HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Keyboard Layouts   for id_hkl
const Layout layouts[] = {
    { "",        "Albanian",                                              0x0000041c, 0x041c041c },
    { "",        "Arabic (101)",                                          0x00000401, 0x04010401 },
    { "",        "Arabic (102)",                                          0x00010401, 0xf0280401 },
    { "",        "Arabic (102) AZERTY",                                   0x00020401, 0xf0290401 },
    { "",        "Armenian Eastern",                                      0x0000042b, 0x042b042b },
    { "",        "Armenian Phonetic",                                     0x0002042b, 0xf038042b },
    { "",        "Armenian Typewriter",                                   0x0003042b, 0xf039042b },
    { "",        "Armenian Western",                                      0x0001042b, 0xf025042b },
    { "",        "Assamese - Inscript",                                   0x0000044d, 0x044d044d },
    { "",        "Azerbaijani (Standard)",                                0x0001042c, 0xf0bd042c },
    { "",        "Azerbaijani Cyrillic",                                  0x0000082c, 0x082c082c },
    { "",        "Azerbaijani Latin",                                     0x0000042c, 0x042c042c },
    { "",        "Bashkir",                                               0x0000046d, 0x046d046d },
    { "",        "Belarusian",                                            0x00000423, 0x04230423 },
    { "",        "Belgian (Comma)",                                       0x0001080c, 0xf01e080c },
    { "",        "Belgian (Period)",                                      0x00000813, 0x08130813 },
    { "",        "Belgian French",                                        0x0000080c, 0x080c080c },
    { "",        "Bangla (Bangladesh)",                                   0x00000445, 0x04450445 },
    { "",        "Bangla (India)",                                        0x00020445, 0x04450445 },
    { "",        "Bangla (India - Legacy)",                               0x00010445, 0x04450445 },
    { "",        "Bosnian (Cyrillic)",                                    0x0000201a, 0x201a201a },
    { "",        "Buginese",                                              0x000b0c00, 0xf0b30c00 },
    { "",        "Bulgarian",                                             0x0030402 , 0xf0aa0402 },
    { "",        "Bulgarian (Latin)",                                     0x00010402, 0xf0040402 },
    { "",        "Bulgarian (phonetic layout)",                           0x00020402, 0x04020402 },
    { "",        "Bulgarian (phonetic traditional)",                      0x00040402, 0xf0af0402 },
    { "",        "Bulgarian (Typewriter)",                                0x00000402, 0x04020402 },
    { "",        "Canadian French",                                       0x00001009, 0x10091009 },
    { "",        "Canadian French (Legacy)",                              0x00000c0c, 0x0c0c0c0c },
    { "",        "Canadian Multilingual Standard",                        0x00011009, 0xf0201009 },
    { "",        "Central Atlas Tamazight",                               0x0000085f, 0x085f085f },
    { "",        "Central Kurdish",                                       0x00000429, 0x04290429 },
    { "",        "Cherokee Nation",                                       0x0000045c, 0x045c045c },
    { "",        "Cherokee Nation Phonetic",                              0x0001045c, 0xf037045c },
    { "",        "Chinese (Simplified) - US Keyboard",                    0x00000804, 0x08040804 },
    { "",        "Chinese (Traditional) - US Keyboard",                   0x00000404, 0x04040404 },
    { "",        "Chinese (Traditional, Hong Kong S.A.R.)",               0x00000c04, 0x0c040c04 },
    { "",        "Chinese (Traditional Macao S.A.R.) US Keyboard",        0x00001404, 0x14041404 },
    { "",        "Chinese (Simplified, Singapore) - US keyboard",         0x00001004, 0x10041004 },
    { "",        "Croatian",                                              0x0000041a, 0x041a041a },
    { "",        "Czech",                                                 0x00000405, 0x04050405 },
    { "",        "Czech (QWERTY)",                                        0x00010405, 0xf0050405 },
    { "",        "Czech Programmers",                                     0x00020405, 0xf00a0405 },
    { "",        "Danish",                                                0x00000406, 0x04060406 },
    { "",        "Devanagari-INSCRIPT",                                   0x00000439, 0x04390439 },
    { "",        "Divehi Phonetic",                                       0x00000465, 0x04650465 },
    { "",        "Divehi Typewriter",                                     0x00010465, 0xf00d0465 },
    { "",        "Dutch",                                                 0x00000413, 0x04130413 },
    { "",        "Dzongkha",                                              0x00000C51, 0x0c510c51 },
    { "",        "Estonian",                                              0x00000425, 0x04250425 },
    { "",        "Faeroese",                                              0x00000438, 0x04380438 },
    { "",        "Finnish",                                               0x0000040b, 0x040b040b },
    { "",        "Finnish with Sami",                                     0x0001083b, 0xf02d083b },
    { "",        "French",                                                0x0000040c, 0x040c040c },
    { "",        "Futhark",                                               0x00120c00, 0xf0bb0c00 },
    { "",        "Georgian",                                              0x00000437, 0x04370437 },
    { "",        "Georgian (Ergonomic)",                                  0x00020437, 0xf0ac0437 },
    { "",        "Georgian (QWERTY)",                                     0x00010437, 0xf0ab0437 },
    { "",        "Georgian Ministry of Education and Science Schools",    0x00030437, 0xf03b0437 },
    { "",        "Georgian (Old Alphabets)",                              0x00040437, 0xf03c0437 },
    { "",        "German",                                                0x00000407, 0x04070407 },
    { "",        "German (IBM)",                                          0x00010407, 0xf0120407 },
    { "",        "Gothic",                                                0x000c0c00, 0xf0b40c00 },
    { "",        "Greek",                                                 0x00000408, 0x04080408 },
    { "",        "Greek (220)",                                           0x00010408, 0xf0160408 },
    { "",        "Greek (220) Latin",                                     0x00030408, 0xf0170408 },
    { "",        "Greek (319)",                                           0x00020408, 0xf0180408 },
    { "",        "Greek (319) Latin",                                     0x00040408, 0xf0110408 },
    { "",        "Greek Latin",                                           0x00050408, 0xf0190408 },
    { "",        "Greek Polytonic",                                       0x00060408, 0xf01f0408 },
    { "",        "Greenlandic",                                           0x0000046f, 0x046f046f },
    { "",        "Guarani",                                               0x00000474, 0x04740474 },
    { "",        "Gujarati",                                              0x00000447, 0x04470447 },
    { "",        "Hausa",                                                 0x00000468, 0x04680468 },
    { "",        "Hebrew",                                                0x0000040d, 0x040d040d },
    { "",        "Hindi Traditional",                                     0x00010439, 0xf00c0439 },
    { "",        "Hungarian",                                             0x0000040e, 0x040e040e },
    { "",        "Hungarian 101-key",                                     0x0001040e, 0xf006040e },
    { "",        "Icelandic",                                             0x0000040f, 0x040f040f },
    { "",        "Igbo",                                                  0x00000470, 0x04700470 },
    { "",        "India",                                                 0x00004009, 0x40094009 },
    { "",        "Inuktitut - Latin",                                     0x0000085d, 0x085d085d },
    { "",        "Inuktitut - Naqittaut",                                 0x0001045d, 0xf0a7045d },
    { "",        "Irish",                                                 0x00001809, 0x18091809 },
    { "",        "Italian",                                               0x00000410, 0x04100410 },
    { "",        "Italian (142)",                                         0x00010410, 0xf0030410 },
    { "ja-JP",   "Japanese",                                              0x00000411, 0x04110411 },
    { "",        "Javanese",                                              0x00110c00, 0xf0ba0c00 },
    { "",        "Kannada",                                               0x0000044b, 0x044b044b },
    { "",        "Kazakh",                                                0x0000043f, 0x043f043f },
    { "",        "Khmer",                                                 0x00000453, 0x04530453 },
    { "",        "Khmer (NIDA)",                                          0x00010453, 0xf02f0453 },
    { "",        "Korean",                                                0x00000412, 0x04120412 },
    { "",        "Kyrgyz Cyrillic",                                       0x00000440, 0x04400440 },
    { "",        "Lao",                                                   0x00000454, 0x04540454 },
    { "",        "Latin American",                                        0x0000080a, 0x080a080a },
    { "",        "Latvian (Standard)",                                    0x00020426, 0xf0b10426 },
    { "",        "Latvian (Legacy)",                                      0x00010426, 0x04260426 },
    { "",        "Lisu (Basic)",                                          0x00070c00, 0xf03e0c00 },
    { "",        "Lisu (Standard)",                                       0x00080c00, 0xf03f0c00 },
    { "",        "Lithuanian",                                            0x00010427, 0xf0270427 },
    { "",        "Lithuanian IBM",                                        0x00000427, 0x04270427 },
    { "",        "Lithuanian Standard",                                   0x00020427, 0xf0a10427 },
    { "",        "Luxembourgish",                                         0x0000046e, 0x046e046e },
    { "",        "Macedonia (FYROM)",                                     0x0000042f, 0x042f042f },
    { "",        "Macedonia (FYROM) - Standard",                          0x0001042f, 0x042f042f },
    { "",        "Malayalam",                                             0x0000044c, 0x044c044c },
    { "",        "Maltese 47-Key",                                        0x0000043a, 0x043a043a },
    { "",        "Maltese 48-key",                                        0x0001043a, 0xf02b043a },
    { "",        "Maori",                                                 0x00000481, 0x04810481 },
    { "",        "Marathi",                                               0x0000044e, 0x044e044e },
    { "",        "Mongolian (Mongolian Script - Legacy)",                 0x00000850, 0x08500850 },
    { "",        "Mongolian (Mongolian Script - Standard)",               0x00020850, 0x08500850 },
    { "",        "Mongolian Cyrillic",                                    0x00000450, 0x04500450 },
    { "",        "Myanmar",                                               0x00010c00, 0x0c000c00 },
    { "",        "N'ko",                                                  0x00090c00, 0x0c000c00 },
    { "",        "Nepali",                                                0x00000461, 0x04610461 },
    { "",        "New Tai Lue",                                           0x00020c00, 0xf0310c00 },
    { "",        "Norwegian",                                             0x00000414, 0x04140414 },
    { "",        "Norwegian with Sami",                                   0x0000043b, 0x043b043b },
    { "",        "Odia",                                                  0x00000448, 0x04480448 },
    { "",        "Ol Chiki",                                              0x000d0c00, 0xf0b60c00 },
    { "",        "Old Italic",                                            0x000f0c00, 0xf0b80c00 },
    { "",        "Osmanya",                                               0x000e0c00, 0xf0b70c00 },
    { "",        "Pashto (Afghanistan)",                                  0x00000463, 0x04630463 },
    { "",        "Persian",                                               0x00000429, 0x04290429 },
    { "",        "Persian (Standard)",                                    0x00050429, 0xf03a0429 },
    { "",        "Phags-pa",                                              0x000a0c00, 0xf0410c00 },
    { "",        "Polish (214)",                                          0x00010415, 0xf0070415 },
    { "",        "Polish (Programmers)",                                  0x00000415, 0x04150415 },
    { "",        "Portuguese",                                            0x00000816, 0x08160816 },
    { "",        "Portuguese (Brazilian ABNT)",                           0x00000416, 0x04160416 },
    { "",        "Portuguese (Brazilian ABNT2)",                          0x00010416, 0xf0100416 },
    { "",        "Punjabi",                                               0x00000446, 0x04460446 },
    { "",        "Romanian (Legacy)",                                     0x00000418, 0x04180418 },
    { "",        "Romanian (Programmers)",                                0x00020418, 0xf0a60418 },
    { "",        "Romanian (Standard)",                                   0x00010418, 0xf0a50418 },
    { "ru-RU",   "Russian",                                               0x00000419, 0x04190419 },
    { "",        "Russian - Mnemonic",                                    0x00020419, 0xf0330419 },
    { "",        "Russian (Typewriter)",                                  0x00010419, 0xf0080419 },
    { "ru-IBTL", "Russian (Ilya Birman's typographic layout)",            0xa0000419, 0xf0c00419 },
    { "",        "Sakha",                                                 0x00000485, 0x04850485 },
    { "",        "Sami Extended Finland-Sweden",                          0x0002083b, 0xf02e083b },
    { "",        "Sami Extended Norway",                                  0x0001043b, 0xf02c043b },
    { "",        "Scottish Gaelic",                                       0x00011809, 0x18091809 },
    { "",        "Serbian (Cyrillic)",                                    0x00000c1a, 0x0c1a0c1a },
    { "",        "Serbian (Latin)",                                       0x0000081a, 0x081a081a },
    { "",        "Sesotho sa Leboa",                                      0x0000046c, 0x046c046c },
    { "",        "Setswana",                                              0x00000432, 0x04320432 },
    { "",        "Sinhala",                                               0x0000045b, 0x045b045b },
    { "",        "Sinhala - wij 9",                                       0x0001045b, 0xf0a0045b },
    { "",        "Slovak",                                                0x0000041b, 0x041b041b },
    { "",        "Slovak (QWERTY)",                                       0x0001041b, 0xf013041b },
    { "",        "Slovenian",                                             0x00000424, 0x04240424 },
    { "",        "Sora",                                                  0x00100c00, 0xf0b90c00 },
    { "",        "Sorbian Extended",                                      0x0001042e, 0xf09f042e },
    { "",        "Sorbian Standard",                                      0x0002042e, 0xf0ae042e },
    { "",        "Sorbian Standard (Legacy)",                             0x0000042e, 0x042e042e },
    { "",        "Spanish",                                               0x0000040a, 0x040a040a },
    { "",        "Spanish Variation",                                     0x0001040a, 0xf086040a },
    { "",        "Swedish",                                               0x0000041d, 0x041d041d },
    { "",        "Swedish with Sami",                                     0x0000083b, 0x083b083b },
    { "",        "Swiss French",                                          0x0000100c, 0x100c100c },
    { "",        "Swiss German",                                          0x00000807, 0x08070807 },
    { "",        "Syriac",                                                0x0000045a, 0x045a045a },
    { "",        "Syriac Phonetic",                                       0x0001045a, 0xf00e045a },
    { "",        "Tai Le",                                                0x00030c00, 0xf0340c00 },
    { "",        "Tajik",                                                 0x00000428, 0x04280428 },
    { "",        "Tamil",                                                 0x00000449, 0x04490449 },
    { "",        "Tatar",                                                 0x00010444, 0xf0bc0444 },
    { "",        "Tatar (Legacy)",                                        0x00000444, 0x04440444 },
    { "",        "Telugu",                                                0x0000044a, 0x044a044a },
    { "",        "Thai Kedmanee",                                         0x0000041e, 0x041e041e },
    { "",        "Thai Kedmanee (non-ShiftLock)",                         0x0002041e, 0xf022041e },
    { "",        "Thai Pattachote",                                       0x0001041e, 0xf021041e },
    { "",        "Thai Pattachote (non-ShiftLock)",                       0x0003041e, 0xf023041e },
    { "",        "Tibetan (PRC - Standard)",                              0x00010451, 0x04510451 },
    { "",        "Tibetan (PRC - Legacy)",                                0x00000451, 0x04510451 },
    { "",        "Tifinagh (Basic)",                                      0x00050c00, 0x0c000c00 },
    { "",        "Tifinagh (Full)",                                       0x00060c00, 0xf0360c00 },
    { "",        "Turkish F",                                             0x0001041f, 0xf014041f },
    { "",        "Turkish Q",                                             0x0000041f, 0x041f041f },
    { "",        "Turkmen",                                               0x00000442, 0x04420442 },
    { "",        "Uyghur",                                                0x00010408, 0xf0ad0408 },
    { "",        "Uyghur (Legacy)",                                       0x00000480, 0x04800480 },
    { "uk-UA",   "Ukrainian",                                             0x00000422, 0x04220422 },
    { "uke-UA",  "Ukrainian (Enhanced)",                                  0x00020422, 0xf0a80422 },
    { "",        "United Kingdom",                                        0x00000809, 0x08090809 },
    { "",        "United Kingdom Extended",                               0x00000452, 0x04520452 },
    { "",        "United States - Dvorak",                                0x00010409, 0xf0020409 },
    { "",        "United States - International",                         0x00020409, 0xf0010409 },
    { "",        "United States-Dvorak for left hand",                    0x00030409, 0xf01a0409 },
    { "",        "United States-Dvorak for right hand",                   0x00040409, 0xf01b0409 },
    { "en-US",   "United States - English",                               0x00000409, 0x04090409 },
    { "",        "Urdu",                                                  0x00000420, 0x04200420 },
    { "",        "Uyghur",                                                0x00010480, 0xf0ad0480 },
    { "",        "Uzbek Cyrillic",                                        0x00000843, 0x08430843 },
    { "",        "Vietnamese",                                            0x0000042a, 0x042a042a },
    { "",        "Wolof",                                                 0x00000488, 0x04880488 },
    { "",        "Yakut",                                                 0x00000485, 0x04850485 },
    { "",        "Yoruba",                                                0x0000046a, 0x046a046a },
};



const char* layout_from_table(uint32_t id, bool full_name = false) {
    uint32_t low = LOW(id);

    //find full 
    for (const auto& layout : layouts) {
        if (id == layout.id_hkl) {
            return layout.get_name(full_name);
        }
    }

    //fallback, find general
    for (const auto& layout : layouts) {
        if (HIGH(layout.id_lkid) == 0 && LOW(layout.id_lkid) == low) {
            return layout.get_name(full_name);
        }
    }

    return nullptr;
}


char* layout_from_winapi(uint32_t id) {
    char locbuf[32];
    char countrybuf[32];

    static char retbuf[64];

    GetLocaleInfoA(MAKELCID(id, SORT_DEFAULT), LOCALE_SISO639LANGNAME, locbuf, 32);
    GetLocaleInfoA(MAKELCID(id, SORT_DEFAULT), LOCALE_SISO3166CTRYNAME, countrybuf, 32);

    sprintf_s(retbuf, 64, "%s-%s", locbuf, countrybuf);
    
    return retbuf;
}


uint32_t lkid_from_table(const char* layout_name) {
    for (const auto& layout : layouts) {
        if (strncmp(layout_name, layout.short_name, Layout::SHORT_NAME_LEN) == 0
            || strncmp(layout_name, layout.full_name, Layout::FULL_NAME_LEN) == 0) {
            return layout.id_lkid;
        }
    }
    return 0;
}


int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout
            << "langswitch.exe [-l] layout\n"
            << "options:\n"
            << "layout      layout to activate e.g. en-US or \"United States - English\"\n"
            << "-l          list available layouts, format: name_winapi short_name_table full_name_table\n";
        return 1;
    }

    HKL list[256]{ 0 };

    GetKeyboardLayoutList(256, list);

    HKL* lst = list;

    while (*lst != 0) {
        const char* lay_api = layout_from_winapi((uint32_t)*lst);
        const char* lay_tab_short = layout_from_table((uint32_t)*lst);
        const char* lay_tab_full = layout_from_table((uint32_t)*lst, true);

        if (!lay_tab_full) {
            std::cout << lay_api << " skipped, not found in table\n";
            lst++;
            continue;
        }

        if (strncmp(argv[1], "-l", 3) == 0) {
            std::cout << lay_api << " " << lay_tab_short << " " << lay_tab_full << std::endl;
        }

        else if (strncmp(argv[1], lay_tab_short, Layout::FULL_NAME_LEN) == 0 
              || strncmp(argv[1], lay_tab_full, Layout::FULL_NAME_LEN) == 0) {

            std::ostringstream lkid_oss;
            lkid_oss << std::setw(8) << std::setfill('0') << std::hex << lkid_from_table(lay_tab_full);
            HKL hkl = LoadKeyboardLayoutA(lkid_oss.str().c_str(), KLF_ACTIVATE);

            if (!hkl) {
                return 2;
            }

            HWND wind = GetForegroundWindow();

            PostMessage(wind, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hkl);
            return 0;
        }

        lst++;
    }

    return 0;
}

