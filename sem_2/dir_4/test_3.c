/*#include <stdio.h>
#include "func_4.c"
*/
int main() {
  Rect test_3 = {{-3, 7}, {2, 4}};
  Point p_3 = {-5, 0};
  test_3 = turnLeft90 (test_3, p_3);
  printRect(test_3);
  return 0;
}
