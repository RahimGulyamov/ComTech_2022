/*#include <stdio.h>
#include "func_4.c"
*/
int main() {
  Rect test_5 = {{2, 10}, {5, 9}};
  Point p_5 = {8, 10};
  test_5 = turnLeft90 (test_5, p_5);
  printRect(test_5);
  return 0;
}
