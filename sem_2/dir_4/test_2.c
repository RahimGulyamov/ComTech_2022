/*#include <stdio.h>
#include "func_4.c"
*/
int main() {
  Rect test_2 = {{6, 2}, {9, -1}};
  Point p_2 = {2, 2};
  test_2 = turnLeft90 (test_2, p_2);
  printRect(test_2);
  return 0;
}
