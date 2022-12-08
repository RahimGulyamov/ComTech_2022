/*#include <stdio.h>
#include "func_4.c"
*/
int main() {
  Rect test_1 = {{-3, -4}, {-1, -8}};
  Point p_1 = {0, 0};
  test_1 = turnLeft90 (test_1, p_1);
  printRect(test_1);
  return 0;
}
