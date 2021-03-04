#include <stdio.h>
int main() {
  int x = 98;  //Non-negative integer
  int k = 27;
  int y = (x|(1<<k)) & ~(1 << k/2);
  printf("%d -> %d \n", x, y);
}
