// util.h
// Authors: MCMi460

// Macros
#define STRING(x) #x
#define STR(x) STRING(x)

// Utils
#ifdef __cplusplus
    namespace Mi4 {
        void Printf(const char* format, ...);
    }
#else
    void Mi4_Printf(const char* format, ...);
#endif // __cplusplus
