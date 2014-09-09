#include <inttypes.h>

void vstrncpy(char *dst, const char* src, int count)
{
	for(int i = 0; i < count && (*dst++ = *src++) != '\200'; i++);
}