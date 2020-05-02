/*
 * @Author: karin018
 * @Date: 2019-09-14 18:16:19
 * @Last Modified by:   karin018
 * @Last Modified time: 2019-09-14 18:16:19
 */

/*
实现实数 x(-1024<x<1024)的加减乘运算，要求运算精度（最小分辨率）
达到 2^(-n) n 是一个输入参数或预定义参数
要求：
- 用十进制或二进制串(线性表) 表示实数 x
- 构造 ADT 具有读入十进制实数的功能，实现到 N 进制的转换 (N的值可以输入时指定)
实现加减乘，三个基本操作
- 实现一个复杂操作，多项式求值。例如函数 F(x) = 3/7*x^3-1/3*x^2+4 的的值
输入(x=1.4)，精度要求为 n = 200.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

//宏定义栈
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
unsigned int_stacksize;  //预分配大小
int *int_stacktop_ptr;   //栈顶指针
int *int_stackbase_ptr;  //基底指针
/**下面用宏定义来实现 8 个栈的基本操作
 * ## 表示把前后两个参数连接起来
 * gcc -E hstack.cpp
 * 只做预编译，输出宏定义展开后的结果，用于粗略检查宏定义是否存在问题
 */
//初始化栈
#define initStack(stack)                                                    \
  stack##_stackbase_ptr = (stack *)malloc(sizeof(stack) * STACK_INIT_SIZE); \
  if (stack##_stackbase_ptr) {                                              \
    stack##_stacktop_ptr = stack##_stackbase_ptr;                           \
    stack##_stacksize = STACK_INIT_SIZE;                                    \
  } else                                                                    \
    exit(0)  //分配空间失败 退出程序

//判断是否为空栈
#define stackEmpty(stack) \
  stack##_stackbase_ptr == stack##_stacktop_ptr ? 1 : 0  // yes 1;no 0
