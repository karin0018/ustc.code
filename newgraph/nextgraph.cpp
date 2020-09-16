/*
ʵ�ֻ���Fringe���ϵ�ͼ�����㷨��������������������������������Dijistra�㷨
ʵ����ͼ����ͨƬ���������㷨
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <stack>
using namespace std;

// define max number of vertexes and edges
#define MAXV 100
#define MAXE 20000
#define INF 99999

//���廡���
typedef struct ArcNode {
  int id;  //�����
  int h;   //����ͷ�ڵ�
  int t;   // tail
  int w;
  int used;                 //�Ƿ�ʹ��--��С��������ʹ��
  struct ArcNode *nextarc;  //ָ����һ����ָ��
} ArcNode, ArcList[MAXE];   //������

// define vertex's strcut
typedef struct Vnode {
  int id;                //������
  int w;                 //����Ȩֵ
  int degree;            //������ȣ������ڽ�����ĳ���
  int cp;                //��ͨƬ���
  ArcNode *firstarc;     //ָ���һ�������ö���Ļ�
} Vnode, AdjList[MAXV];  //��������

//����ͼ���
typedef struct {
  AdjList vertices;
  ArcList e;  //������
  int nv;     //�������
  int ne;
  int delne;
} Graph;

//���ͼ����
//����һ���� n ������Ĵ�Ȩ����ͼ��ÿ������������κζ������ߵĸ�����
// P�����ɽ������ filename.txt �� ����������� seed
void randgraph(int n, float p, const char *filename, int seed) {
  srand(seed);
  //�����ļ����ݣ��ļ���С������ 5M
  char *content = (char *)malloc(5000000);
  if (!content) {
    printf("the content can not generate!");
    exit(0);
  }
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    printf("the %s can not open!", filename);
    exit(0);
  }
  long offset = 0;  //��ʼд��λ��
  long ne = 0;
  for (int i = 0; i < n; ++i)  //д�붥����Ϣ
    offset += sprintf(content + offset, "%3d %5d\n", i,
                      rand() % 100);  //д����ı���Լ�������Ȩֵ
  int pn = (int)(10000 * p);
  for (int i = 0; i < n; i++) {  //д�����Ϣ
    for (int j = i; j < n; j++) {
      if (i != j && (rand() % 10000 < pn)) {
        offset +=
            sprintf(content + offset, "%3d  %3d  %4d\n", i, j, rand() % 100);
        ne++;
      }
    }
  }

  char ch[10];
  int sz = sprintf(ch, "%3d  %3d\n", n, ne);  //���붥����Ŀ�ͱߵ���Ŀ
  fwrite(&ch, sz, 1, fp);
  fwrite(content, offset, 1, fp);
  fclose(fp);
  free(content);
}

//��ȡͼ�����ڴ�������ͼ�ı�ʾ
void initGraph(Graph *g, const char *gfile) {
  FILE *fp = fopen(gfile, "r");
  if (!fp) {
    printf("can not open the file !\n");
    exit(0);
  }
  char bv[10];
  //��ȡͼ�Ļ�����Ϣ ,ͼ�����ͣ���������������
  fscanf(fp, "%d%d", &(g->nv), &(g->ne), bv);
  //��ȡ������Ϣ��id��w��degree�� û�� edges��������Ϣʱ���ϣ�
  for (int i = 0; i < g->nv; ++i) {
    fscanf(fp, "%d%d", &(g->vertices[i].id), &(g->vertices[i].w));

    g->vertices[i].degree = 0;
    printf("vertex %d - weight %d\n", g->vertices[i].id, g->vertices[i].w);
    g->vertices[i].firstarc = NULL;
  }
  //��ȡ����Ϣ��  g.e[i]: id,h,t,w;
  for (unsigned long i = 0; i < g->ne; i++) {
    fscanf(fp, "%d%d%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
    printf("arc:from %d -> %d => weight %d\n", g->e[i].h, g->e[i].t, g->e[i].w);
    g->e[i].id = i;
    unsigned h, t, w;
    h = g->e[i].h;  //���Ϊi�ıߣ���ͷh����βt
    t = g->e[i].t;
    w = g->e[i].w;
    g->vertices[h].degree++;  //��¼����
    if (g->vertices[h].firstarc == NULL) {
      g->vertices[h].firstarc = &(g->e[i]);
      g->e[i].nextarc = NULL;

    } else {
      //����h������ڽӱ�,Ϊ�����Ч�ʣ����ڱ�ͷ�����㡣
      ArcNode *arc = new ArcNode;
      arc->id = i;
      arc->h = h;
      arc->t = t;
      arc->w = w;
      arc->nextarc = g->vertices[h].firstarc;
      g->vertices[h].firstarc = arc;
      /*debug
              for(arc = g->vertices[h].firstarc;arc!=NULL;arc = arc->nextarc){
                  printf("root %d ,arc head %d,tail %d weight
         %d",h,arc->h,arc->t,arc->w); getchar();
              }
      */
    }
  }
  fclose(fp);
  //��ʼ����ͨƬ
  for (int a = 0; a < g->nv; a++) {
    g->vertices[a].cp = a;
  }
  for (int b = 0; b < g->ne; b++) {
    g->e[b].used = 0;
  }
}

