#include <stdio.h>

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point a;
  Point b;
} Rect;

Point getPoint() {
  Point f;
  printf("x: ");
  scanf("%d", &f.x);
  printf("y: ");
  scanf("%d", &f.y);
  return f;
}

void printPoint(Point f) {
  printf("Coord: (%d, %d)", f.x, f.y);
}
Rect getRect() {
  Rect r;
  printf("Upper left corner \n");
  r.a = getPoint();
  printf("Bottom right corner \n");
  r.b = getPoint();
  return r;
}

void printRect(Rect r) {
  printf("(%d,%d) ", r.a.x, r.a.y);
  printf("(%d,%d) ", r.b.x, r.b.y);
}

Rect turnLeft90 (Rect r, Point t) {
  int dist_x = t.x - r.b.x;
  int dist_y = t.y - r.a.y;
  int len_x = r.b.x - r.a.x;
  int len_y = r.a.y - r.b.y;
  r.b.x = t.x - dist_y;
  r.b.y = t.y + dist_x;
  r.a.x = r.b.x - len_y;
  r.a.y = r.b.y + len_x;
  return r;
}

