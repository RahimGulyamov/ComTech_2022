/*#include <stdio.h>
#include "func_4.c"
*/
int main() {
  Rect test_4 = {{3, 1}, {7, -2}};
  Point p_4 = {0, 0};
  test_4 = turnLeft90 (test_4, p_4);
  printRect(test_4);
  return 0;
}