//��ӡ�ڽӱ����Ϣ
void printG(Graph *g) {
  printf("graph info��vexnum(%u)-arcnum(%u)\n", g->nv, (g->ne - g->delne));
  for (int i = 0; i < g->nv; ++i) {
    printf("ID(%u)-degree(%d)-weight(%d) -ArcList (eid|w)��%u ",
           g->vertices[i].id, g->vertices[i].degree, g->vertices[i].w,
           g->vertices[i].id);
    ArcNode *e = g->vertices[i].firstarc;
    for (int j = 0; j < g->vertices[i].degree; ++j) {
      if (e->id != -1) {
        printf("-> %u(%d-%d) ", e->t, e->id,
               e->w);  //�붥��g->v[i]�����ıߵ�β��㡢�ߵı�š��ߵ�Ȩֵ
      }
      e = e->nextarc;
    }
    printf("\n");
  }
}

//�����������ͼ
int BFS(Graph *g, int start, int key) {
  /*
  start -- �ӱ��Ϊ start �Ķ��㿪ʼ����
  key -- ��Ҫ�������Ķ����� key
  */
  printf("BFS --  ");
  int nv = g->nv;  //��¼û�б��ѵ��Ķ�������
//  printf("%d",nv);
//  getchar();
  int visit[nv];
  memset(visit, 0, sizeof(visit));

  queue<int> q;  //�½�����

  while (nv > 0) {
    q.push(start);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();  //��ͷ����
      visit[cur] = 1;
      nv--;
      printf("%d - ", cur);  //��ӡ����·�� path
      if (cur == key) {
        printf("done!\n");
        return 0;
      }
      //���ڽӵ������
      int i = 0;
      ArcNode *p = g->vertices[cur].firstarc;
      while (p != NULL) {
        i = p->t;
        if (!visit[i]) {
          q.push(i);  //û��������е��ڽӵ�Ӷ�β���
          printf(" push (%d) ",i); //debug
          visit[i] = 1;
        }
        p = p->nextarc;
      }
    }
    if (nv > 0 && q.empty()) {
    	printf("random nv- %d\n",nv);//debug
      start = rand() % (g->nv);  //���ѡ�����¿�ʼ
      while(visit[start] == 1){
      	start = rand() % (g->nv);  //���ѡ�����¿�ʼ
	  }
    }
  }
  printf("failure to find !\n");
  return 0;
}

