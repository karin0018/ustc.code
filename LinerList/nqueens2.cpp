// n-�ʺ��������������㷨���ҵ��⼴��
//��һά���������ÿһ�лʺ���кţ�����solution[3]=4��ʾ�����е����з�����һ���ʺ�

#include <stdio.h>
#include <stdlib.h>

//���öѷ���洢�ķ�ʽʵ��
unsigned *neighbors;  //����ھӵ����飬����Ϊ0,1,2,...,size-1
unsigned *solution;  //ÿ��һ���ʺ�solution[i]=row,��ʾ��j�еĻʺ���row��
int len;             //�ʺ�����
unsigned size;  //ÿ�������ھ����̵����� size=(len-1)*len/2��¼�����������

//��������
void restart();
//void chkSolution();

/***  ��ʼ��һ�����̲���,���ھ�����׼����  ***/
void initSolution() {
  size = (len - 1) * len / 2;
  solution = (unsigned *)malloc(sizeof(unsigned) * len);
  neighbors = (unsigned *)malloc(sizeof(unsigned) * size);
  if (!solution || !neighbors) exit(0);  //����ռ�ʧ��

  for (int i = 0; i < len; ++i)  //�������ʼ���ֻ����ĳ����ʼ����
    solution[i] = i;
  for (int i = 0; i < size; ++i)  //�ھ������ʼ��
    neighbors[i] = i;
  printf("initialize had done !\n");
}

/***  �������̵�Ŀ�꺯�������̵ļ�ֵ: value=���໥�������Ļʺ������
 ***  ���ʺ��໥��������ʱ��Ŀ�꺯����ֵvalue==0
 ***   solution[i]==solution[j],
 *(solution[i]-solution[j])/(i-j)==1��-1ʱ�������ʺ�˴��ܹ�������value++
 ***  ���̱��뷽ʽ�ܱ�֤������� solution[i]==solution[j]���ʸ��������Բ����ж�
 ***  �ú�����ʱ�������Ƿ�����ߣ�����ʾ������ǰһ�����value�������ھӵ�value,
 *len*len => 2*len��
 ***/
int evaluate() {
  int value = 0;
  // todo
  for (int i = 0; i < len; i++) {
    for (int j = i+1 ; j < len; j++) {
      if (((solution[i] - solution[j])/(i-j)) == -1 ||((solution[i] - solution[j])/(i-j))== 1) {
        value++;
      }
    }
  }
 //printf("evaluate have done %d\n",value);
  return value;
}

/***  ����û� randShuffle()
 *���޷Żصľ�����������������������ڲ�����С��ֱ��Ϊ0���㷨ֹͣ��
 ***  ������ neighbors ��������û�����
 ***  �õ������ݣ�size= neighbors�ĳ���
 *** best found �����ò��Ÿú���
 ***/
/*void randShuffle() {  //ÿ�������ѡ��k��Ԫ�س���,Ȼ���������顰��ǰĩβ��
  // todo
}*/

/***
 *�������Ǿ��󣨲����Խ��ߣ��洢��һά�����У����±�k�;����±�i,j֮��Ĺ�ϵ����
 ***  ����k������i��j
 *** �����ھ�ʱ�������ھӵı��k���ҵ����Ӧ��Ҫ������i��j��
 ***  K �� i j
 *֮���ת����ʽ�����������Ǿ������ۼƼ���ÿһ�еĸ�����Ȼ��������� j -
 *��ǰԪ��ǰ���Ԫ��
 ***/
void fromKtoIJ(int k, int *i, int *j) {
  // todo
  int a, b;
  for (a = 0; k >= 0;) {
    if (k == 0) {  //����ĳ�ʼ k ���� 0 �����
      a++;
      b = 0;
      break;
    }
    a++;
    k = k - a;
    if (k >= a + 1)  //�������һ�����ݴ���
      continue;
    else if (k < a + 1) {  //������һ������δ����
      b = k;
      a++;
      break;
    }
  }
  *i = a;  // a,b��ֵ�ֱ𸳸� i��j ��ָ���ֵ
  *j = b;
  //printf("from k to ij have done!\n");
}

