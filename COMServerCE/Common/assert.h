/**
 * assert.h
 * Definition of the assert macro that is absent in eVC++.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifdef  __cplusplus
extern "C" {
#endif

#undef assert  /* Remove existing definition. */

#ifdef NDEBUG

#define assert(exp) \
	((void)0)

#else

void __cdecl _assert(void *exp, void *file, unsigned int line);

#define assert(exp) \
	(void)((exp) || (_assert(#exp, __FILE__, __LINE__), 0))

#endif  /* NDEBUG */

#ifdef  __cplusplus
}
#endif