//������������㷨
int DFS(Graph *g, int start, int key) {
  /*
  start -- �ӱ��Ϊ start �Ķ��㿪ʼ����
  key -- ��Ҫ�������Ķ����� key
  */
  printf("DFS --  ");
  int nv = g->nv;
  int visit[nv];
  memset(visit, 0, sizeof(visit));

  stack<int> s;  //�½� ջ
  while (nv > 0) {
    s.push(start);        //�����һ�������� start
    while (!s.empty()) {  //ջ�ǿ�
      int cur = s.top();  //���ջ��Ԫ��
      s.pop();            //ջ��Ԫ�س�ջ
      visit[cur] = 1;
      nv--;
      printf("%d - ", cur);  //��ӡ����·�� path
      if (cur == key) {      //�ҵ����㣬��������
        printf("done!\n");
        return 0;
      }
      //���ڽӵ���ջ
      int i = 0;
      ArcNode *p = g->vertices[cur].firstarc;
      while (p != NULL) {
        i = p->t;
        if (!visit[i]) {
          s.push(i);  //��֮ǰ��ջ���������ڽӵ�ȫ����ջ
          printf(" push (%d) ",i); //debug
          visit[i] = 1;
        }
        p = p->nextarc;
      }
    }
    if (nv > 0 && s.empty()) {
      printf("random\n");//debug
      start = rand() % (g->nv);  //���ѡ�����¿�ʼ
      while(visit[start] == 1){
      	start = rand() % (g->nv);  //���ѡ�����¿�ʼ
	  }
    }
  }
  printf("failure to find !\n");
  return 0;
}

//��³˹���� �㷨����С������,������ͨƬ����
//���Ľṹ��--����ṹ���������ͨƬ��� cp�� �߽ṹ����ӱ�ʹ�ñ�� used
//�ҵ�Ȩֵ��С�ı�,���ر��ڱ������е�λ��
int getMinArc(Graph *g) {
  int min = INF;
  int id;
  for (int i = 0; i < g->ne; i++) {
    if ((g->e[i].id != -1) && (g->e[i].used == 0)) {
      printf("unused - id %d", g->e[i].id);  // debug
      getchar();
      if (min > g->e[i].w) {
        min = g->e[i].w;
        id = g->e[i].id;
        printf("%d", id);  // debug
        getchar();
      }
    }
  }
  return id;
}

void resetUse(Graph *g, int h, int t) {  //ʹ(h,t)֮��ı�ȫ�����õ�
  for (int i = 0; i < (g->ne); i++) {  //������h���Ϊͷ��tΪβ�ıߣ�����used
    if ((g->e[i].id != -1) && (g->e[i].t == t) && (g->e[i].h == h)) {
      printf("used (1) - %d", g->e[i].id);
      getchar();
      g->e[i].used = 1;
      break;
    }
  }
}

void minGenTree(Graph *g) {
  printf("��С��������\n");
  int nv = g->nv;  //��ʾ��ͨƬ����
  int ne = g->ne;  //��ʾʣ��ߵ�����
  int h, t, id, cph, cpt;
  int vt[g->nv];
  for (int a = 0; a < g->nv; a++) {
    vt[a] = 0;
  }

  while (nv > 1 && ne > 0) {
    id = getMinArc(g);  //Ȩֵ��С�ı��ڱ������е�λ��
    g->e[id].used = 1;  //���ı������used��Ϣ
    ne--;
    h = g->e[id].h;  //ͷ������
    t = g->e[id].t;  //β������
    cph = g->vertices[h].cp;
    cpt = g->vertices[t].cp;
    printf("cph %d cpt %d\n", cph, cpt);
    if (cph != cpt) {
      nv--;
      g->vertices[h].cp = g->vertices[t].cp = cpt;

      if ((vt[h] == 1) && (vt[t] == 1)) {
        printf("�޸���ͨƬ���\n");
        getchar();
        for (int i = 0; i < (g->ne);
             i++) {  //������h���Ϊͷ�ıߣ����Ķ��������ͨƬ���
          if ((g->e[i].id != -1) && (g->e[i].used == 1) && (g->e[i].h == h)) {
            printf("used==%d - h %d - h' %d", g->e[i].used, h, g->e[i].h);
            g->vertices[g->e[i].t].cp = cpt;
            resetUse(g, g->e[i].t, h);  //��(h,t)֮�䲻�ٻ��б�
          }
        }
        printf("��������");
        getchar();
        for (int i = 0; i < (g->ne);
             i++) {  //������h���Ϊβ�ıߣ����Ķ��������ͨƬ���

          if ((g->e[i].id != -1) && (g->e[i].used == 1) && (g->e[i].t == h)) {
            printf("used==%d -%d - h %d", g->e[i].used, g->e[i].t, h);
            g->vertices[g->e[i].h].cp = cpt;
            resetUse(g, g->e[i].h, t);  //��(h,t)֮�䲻�ٻ��б�
          }
        }
      }
      vt[h] = 1;
      vt[t] = 1;

      printf("��ͨƬ����--%d eid %d (head %d -> tail %d) weight %d\n", nv,
             g->e[id].id, h, t, g->e[id].w);
    }
  }
}


