#include "Environment.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace Dream {
  std::string Environment::getHomeDirectory() {
    char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
      homedir = getpwuid(getuid())->pw_dir;
    }

    return std::string(homedir);
  }
}