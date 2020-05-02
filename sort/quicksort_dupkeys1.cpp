/*
 * @Author: karin
 * @Date: 2020-01-31 00:48:01
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 19:43:31
 * @Description: Quicksort with duplicated keys
 * @TimeComplexity: O(nlogn)
 * @FilePath: \datastructure\ustc.code\sort\quicksort_dupkeys1.cpp
 */

#include <stdio.h>
#include <stdlib.h>

void exch(char *a, int i, int j) {
  //exchange two keys
  char temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void sort(char *a, int lo, int hi) {
  //lo --low; hi --high;
  //lt ~ gt --> duplicated keys;
  if (hi < lo || hi == lo) return;
  int lt = lo, gt = hi;
  char key = a[lo];
  int i = lo;
  while (i < gt || i == gt) {
    if (a[i] < key)
      exch(a, lt++, i++);//the left keys must smaller than refer_key
    else if (a[i] > key)
      exch(a, i, gt--);//the right keys must bigger than refer_key
    else
      i++;
  }
  sort(a, lo, lt - 1);
  printf("lt - %d %s", lt, a);
  getchar();
  sort(a, gt + 1, hi);
}

int main() {
  char a[10] = {'s', 's', 's', 'q', 'a', 'a', 'a', 'i', 'p', 'p'};
  printf("%s", a);
  getchar();
  sort(a, 0, 9);
  printf("%s", a);
  getchar();
  return 0;
}
