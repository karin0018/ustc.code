/*
 * @Author: karin018
 * @Date: 2019-09-14 18:16:19
 * @Last Modified by:   karin018
 * @Last Modified time: 2019-09-14 18:16:19
 */

/*
ʵ��ʵ�� x(-1024<x<1024)�ļӼ������㣬Ҫ�����㾫�ȣ���С�ֱ��ʣ�
�ﵽ 2^(-n) n ��һ�����������Ԥ�������
Ҫ��
- ��ʮ���ƻ�����ƴ�(���Ա�) ��ʾʵ�� x
- ���� ADT ���ж���ʮ����ʵ���Ĺ��ܣ�ʵ�ֵ� N ���Ƶ�ת�� (N��ֵ��������ʱָ��)
ʵ�ּӼ��ˣ�������������
- ʵ��һ�����Ӳ���������ʽ��ֵ�����纯�� F(x) = 3/7*x^3-1/3*x^2+4 �ĵ�ֵ
����(x=1.4)������Ҫ��Ϊ n = 200.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

//�궨��ջ
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
unsigned int_stacksize;  //Ԥ�����С
int *int_stacktop_ptr;   //ջ��ָ��
int *int_stackbase_ptr;  //����ָ��
/**�����ú궨����ʵ�� 8 ��ջ�Ļ�������
 * ## ��ʾ��ǰ������������������
 * gcc -E hstack.cpp
 * ֻ��Ԥ���룬����궨��չ����Ľ�������ڴ��Լ��궨���Ƿ��������
 */
//��ʼ��ջ
#define initStack(stack)                                                    \
  stack##_stackbase_ptr = (stack *)malloc(sizeof(stack) * STACK_INIT_SIZE); \
  if (stack##_stackbase_ptr) {                                              \
    stack##_stacktop_ptr = stack##_stackbase_ptr;                           \
    stack##_stacksize = STACK_INIT_SIZE;                                    \
  } else                                                                    \
    exit(0)  //����ռ�ʧ�� �˳�����

//�ж��Ƿ�Ϊ��ջ
#define stackEmpty(stack) \
  stack##_stackbase_ptr == stack##_stacktop_ptr ? 1 : 0  // yes 1;no 0
