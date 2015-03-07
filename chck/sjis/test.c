#include "sjis.h"
#include <stdlib.h>
#include <string.h>

#undef NDEBUG
#include <assert.h>

int main(void)
{
   static unsigned char sjis[] = {
      0x82, 0xa8, 0x8c, 0x5a, 0x82, 0xbf, 0x82, 0xe1, 0x82, 0xf1, 0x82, 0xa0,
      0x82, 0xe8, 0x82, 0xaa, 0x82, 0xc6, 0x81, 0x49, 0x81, 0x69, 0x81, 0x8b,
      0x2e, 0x81, 0x8b, 0x81, 0x6a, 0x20, 0x84, 0xb3, 0x84, 0xaa, 0x84, 0xb3
   };

   static char utf8[] = {
      0xe3, 0x81, 0x8a, 0xe5, 0x85, 0x84, 0xe3, 0x81, 0xa1, 0xe3, 0x82, 0x83,
      0xe3, 0x82, 0x93, 0xe3, 0x81, 0x82, 0xe3, 0x82, 0x8a, 0xe3, 0x81, 0x8c,
      0xe3, 0x81, 0xa8, 0xef, 0xbc, 0x81, 0xef, 0xbc, 0x88, 0xc2, 0xb0, 0x2e,
      0xc2, 0xb0, 0xef, 0xbc, 0x89, 0x20, 0xe2, 0x94, 0xbb, 0xe2, 0x94, 0x81,
      0xe2, 0x94, 0xbb
   };

   /* TEST: SJIS to UTF8 */
   {
      char *u8;
      u8 = chck_sjis_to_utf8(sjis, sizeof(sjis), NULL, 1);
      assert(memcmp(utf8, u8, sizeof(utf8)) == 0);
      free(u8);
   }

   /* TEST: UTF8 to SJIS */
   {
      unsigned char *sj;
      sj = chck_utf8_to_sjis(utf8, sizeof(utf8), NULL, 1);
      assert(memcmp(sjis, sj, sizeof(sjis)) == 0);
      free(sj);
   }

   return EXIT_SUCCESS;
}
