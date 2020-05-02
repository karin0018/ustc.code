/*
 * @Author: karin
 * @Date: 2020-01-31 12:48:18
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 19:30:18
 * @Description: binary search
 * @TimeComplexity: O(logn)
 * @FilePath: \datastructure\ustc.code\sort\binarySearch1.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//折半查找的 C 实现
int binarySearch(char *a, char key) {
  // a-原数组， key 要查找的关键字
  int lo = 0, hi = strlen(a) - 1;
  while (lo < hi || lo == hi) {
    int mid = (lo + hi) / 2;
    if (key < a[mid])
      hi = mid - 1;
    else if (key > a[mid])
      lo = mid + 1;
    else
      return mid;  //找到，返回 key 在数组中的位置
  }
  return -1;  //没找到
}

int cmp(const void *a, const void *b) {
  return *(char *)a - *(char *)b;  //从小到大排序；
}

int main() {
  char a[10] = "sedfrghjk";
  qsort(a, 9, sizeof(a[0]), cmp);
  printf("%s", a);
  getchar();
  int loc = binarySearch(a, 'e');
  printf("%c , %d", 'e', loc);
  getchar();
}