//获得栈顶数据
#define getTop(stack, e)                        \
  stack##_stackbase_ptr == stack##_stacktop_ptr \
      ? 1                                       \
      : (e = *(stack##_stacktop_ptr - 1), 1)
// 清空栈
#define ClearStack(stack) stack##_stacktop_ptr = stack##_stackbase_ptr
//销毁栈
#define destroyStack(stack) free(stak##_stackbase_ptr)
//测量栈的长度
#define stackLength(stack) stack##_stacktop_ptr - stack##_stackbase_ptr
//弹栈
#define pop(stack, e)                           \
  stack##_stackbase_ptr == stack##_stacktop_ptr \
      ? 1                                       \
      : (e = *(--stack##_stacktop_ptr), 0)
//压栈
#define push(stack, e)                                                     \
  if (stack##_stacktop_ptr - stack##_stackbase_ptr >= stack##_stacksize) { \
    stack##_stackbase_ptr = (stack *)realloc(                              \
        stack##_stackbase_ptr,                                             \
        (stack##_stacksize + STACKINCREMENT) * sizeof(stack));             \
    if (!stack##_stackbase_ptr) exit(0);                                   \
    stack##_stacktop_ptr = stack##_stackbase_ptr + stack##_stacksize;      \
    stack##_stacksize += STACKINCREMENT;                                   \
  }                                                                        \
  *(stack##_stacktop_ptr) = e;                                             \
  (stack##_stacktop_ptr)++

#define NumFloat 55
struct Number {
  int IntNum;
  int FloatNum[NumFloat];
};

struct ADT {
  Number NumberPlus(Number an, Number bn);
  Number NumberMinus(Number an, Number bn);
  Number NumberMultiply(Number an, Number bn);
  void NumberSysConvert(Number an, int n);
  Number NumberDivision(int a, int b);
} Calculate;

Number input();              // input data
void output(Number result);  // output data 二进制输出--保证精度要求
Number reverse(Number newNumber);  //返回整数与小数部分分离好的结构体
Number Float2(Number an, Number bn);  // return float*float
Number initiNum(Number newNum);

int main() {
  int flag = 1;
  while (flag) {
    Number an, bn, cn, result;
    int p, q, a1, b1;
    printf("\nplease input your option :\n");
    printf(
        "1.plus\n2.minus\n3.multiply\n4.sysconvert\n5.polyval\n6.two number "
        "division\n");
    int op = 0;
    scanf("%d", &op);
    switch (op) {
      case 1:
        printf("please input two number:\n");
        an = input();
        bn = input();
        result = Calculate.NumberPlus(an, bn);
        output(result);
        break;
      case 2:
        printf("please input two number:\n");
        an = input();
        bn = input();

        result = Calculate.NumberMinus(an, bn);
        output(result);
        break;
      case 3:
        printf("please input two number:\n");
        an = input();
        bn = input();

        result = Calculate.NumberMultiply(an, bn);
        output(result);
        break;
      case 4:
        printf("plese input a number that you what to exchange : \n");
        cn = input();
        printf("please input the system that you what to exchange : \n");
        int n;
        scanf("%d", &n);
        Calculate.NumberSysConvert(cn, n);
        break;
      case 5:
        printf("this is a polyval\n");
        printf(" F(x) = 3/7*x^3-1/3*x^2+4  \n");
        printf("please input x = ? ");
        Number num, sum1, sum2, sum3;
        num = input();
        p = 3, q = 7;
        sum1 = Calculate.NumberDivision(p, q);
        sum1 = Calculate.NumberMultiply(sum1, num);
        sum1 = Calculate.NumberMultiply(sum1, num);
        sum1 = Calculate.NumberMultiply(sum1, num);
        p = 1, q = 3;
        sum2 = Calculate.NumberDivision(p, q);
        sum2 = Calculate.NumberMultiply(sum2, num);
        sum2 = Calculate.NumberMultiply(sum2, num);
        result = Calculate.NumberMinus(sum1, sum2);
        sum3 = initiNum(sum3);
        sum3.IntNum = 4;
        result = Calculate.NumberPlus(result, sum3);
        output(result);
        break;
      case 6:
        printf("please input two int number that you want to devision :\n");

        scanf("%d %d", &a1, &b1);
        result = Calculate.NumberDivision(a1, b1);
        output(result);
          getchar();
 		  getchar();
        break;
      default:
        printf("error!!!\n");
    }
  }

  getchar();
  getchar();
  return 0;
}

Number reverse(Number newNumber) {
  Number sub;
  sub.IntNum = 1;
  memset(sub.FloatNum, 0, sizeof(sub.FloatNum));
  Number sub2;
  sub2 = initiNum(sub2);
  //得到 newNumber 的小数部分
  for (int i = 0; i < NumFloat; i++) {
    sub2.FloatNum[i] = newNumber.FloatNum[i];
  }
  // 1-小数 得到正小数部分
  sub = Calculate.NumberMinus(sub, sub2);
  //原整数部分--
  newNumber.IntNum--;
  for (int i = 0; i < NumFloat; i++) {
    newNumber.FloatNum[i] = sub.FloatNum[i];
  }

  return newNumber;
}

//初始化被使用的结构体
Number initiNum(Number newNum) {
  newNum.IntNum = 0;
  memset(newNum.FloatNum, 0, sizeof(newNum.FloatNum));
  return newNum;
}

/*读取十进制数*/
Number input() {  //输入数据
  Number newNumber;
  newNumber = initiNum(newNumber);

  char numInt[10];
  char sizeLine[NumFloat + 10];
  memset(numInt, 0, sizeof(numInt));
  memset(sizeLine, 0, sizeof(sizeLine));
  scanf("%s", sizeLine);
  int len = strlen(sizeLine);
  int i = 0, flag = 0;
  for (i = len - 1; i >= 0; i--) {
    if (sizeLine[i] == '.') {
      flag = 1;
      break;
    }
  }
  if (flag == 1) {
    for (i = 0; sizeLine[i] != '.'; i++) {
      numInt[i] = sizeLine[i];  //将整数部分字符串赋给 numInt
    }
    newNumber.IntNum = atoi(numInt);
    int j = 0;
    for (i = i + 1; i < len; i++) {
      newNumber.FloatNum[j] = sizeLine[i] - '0';
      j++;
    }
  } else {  //输入的数据没有小数点，则直接转成整数型
    newNumber.IntNum = atoi(sizeLine);
    memset(newNumber.FloatNum, 0, sizeof(newNumber.FloatNum));
  }

  //如果输入的是负小数，则把小数部分转正
  if (sizeLine[0] == '-') {
    newNumber = reverse(newNumber);
  }
  return newNumber;
}

/*十位正常输出*/
void output(Number result) {
  if (result.IntNum < 0) {
    Number sub;
    sub.IntNum = (result.IntNum) * 2 + 2;
    memset(sub.FloatNum, 0, sizeof(sub.FloatNum));
    result = Calculate.NumberMinus(sub, result);
  }
  printf("%d", result.IntNum);
  printf(".");
  for (int i = 0; i < NumFloat; i++) {
    printf("%d", result.FloatNum[i]);
  }
}

/*实数加法*/
Number ADT::NumberPlus(Number an, Number bn) {
  Number cn;
  cn = initiNum(cn);
  int next = 0;
  int i = 0;
  int sum = 0;
  for (i = NumFloat - 1; i >= 0; i--) {
    sum = an.FloatNum[i] + bn.FloatNum[i] + next;
    next = sum / 10;
    cn.FloatNum[i] = sum % 10;
  }
  cn.IntNum = an.IntNum + bn.IntNum + next;
  return cn;
}

/*实数减法*/
Number ADT::NumberMinus(Number an, Number bn) {
  Number cn;
  cn = initiNum(cn);
  int pre = 0;  //保存借位
  int i = 0;
  int diff = 0;  //保存差值
  for (i = NumFloat - 1; i >= 0; i--) {
    diff = an.FloatNum[i] - bn.FloatNum[i] + pre;

    // diff=diff-10*pre;  实现负数取模
    if (diff < 0) {
      pre = -1;
      diff += 10;  //借位+10
    } else {
      pre = 0;
    }

    cn.FloatNum[i] = diff;
  }
  cn.IntNum = an.IntNum - bn.IntNum + pre;
  return cn;
}

/*实现两个实数的乘法*/
Number ADT::NumberMultiply(Number an, Number bn) {
  //整数乘整数
  int numInt = an.IntNum * bn.IntNum;

  //整数乘小数 an.IntNum * bn.FloatNum
  int flag = 0;
  if (an.IntNum < 0) {
    flag = 1;
    an.IntNum = an.IntNum * (-1);
  }
  Number cn1;
  cn1 = initiNum(cn1);
  int i = 0;
  int next = 0;
  int pro = 0;
  for (i = NumFloat - 1; i >= 0; i--) {
    pro = bn.FloatNum[i] * an.IntNum + next;
    next = pro / 10;
    cn1.FloatNum[i] = pro % 10;
  }
  if (flag == 1) {
    cn1.IntNum = next * (-1);
    reverse(cn1);
  } else {
    cn1.IntNum = next;
  }

  //整数乘小数 bn.IntNum * an.FloatNum
  flag = 0;
  if (bn.IntNum < 0) {
    flag = 1;
    bn.IntNum = bn.IntNum * (-1);
  }
  next = 0;
  pro = 0;
  Number cn2;
  cn2 = initiNum(cn2);
  for (i = NumFloat - 1; i >= 0; i--) {
    pro = an.FloatNum[i] * bn.IntNum + next;
    next = pro / 10;
    cn2.FloatNum[i] = pro % 10;
  }
  if (flag == 1) {
    cn2.IntNum = next * (-1);
    reverse(cn2);
  } else {
    cn2.IntNum = next;
  }

  Number cn;
  cn = initiNum(cn);
  cn = Calculate.NumberPlus(cn1, cn2);
  //实现小数部分的乘法
  Number dn;
  dn = initiNum(dn);
  dn = Float2(an, bn);

  dn.IntNum += numInt;
  //总和
  Number newNumber;
  newNumber = initiNum(newNumber);
  newNumber = Calculate.NumberPlus(cn, dn);
  return newNumber;
}

/*实现两个小数部位的乘法*/
Number Float2(Number an, Number bn) {
  int flta[NumFloat] = {0};
  int fltb[NumFloat] = {0};
  int fltc[NumFloat] = {0};
  Number newNumber;
  newNumber = initiNum(newNumber);
  int i = 0, j = NumFloat - 1;
  int lenA = 0, lenB = 0;
  for (i = NumFloat - 1; i >= 0 && an.FloatNum[i] == 0; i--, lenA++)
    ;
  lenA = NumFloat - lenA;
  for (i = 0, j = lenA - 1; i < lenA; i++, j--) {
    flta[i] = an.FloatNum[j];
  }
  for (i = NumFloat - 1; i >= 0 && bn.FloatNum[i] == 0; i--, lenB++)
    ;
  lenB = NumFloat - lenB;
  for (i = 0, j = lenB - 1; i < lenB; i++, j--) {
    fltb[i] = bn.FloatNum[j];
  }

  //下面使用高精度乘法得出两个小数部分的乘积
  for (i = 0; i < NumFloat; i++) {
    for (j = 0; j < NumFloat; j++) {
      fltc[i + j] += flta[i] * fltb[j];
      fltc[i + j + 1] += fltc[i + j] / 10;  // 进位
      fltc[i + j] = fltc[i + j] % 10;       //模 10 取余
    }
  }

  //反转小数数组
  int lenC = 0;
  for (i = NumFloat - 1; i >= 0 && fltc[i] == 0; i--, lenC++)
    ;
  lenC = NumFloat - lenC;
  for (i = 0, j = lenC - 1; i < lenC; i++, j--) {
    newNumber.FloatNum[i] = fltc[j];
  }

  return newNumber;
}

/*十进制到任意进制之间的转换*/
void ADT::NumberSysConvert(Number an, int n) {
  initStack(int);  //初始化栈
  //如果是负数，则转换成一般实数表达式
  int flag = 0;
  if (an.IntNum < 0) {
    Number sub;
    sub = initiNum(sub);
    sub.IntNum = (an.IntNum) * 2 + 2;
    memset(sub.FloatNum, 0, sizeof(sub.FloatNum));
    an = Calculate.NumberMinus(sub, an);
    flag = 1;
  }
  //取出整数部分
  int num = an.IntNum;

  if (num == 0) {
    if (flag == 1) {
      printf("-0.");
    } else {
      printf("0.");
    }
  } else {
    //判断正负
    if (flag == 1) {
      num = num * (-1);
    }
    //取余压栈
    while (num != 0) {
      push(int, num % n);
      num = num / n;
    }
    int e = 0;
    if (flag) {
      printf("-");
    }
    //弹栈，倒序输出
    int len = stackLength(int);
    while (len > 0) {
      pop(int, e);
      printf("%d", e);
      len--;
    }
    printf(".");
  }
  //得到 an 的小数部分
  Number sum;
  sum = initiNum(sum);
  for (int i = 0; i < NumFloat; i++) {
    sum.FloatNum[i] = an.FloatNum[i];
  }
  int i = NumFloat;
  Number system;
  system = initiNum(system);
  system.IntNum = n;  //进制基数

  for (; i >= 0; i--) {
    sum = Calculate.NumberMultiply(sum, system);
    printf("%d", sum.IntNum);
    sum.IntNum = 0;
  }
}

/*模拟竖式除法做两个整数的除法*/
Number ADT::NumberDivision(int a, int b) {
  Number newNumber;
  newNumber = initiNum(newNumber);
  //直接相除取整得到整数位
  newNumber.IntNum = a / b;
  //逐位乘10 取整得到小数位
  int i = 0;
  a = a % b;
  for (; i < NumFloat; i++) {
    newNumber.FloatNum[i] = a * 10 / b;
    a = a * 10 % b;
  }
  return newNumber;
}

