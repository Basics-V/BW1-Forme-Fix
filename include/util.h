#pragma once

// Macros
#define STRING(x) #x
#define STR(x) STRING(x)

#define DEBUG
#define MELONDS

// Debug utils
#ifdef __cplusplus
    namespace Mi4 {
        #ifdef DEBUG
            void Printf(const char* format, ...);
        #else
            static inline void Printf(...) {}
        #endif
    }
#else
    #ifdef DEBUG
        void Mi4_Printf(const char* format, ...);
    #else
        static inline void Mi4_Printf(...) {}
    #endif
#endif // __cplusplus
