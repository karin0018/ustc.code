/*
 * @Author: karin
 * @Date: 2020-01-05 15:48:04
 * @LastEditors  : karin
 * @LastEditTime : 2020-01-05 16:58:37
 * @Description: KMP 算法实现子串匹配（模式匹配）
 * @TimeComplexity: O(n)
 * @FilePath: \datastructure\string\kmp.cpp
 */
// KMP实现代码
//模式串 1 开始是有效位，t[0]不是有效位
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *ch;    //按长度分配， 否则为NULL
  int length;  //串的长度
} StringType;

#define Max_Strlen 1024
int next[Max_Strlen];//next[j]数组

int KMP_index(StringType s, StringType t) {
  //用KMP算法进行模式匹配， 匹配返回位置， 否则返回-1
  //用堆分配存储方式保存字符串， s和t分别表示主串和模式串
  int i = 0, j = 1;  //初始匹配位置设置
  while ((i < s.length) && (j < t.length)) {
    if ((j == 0) || (s.ch[i] == t.ch[j])) {
      i++;
      j++;
    } else
      j = next[j];
  }
  if (j >= t.length) {//匹配成功
    printf("\nsuccessfully ! \n pos - %d", i - t.length + 1);
    return (i - t.length + 1);
  }
  printf("false!");
  return (-1);  //匹配失败
}

// next[j] 优化版本，已经略去了next[j]中重复比较的部分
void next2(StringType t) {
  //求模式t的next串t函数值并保存在next数组中
  int k = 1, j = 0;
  next[1] = 0;
  printf("next[j]:");
  while (k < t.length) {
    printf("%d - ", next[k]);
    if ((j == 0) || (t.ch[k] == t.ch[j])) {
      k++;
      j++;
      if (t.ch[k] != t.ch[j])
        next[k] = j;
      else  //若下一个 tj 与当前的 tj 相同，则不用重复与 si比较；这里用二者的
            // next[j] 相同实现；
        next[k] = next[j];
    } else
      j = next[j];
  }
}

int main() {
  StringType S;
  StringType T;
  int len = 10;
  S.ch = (char *)malloc(len * sizeof(char));
  if (!S.ch) {
    printf("room fail!");
  }
  T.ch = (char *)malloc(len * sizeof(char));
  if (!T.ch) {
    printf("room fail!");
  }
  //这里为了简化代码，直接给ch指针赋值地址
  char s[20] = {"acabaabaabcacaabc"};
  char t[20] = {"#abaabcac"};//模式串首位是无效位
  S.ch = s;
  printf("%s\n", S.ch);
  S.length = 17;
  T.ch = t;
  T.length = 9;
  next2(T); //先算next[j]数组
  KMP_index(S, T);//给出子串首次出现的位置
  return 0;
}