//���ջ������
#define getTop(stack, e)                        \
  stack##_stackbase_ptr == stack##_stacktop_ptr \
      ? 1                                       \
      : (e = *(stack##_stacktop_ptr - 1), 1)
// ���ջ
#define ClearStack(stack) stack##_stacktop_ptr = stack##_stackbase_ptr
//����ջ
#define destroyStack(stack) free(stak##_stackbase_ptr)
//����ջ�ĳ���
#define stackLength(stack) stack##_stacktop_ptr - stack##_stackbase_ptr
//��ջ
#define pop(stack, e)                           \
  stack##_stackbase_ptr == stack##_stacktop_ptr \
      ? 1                                       \
      : (e = *(--stack##_stacktop_ptr), 0)
//ѹջ
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
void output(Number result);  // output data ���������--��֤����Ҫ��
Number reverse(Number newNumber);  //����������С�����ַ���õĽṹ��
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
  //�õ� newNumber ��С������
  for (int i = 0; i < NumFloat; i++) {
    sub2.FloatNum[i] = newNumber.FloatNum[i];
  }
  // 1-С�� �õ���С������
  sub = Calculate.NumberMinus(sub, sub2);
  //ԭ��������--
  newNumber.IntNum--;
  for (int i = 0; i < NumFloat; i++) {
    newNumber.FloatNum[i] = sub.FloatNum[i];
  }

  return newNumber;
}

//��ʼ����ʹ�õĽṹ��
Number initiNum(Number newNum) {
  newNum.IntNum = 0;
  memset(newNum.FloatNum, 0, sizeof(newNum.FloatNum));
  return newNum;
}

/*��ȡʮ������*/
Number input() {  //��������
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
      numInt[i] = sizeLine[i];  //�����������ַ������� numInt
    }
    newNumber.IntNum = atoi(numInt);
    int j = 0;
    for (i = i + 1; i < len; i++) {
      newNumber.FloatNum[j] = sizeLine[i] - '0';
      j++;
    }
  } else {  //���������û��С���㣬��ֱ��ת��������
    newNumber.IntNum = atoi(sizeLine);
    memset(newNumber.FloatNum, 0, sizeof(newNumber.FloatNum));
  }

  //���������Ǹ�С�������С������ת��
  if (sizeLine[0] == '-') {
    newNumber = reverse(newNumber);
  }
  return newNumber;
}

/*ʮλ�������*/
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

/*ʵ���ӷ�*/
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

/*ʵ������*/
Number ADT::NumberMinus(Number an, Number bn) {
  Number cn;
  cn = initiNum(cn);
  int pre = 0;  //�����λ
  int i = 0;
  int diff = 0;  //�����ֵ
  for (i = NumFloat - 1; i >= 0; i--) {
    diff = an.FloatNum[i] - bn.FloatNum[i] + pre;

    // diff=diff-10*pre;  ʵ�ָ���ȡģ
    if (diff < 0) {
      pre = -1;
      diff += 10;  //��λ+10
    } else {
      pre = 0;
    }

    cn.FloatNum[i] = diff;
  }
  cn.IntNum = an.IntNum - bn.IntNum + pre;
  return cn;
}

/*ʵ������ʵ���ĳ˷�*/
Number ADT::NumberMultiply(Number an, Number bn) {
  //����������
  int numInt = an.IntNum * bn.IntNum;

  //������С�� an.IntNum * bn.FloatNum
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

  //������С�� bn.IntNum * an.FloatNum
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
  //ʵ��С�����ֵĳ˷�
  Number dn;
  dn = initiNum(dn);
  dn = Float2(an, bn);

  dn.IntNum += numInt;
  //�ܺ�
  Number newNumber;
  newNumber = initiNum(newNumber);
  newNumber = Calculate.NumberPlus(cn, dn);
  return newNumber;
}

/*ʵ������С����λ�ĳ˷�*/
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

  //����ʹ�ø߾��ȳ˷��ó�����С�����ֵĳ˻�
  for (i = 0; i < NumFloat; i++) {
    for (j = 0; j < NumFloat; j++) {
      fltc[i + j] += flta[i] * fltb[j];
      fltc[i + j + 1] += fltc[i + j] / 10;  // ��λ
      fltc[i + j] = fltc[i + j] % 10;       //ģ 10 ȡ��
    }
  }

  //��תС������
  int lenC = 0;
  for (i = NumFloat - 1; i >= 0 && fltc[i] == 0; i--, lenC++)
    ;
  lenC = NumFloat - lenC;
  for (i = 0, j = lenC - 1; i < lenC; i++, j--) {
    newNumber.FloatNum[i] = fltc[j];
  }

  return newNumber;
}

/*ʮ���Ƶ��������֮���ת��*/
void ADT::NumberSysConvert(Number an, int n) {
  initStack(int);  //��ʼ��ջ
  //����Ǹ�������ת����һ��ʵ�����ʽ
  int flag = 0;
  if (an.IntNum < 0) {
    Number sub;
    sub = initiNum(sub);
    sub.IntNum = (an.IntNum) * 2 + 2;
    memset(sub.FloatNum, 0, sizeof(sub.FloatNum));
    an = Calculate.NumberMinus(sub, an);
    flag = 1;
  }
  //ȡ����������
  int num = an.IntNum;

  if (num == 0) {
    if (flag == 1) {
      printf("-0.");
    } else {
      printf("0.");
    }
  } else {
    //�ж�����
    if (flag == 1) {
      num = num * (-1);
    }
    //ȡ��ѹջ
    while (num != 0) {
      push(int, num % n);
      num = num / n;
    }
    int e = 0;
    if (flag) {
      printf("-");
    }
    //��ջ���������
    int len = stackLength(int);
    while (len > 0) {
      pop(int, e);
      printf("%d", e);
      len--;
    }
    printf(".");
  }
  //�õ� an ��С������
  Number sum;
  sum = initiNum(sum);
  for (int i = 0; i < NumFloat; i++) {
    sum.FloatNum[i] = an.FloatNum[i];
  }
  int i = NumFloat;
  Number system;
  system = initiNum(system);
  system.IntNum = n;  //���ƻ���

  for (; i >= 0; i--) {
    sum = Calculate.NumberMultiply(sum, system);
    printf("%d", sum.IntNum);
    sum.IntNum = 0;
  }
}

/*ģ����ʽ���������������ĳ���*/
Number ADT::NumberDivision(int a, int b) {
  Number newNumber;
  newNumber = initiNum(newNumber);
  //ֱ�����ȡ���õ�����λ
  newNumber.IntNum = a / b;
  //��λ��10 ȡ���õ�С��λ
  int i = 0;
  a = a % b;
  for (; i < NumFloat; i++) {
    newNumber.FloatNum[i] = a * 10 / b;
    a = a * 10 % b;
  }
  return newNumber;
}

