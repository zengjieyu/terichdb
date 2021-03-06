#ifndef __terark_config_h__
#define __terark_config_h__

#if defined(_MSC_VER)

# pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NONSTDC_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#  if defined(TERARK_CREATE_DLL)
#    pragma warning(disable: 4251)
#    define TERARK_DLL_EXPORT __declspec(dllexport)      // creator of dll
#    if defined(_DEBUG) || !defined(NDEBUG)
#//	   pragma message("creating terark-d.lib")
#    else
#//	   pragma message("creating terark-r.lib")
#    endif
#  elif defined(TERARK_USE_DLL)
#    pragma warning(disable: 4251)
#    define TERARK_DLL_EXPORT __declspec(dllimport)      // user of dll
#    if defined(_DEBUG) || !defined(NDEBUG)
//#	   pragma comment(lib, "terark-d.lib")
#    else
//#	   pragma comment(lib, "terark-r.lib")
#    endif
#  else
#    define TERARK_DLL_EXPORT                            // static lib creator or user
#  endif

#else /* _MSC_VER */

#  define TERARK_DLL_EXPORT

#endif /* _MSC_VER */

#if defined(__GNUC__) && __GNUC__*1000 + __GNUC_MINOR__ >= 7001
#  define no_break_fallthrough __attribute__ ((fallthrough))
#endif

#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)

#  define terark_likely(x)    __builtin_expect(x, 1)
#  define terark_unlikely(x)  __builtin_expect(x, 0)
#  define terark_no_return    __attribute__((noreturn))
#  define terark_warn_unused_result  __attribute__((warn_unused_result))
#  define flatten_inline __attribute__((flatten))

#else

#if defined(_MSC_VER) && _MSC_VER >= 1310
#  define terark_no_return __declspec(noreturn)
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400
#  define terark_no_alias __declspec(noalias)
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1910 // vs2017
#  define no_break_fallthrough [[fallthrough]]
#endif

#  define terark_likely(x)    x
#  define terark_unlikely(x)  x
#  define terark_warn_unused_result
#  define flatten_inline

#endif

#if !defined(terark_no_return)
#  define terark_no_return
#endif

#if !defined(terark_no_alias)
#  define terark_no_alias
#endif

/* The ISO C99 standard specifies that in C++ implementations these
 *    should only be defined if explicitly requested __STDC_CONSTANT_MACROS
 */
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#if defined(__GNUC__) && ( \
	  defined(__LP64__) && (__LP64__ == 1) || \
	  defined(__amd64__) || defined(__amd64) || \
	  defined(__x86_64__) || defined(__x86_64) || \
	  defined(__ia64__) || defined(_IA64) || defined(__IA64__) ) || \
	defined(_MSC_VER) && ( defined(_WIN64) || defined(_M_X64) || defined(_M_IA64) ) || \
	defined(__INTEL_COMPILER) && ( \
	  defined(__ia64) || defined(__itanium__) || \
	  defined(__x86_64) || defined(__x86_64__) ) || \
    defined(__WORD_SIZE) && __WORD_SIZE == 64
  #define TERARK_WORD_BITS 64
  #define TERARK_IF_WORD_BITS_64(Then, Else) Then
#else
  #define TERARK_WORD_BITS 32
  #define TERARK_IF_WORD_BITS_64(Then, Else) Else
#endif

#if defined(_MSC_VER)
  #define TERARK_IF_MSVC(Then, Else) Then
#else
  #define TERARK_IF_MSVC(Then, Else) Else
#endif

#if !defined(no_break_fallthrough)
  #define no_break_fallthrough  /* fall through */
#endif

#endif // __terark_config_h__