/***
 *��鵱ǰ�⣨���̣����ھ����̣�����solution[i]��solution[j],i��j���ѡ�񣬹���n(n-1)/2�ֲ�ͬ�Ŀ��ܣ�
 ***  ������ͻ��С�����̣�������Ϊ�µĽ⣨best found���ԣ�,
 *���ع����½�ʱ�����������ھӱ��current
 ***  ������-1,��ʾû���ҵ����õ��ھӣ���Ҫ���� restart()
 *,����0��ʾ�ҵ�����Ľ⣬
 ***/
int traverseNeighbors() {
  int y_current = evaluate();  //��ǰ���̵�Ŀ�꺯��ֵ
  int y, current = -1;  // y���ھӵ�Ŀ�꺯��ֵ��current��ѡ������õ��ھӱ��
  int i, j, row1, row2;

  //�����ھӣ�����ÿ���ھӳ�ͻ�ʺ�Եĸ���y
  /*
  Q��Ϊʲô����ֱ������û���
  A��ֱ������û����ܴﵽ�����ھӵ�Ч��
  */
  for (int k = 0; k < size; ++k) {
    //����뵱ǰsolution��������ͬ���е��ھӵĲ�ͬ�еı��
    fromKtoIJ(neighbors[k], &i, &j);
    //���������ж�Ӧ��ֵ���ʺ����ڵ��кţ�


    row1 = solution[i];
    row2 = solution[j];
    // ������solution[col1] <--> solution[col2]
    int ex;
    solution[i] = row2;
    solution[j] = row1;
    //�����ͻ��y
    y = evaluate();
    //�������õĽ⣨�ھӣ�����Ϣ����ͻ�����ھӱ��
    if (y < y_current) {
      y_current = y;
      current = k;
    }
    //��ɽ���������ھӶ������Ϻ�current��¼����õ��ھ�(best_found����)

    // solution[col1] <--> solution[col2] �ظ���ԭ����׼��������һ���ھ�
    solution[i] = row1;
    solution[j] = row2;
  }

  if (current ==
      -1) {  //������������е��ھӽڵ㣬Ҳ�Ҳ������õ��ƶ���ʽ����ô����Ҫ���������㷨����ʼ��ָı�һ��
    printf("failing find solution��let's restart...\n");
    return -1;
  }
  fromKtoIJ(neighbors[current], &i,
            &j);  //�������ھ��뵱ǰsolution��ͬ�������б��
  //�����ŵ��ھӳ�Ϊ��ǰ��
  row1 = solution[i];
  solution[i] = solution[j];
  solution[j] = row1;
  return y_current;
}

/***  �������������ھӣ�Ҳû���ҵ�y==0�����̲��֣�
 ***  ��ô�������solution��Ȼ��������ɽ������
 ***  ����������ھ��������ڵġ�΢С�����Ŷ��������Ŷ���Χ�������������times=20��
 ***/
void restart() {
  int times = 20;  //���������Ĵ������Ŷ���С,����times>1����
  for (int i = 0; i < times; ++i) {
    int k = rand() % len;
    int j = rand() % len;
    int row = solution[k];
    solution[k] = solution[j];
    solution[j] = row;
  }
  puts("restart() have done ��");
}

int main() {
  int c1, c2;  //����ѡ�����׼����������
  long seed =
      560;  //��������ӣ������������ı䣬��ôÿ���㷨���еĽ������һ���ģ���ʹ��rand()����
  srand(seed);  //��һ��ע�͵�������ÿ�ε���������Ӷ���һ��������ע�ͱ���ÿ��������Ӷ�һ������������ͬ���ڵ���

  printf("pleaes input the qeen number :");
  scanf("%d", &len);  //���̶������̵Ĵ�С

  initSolution();

  int flag;
  while ((flag = traverseNeighbors()) != 0) {
    if (flag < 0) restart();
  }

  printf("the solution is :\n");
  for (int i = 0; i < len; ++i){
       printf("%d, ", solution[i]);
  }
  getchar();//���ܻس�
  getchar();
  free(neighbors);//free �� malloc �Ŀռ�
  free(solution);
}
