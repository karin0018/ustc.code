/*
 * @Author: karin
 * @Date: 2020-02-01 01:17:32
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 19:30:26
 * @Description: Insert sort
 * @TimeComplexity: O(n^2)
 * @FilePath: \datastructure\ustc.code\sort\insertSort1.cpp
 */

#include <stdio.h>
#include <string.h>
void exch(char* a, int i, int j) {
  char temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void insertSort(char* a) {
  int len = strlen(a);
  for (int i = 0; i < len; i++) {  //记录扫描位置
    for (int j = i; j > 0; j--) {  //保证左侧升序
      if (a[j - 1] > a[j])
        exch(a, j - 1, j);
      else
        break;  //直到 a[j] 左侧元素比自己小就完成本数据元素的排序；
    }
  }
}

int main() {
  char a[10] = "asxdccfvg";
  printf("raw %s", a);
  getchar();
  insertSort(a);
  printf("sort %s", a);
  getchar();
  return 0;
}
