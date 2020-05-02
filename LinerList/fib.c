/*
 * @Author: karin
 * @Date: 2020-01-02 19:56:08
 * @LastEditTime : 2020-01-02 20:15:06
 * @LastEditors  : Please set LastEditors
 * @Description: 斐波那契数列循环求法，时间复杂度为 O(n)
 * @FilePath: \datastructure\LinerList\fib.c
 */

#include <stdio.h>

int fib(int n) {
  if (n <= 1) return 0;
  int fibs[n];
  fibs[0] = 0;
  fibs[1] = 1;
  for(int i = 1;i < n;i++){
      fibs[i+1] = fibs[i] + fibs[i-1];//单层循环
      printf("%d",fibs[i]);
  }
  return fibs[n];
}

int main() {
  printf("输入斐波那契数列序号 - ");
  int num;
  scanf("%d",&num);
  int result;
  result=fib(num);
  printf("\n%d",result);
  return 0;
}