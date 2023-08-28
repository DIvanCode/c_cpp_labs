#include "util.h"
#include "io.h"

int max(int x, int y) {
  logDebug('m');
  if (x > y) return x;
  return y;
}
