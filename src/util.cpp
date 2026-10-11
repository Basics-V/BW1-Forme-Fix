#include "util.h"

#ifdef DEBUG
    #ifdef MELONDS
        #define DEBUG_PREFIX "~ "
        // stdbuf -oL ./melonDS | sed -unE "/abort/p; s/^~ //p"
    #endif

    #include <cstdarg>
    #include <cstdio>

    namespace Mi4 {
        /*
            Reimplementation of k::Printf in Hello007/NitroKernel
        */
        void Printf_Core(const char* str) {
            #if defined DESMUME
                // https://wiki.desmume.org/index.php?title=Faq
                asm volatile ("MOVS R0, %0" : : "r" (str));
                asm volatile ("SWI #0xFC");
            #elif defined MELONDS
                // https://problemkaputt.de/gbatek-ds-debug-registers-emulator-devkits.htm
                volatile char* nocashCharOut = (volatile char*)0x4FFFA1C;
                while (*str) {
                    *nocashCharOut = *str;
                    #ifdef DEBUG_PREFIX
                        if (*str == '\n' && *(str + 1)) {
                            Printf_Core(DEBUG_PREFIX);
                        }
                    #endif
                    str++;
                }
            #endif
        }

        // HelloOO7/NitroKernel/src/kPrint.cpp
        void Printf(const char* format, ...) {
            #ifdef DEBUG_PREFIX
                Printf_Core(DEBUG_PREFIX);
            #endif
            va_list args;
            va_start(args, format);
            char outBuffer[256];
            vsnprintf(outBuffer, 256, format, args);
            Printf_Core(outBuffer);
            va_end(args);
        }
    }

    extern "C" void Mi4_Printf(const char* format, ...) {
        Mi4::Printf(format);
    }
#endif