//�õ�ĳ�� (h,t) ��Ȩ�ز�����
int getArcweight(Graph *g, int h, int t) {
  for (int i = 0; i < g->ne; i++) {
    if ((h == g->e[i].h) && t == g->e[i].t) {
//    	printf("weight %d", g->e[i].w);
//    	getchar();
      return g->e[i].w;
    }
  }
//   printf("the arc is not founded!");
  return INF;  //����������֮��û�бߴ���ʱ����Ϊ���������������
}


//��³˹�����㷨�����·��
int dijkstra(Graph *g, int start) {
  int nv = g->nv;
  int visit[nv];
  int dist[nv];  //��ŵ���ʼ��ľ���
  memset(visit, 0, sizeof(visit));
//  printf("begin!");
//  getchar();
  for (int i = 0; i < nv; i++) {  //��ʼ�� dist ����
    if (i == start) {
      dist[i] = 0;
    } else {
      dist[i] = getArcweight(g, start, i);
//      printf("%d -> %d = %d",start,i,dist[i]);//debug
//      getchar();
    }
  }
  printf("��ʼ����ϣ�");
  getchar();
  
  visit[start] = 1;

  int min, cur_min;               //��¼�ߵ���СȨֵ�͵�ǰ����
  for (int i = 0; i < nv; i++) {  //�������ж���
    min = INF;
    for (int j = 0; j < nv; j++) {
      if (!visit[j] && min > dist[j]) {
        min = dist[j];
        cur_min = j;
      }
    }
    visit[cur_min] = 1;
//    printf("cur_min = %d , dist = %d \n",cur_min,dist[cur_min]);//debug
//    getchar(); 
    
    for (int k = 0; k < nv; k++) {
      if (dist[k] > dist[cur_min] + getArcweight(g, cur_min, k)) {
        dist[k] = dist[cur_min] + getArcweight(g, cur_min, k);
      }
    }
  }

  //��ӡ start ���������ж�������·��ֵ
	printf("���·��:\n"); 
  for(int i = 0;i<nv;i++){
      if(i != start){
          printf("%d -> %d = %d \n",start,i,dist[i]);
      }
  }
}


int main() {
  int seed = 121;
  randgraph(5, 0.5, "draw.txt",
            seed);  //�������ͼ���涨��������������߸��ʣ�
  Graph *g = (Graph *)malloc(sizeof(Graph));
  printf("size of g = %ld\n", sizeof(Graph));
  initGraph(g, "draw.txt");
  printG(g);
  int w, h, t, id;

//  minGenTree(g);
//  printG(g);
//  getchar();
  
  printf("��������Ҫ�����Ķ����ţ�\n");
  int key;
  scanf("%d",&key);
  printf("����������������\n");
  DFS(g,0,key);
  getchar();
  printf("����������������\n");
  BFS(g,0,key);
  getchar();
  
  printf("��³˹�����㷨�����·����\n");
  printf("��������ʼ�㣺\n");
  int start;
  scanf("%d",&start);//��Ҫ����ȡ��ַ 
  dijkstra(g, start);
  getchar(); 
  
  
  return 0;
}

