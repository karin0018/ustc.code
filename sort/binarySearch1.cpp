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

//�۰���ҵ� C ʵ��
int binarySearch(char *a, char key) {
  // a-ԭ���飬 key Ҫ���ҵĹؼ���
  int lo = 0, hi = strlen(a) - 1;
  while (lo < hi || lo == hi) {
    int mid = (lo + hi) / 2;
    if (key < a[mid])
      hi = mid - 1;
    else if (key > a[mid])
      lo = mid + 1;
    else
      return mid;  //�ҵ������� key �������е�λ��
  }
  return -1;  //û�ҵ�
}

int cmp(const void *a, const void *b) {
  return *(char *)a - *(char *)b;  //��С��������
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
