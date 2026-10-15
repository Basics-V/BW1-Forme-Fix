// Sourced from ds-pokemon-hacking/swan/swantypes.h

#ifdef __cplusplus

#include <cstdbool>
#include <cstddef>
#include <cstdint>

#else

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#endif

#define NELEMS(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifdef __cplusplus
#define STRUCT_DECLARE(tag) struct tag;
#define UNION_DECLARE(tag) union tag;
#define ENUM_DECLARE(tag) enum tag : u32;
#define ENUM_DECLARE_EX(tag, type) enum tag : type;
#else
#define STRUCT_DECLARE(tag) typedef struct tag tag;
#define UNION_DECLARE(tag) typedef union tag tag;
#define ENUM_DECLARE(tag) typedef enum tag tag;
#define ENUM_DECLARE_EX(tag, type) enum tag : type; typedef enum tag tag;
#endif

typedef uint64_t u64;

typedef int64_t s64;

typedef uint32_t u32;

typedef int32_t s32;

typedef uint16_t u16;

typedef int16_t s16;

typedef uint8_t u8;

typedef int8_t s8;

typedef int32_t b32; //32-bit bool

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

#define wchar_t short

#ifdef __GNUC__
#define WB_PACKED __attribute__((__packed__))
#endif

#ifdef _MSC_VER //unsupported on MSVC
#define WB_PACKED 
#endif

#if defined(_MSC_VER)
#define INLINE inline __forceinline
#elif defined(__GNUC__)
#define INLINE inline __attribute__((always_inline))
#endif

#ifdef __cplusplus
#define C_DECL_BEGIN extern "C" {
#define C_DECL_END } //extern "C"
#define WB_CPPTYPE(ns, typename) namespace ns { typedef typename typename; }
#define WB_CPPTYPE_EX(ns, cppTypename, typename) namespace ns { typedef typename cppTypename; }
#define WB_CPPONLY(code) code
#define WB_NAMESPACE(ns, localname) namespace ns { struct localname; }
#else
#define C_DECL_BEGIN
#define C_DECL_END
#define WB_CPPTYPE(ns, typename)
#define WB_CPPTYPE_EX(ns, cppTypename, typename)
#define WB_CPPONLY(code)
#define WB_NAMESPACE(ns, localname)
#endif
