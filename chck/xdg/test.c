#include "xdg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef NDEBUG
#include <assert.h>

int
main(void)
{
   // OUTPUT: current variables
   {
      char *ret;
      printf("%s\n", (ret = xdg_get_path("XDG_CONFIG_HOME", ".config"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_DATA_HOME", ".local/share"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_CACHE_HOME", ".cache"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_DESKTOP_DIR", "Desktop"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_DOWNLOAD_DIR", "Downloads"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_TEMPLATES_DIR", "Templates"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_PUBLICSHARE_DIR", "Public"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_DOCUMENTS_DIR", "Documents"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_MUSIC_DIR", "Music"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_PICTURES_DIR", "Pictures"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_VIDEOS_DIR", "Videos"))); free(ret);
      printf("%s\n", (ret = xdg_get_path("XDG_THIS_DOES_NOT_EXIST", "but_mah_path_is_still_here"))); free(ret);

      const char *path;
      struct xdg_paths state;
      memset(&state, 0, sizeof(state));
      while ((path = xdg_get_paths("XDG_DATA_DIRS", "/usr/share:/foo/bar:asd:/the/relative/got/skipped:asd", &state, -1)))
         printf("=> %s\n", path);
   }

   // TEST: good set
   {
      const char *home = "/home/dir/.configs" ;
      setenv("XDG_CONFIG_HOME", home, 1);
      char *ret = xdg_get_path("XDG_CONFIG_HOME", "default_is_not_used");
      assert(!strcmp(ret, home));
      free(ret);
   }

   // TEST: default value
   {
      unsetenv("XDG_CONFIG_HOME");
      char *ret = xdg_get_path("XDG_CONFIG_HOME", "default_path");
      assert(strstr(ret, "default_path"));
      free(ret);
   }

   // TEST: non relative
   {
      const char *home = "\\o// $24$@£ DID I SET MY CONFIG_HOME RIGHT!?" ;
      setenv("XDG_CONFIG_HOME", home, 1);
      char *ret = xdg_get_path("XDG_CONFIG_HOME", "that_does_not_get_set");
      assert(strcmp(ret, home));
      free(ret);
   }

   // TEST: good paths
   {
      int i = 0;
      const char *paths[3] = { "/test", "/test2", "/relative/skipped" };
      setenv("XDG_DATA_DIRS", "/test:/test2:relative:/relative/skipped:/ignored/by/max/iter/arg", 1);

      const char *path;
      struct xdg_paths state;
      memset(&state, 0, sizeof(state));
      while ((path = xdg_get_paths("XDG_DATA_DIRS", "/does:/not:/trigger", &state, 3))) {
         assert(i < 3 && !strcmp(path, paths[i]));
         ++i;
      }
   }

   // TEST: default paths
   {
      int i = 0;
      const char *paths[1] = { "/default" };
      unsetenv("XDG_DATA_DIRS");

      const char *path;
      struct xdg_paths state;
      memset(&state, 0, sizeof(state));
      while ((path = xdg_get_paths("XDG_DATA_DIRS", "/default:relative:skip/path", &state, 1))) {
         assert(i < 1 && !strcmp(path, paths[i]));
         ++i;
      }
   }

   return EXIT_SUCCESS;
}
