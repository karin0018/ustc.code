/*
 * @Author: karin
 * @Date: 2020-02-01 19:47:08
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 19:30:36
 * @Description: Merge sort
 * @TimeComplexity: O(nlogn)
 * @FilePath: \datastructure\ustc.code\sort\mergeSort2.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(char* a, char* aux, int lo, int mid, int hi) {
  // aux--辅助数组
  for (int k = 0; k < hi + 1; k++) {
    aux[k] = a[k];
  }
  int i = lo, j = mid + 1;             // mid 把数组分成两部分
  for (int k = lo; k < hi + 1; k++) {  //追踪新数组位置
    if (i > mid)
      a[k] = aux[j++];
    else if (j > hi)
      a[k] = aux[i++];
    else if (a[i] > a[j])
      a[k] = aux[j++];
    // else if (a[i] < a[j])
    //	a[k] = aux[i++];
    else
      a[k] = aux[i++];
  }
}

void Sort(char* a, char* aux, int lo, int hi) {
  if (hi < lo || hi == lo) return;
  int mid = (lo + hi) / 2;
  Sort(a, aux, lo, mid);
  Sort(a, aux, mid + 1, hi);
  merge(a, aux, lo, mid, hi);
}

int main() {
  char a[10] = "sedfrtgcd";
  char aux[10];
  printf("raw %s", a);
  getchar();
  Sort(a, aux, 0, 8);
  printf("sort1 %s", a);
  getchar();
  return 0;
}
