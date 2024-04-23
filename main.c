//deneme github
// bağlılık kontrolleri 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int a;
  int b;
  int c;
} Point;

Point *rotate(Point *p, int angle) {
  int temp;
  if (angle % 90 != 0) {
    return NULL;
  }
  angle /= 90;
  while (angle--) {
    temp = p->a;
    p->a = p->b;
    p->b = -p->c;
    p->c = temp;
  }
  return p;
}

int main() {
  Point point = {1, 2, 3};
  Point *rotated = rotate(&point, 180);

  if (rotated != NULL) {
    printf("Döndürülmüş nokta: (%d, %d, %d)\n", rotated->a, rotated->b, rotated->c);
  } else {
    printf("Nokta döndürülemedi.\n");
  }

  free(rotated); // Belleği serbest bırakmayı unutmayın!

  return 0;
}
