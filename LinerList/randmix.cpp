/*
 * @Author: karin
 * @Date: 2020-01-02 20:51:17
 * @LastEditors  : karin
 * @LastEditTime : 2020-01-02 21:47:47
 * @Description: 随机置换
 * @TimeComplexity: O(nlogn)
 * @FilePath: \datastructure\randmix.cpp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define len 10

void randmix1(int a[], int b[]) {
  // b[] - 存储置换结果；len - 数组长度
  int used[len];                  //记录被使用过的数
  memset(used, 0, sizeof(used));  //注意使用前清零

  for (int i = 0; i < len; i++) {
    int temp = rand() % len;  //随机抽一个数
    while (used[temp]) {
      temp = rand() % len;
    }
    b[i] = a[temp];//放入 b 数组中
    used[temp] = 1;
  }
}
int main() {
  int a[len] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int b[len];
  randmix1(a, b);
  for (int i = 0; i < len; i++) {
    printf("%d ", b[i]);
  }
  return 0;
}