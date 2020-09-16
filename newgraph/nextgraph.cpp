/*
实现基于Fringe集合的图搜索算法，包括广度优先搜索，深度优先搜索和Dijistra算法
实现求图的联通片的数量的算法
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

//定义弧结点
typedef struct ArcNode {
  int id;  //弧编号
  int h;   //弧的头节点
  int t;   // tail
  int w;
  int used;                 //是否被使用--最小生成树中使用
  struct ArcNode *nextarc;  //指向下一条弧指针
} ArcNode, ArcList[MAXE];   //边数组

// define vertex's strcut
typedef struct Vnode {
  int id;                //顶点编号
  int w;                 //顶点权值
  int degree;            //顶点出度，顶点邻接链表的长度
  int cp;                //连通片编号
  ArcNode *firstarc;     //指向第一条依附该顶点的弧
} Vnode, AdjList[MAXV];  //顶点数组

//定义图结点
typedef struct {
  AdjList vertices;
  ArcList e;  //边数组
  int nv;     //顶点个数
  int ne;
  int delne;
} Graph;

//随机图生成
//生成一个含 n 个顶点的带权有向图，每个顶点和其他任何顶点连边的概率是
// P，生成结果存入 filename.txt 中 随机数种子是 seed
void randgraph(int n, float p, const char *filename, int seed) {
  srand(seed);
  //保存文件内容，文件大小不超过 5M
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
  long offset = 0;  //起始写入位置
  long ne = 0;
  for (int i = 0; i < n; ++i)  //写入顶点信息
    offset += sprintf(content + offset, "%3d %5d\n", i,
                      rand() % 100);  //写入结点的编号以及结点随机权值
  int pn = (int)(10000 * p);
  for (int i = 0; i < n; i++) {  //写入边信息
    for (int j = i; j < n; j++) {
      if (i != j && (rand() % 10000 < pn)) {
        offset +=
            sprintf(content + offset, "%3d  %3d  %4d\n", i, j, rand() % 100);
        ne++;
      }
    }
  }

  char ch[10];
  int sz = sprintf(ch, "%3d  %3d\n", n, ne);  //存入顶点数目和边的数目
  fwrite(&ch, sz, 1, fp);
  fwrite(content, offset, 1, fp);
  fclose(fp);
  free(content);
}

//读取图，在内存中生成图的表示
void initGraph(Graph *g, const char *gfile) {
  FILE *fp = fopen(gfile, "r");
  if (!fp) {
    printf("can not open the file !\n");
    exit(0);
  }
  char bv[10];
  //读取图的基本信息 ,图的类型，顶点数，边数等
  fscanf(fp, "%d%d", &(g->nv), &(g->ne), bv);
  //读取顶点信息：id，w，degree； 没有 edges（读边信息时加上）
  for (int i = 0; i < g->nv; ++i) {
    fscanf(fp, "%d%d", &(g->vertices[i].id), &(g->vertices[i].w));

    g->vertices[i].degree = 0;
    printf("vertex %d - weight %d\n", g->vertices[i].id, g->vertices[i].w);
    g->vertices[i].firstarc = NULL;
  }
  //读取边信息：  g.e[i]: id,h,t,w;
  for (unsigned long i = 0; i < g->ne; i++) {
    fscanf(fp, "%d%d%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
    printf("arc:from %d -> %d => weight %d\n", g->e[i].h, g->e[i].t, g->e[i].w);
    g->e[i].id = i;
    unsigned h, t, w;
    h = g->e[i].h;  //编号为i的边，弧头h，弧尾t
    t = g->e[i].t;
    w = g->e[i].w;
    g->vertices[h].degree++;  //记录出度
    if (g->vertices[h].firstarc == NULL) {
      g->vertices[h].firstarc = &(g->e[i]);
      g->e[i].nextarc = NULL;

    } else {
      //插入h顶点的邻接表,为了提高效率，总在表头插入结点。
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
  //初始化连通片
  for (int a = 0; a < g->nv; a++) {
    g->vertices[a].cp = a;
  }
  for (int b = 0; b < g->ne; b++) {
    g->e[b].used = 0;
  }
}

//打印邻接表的信息
void printG(Graph *g) {
  printf("graph info：vexnum(%u)-arcnum(%u)\n", g->nv, (g->ne - g->delne));
  for (int i = 0; i < g->nv; ++i) {
    printf("ID(%u)-degree(%d)-weight(%d) -ArcList (eid|w)：%u ",
           g->vertices[i].id, g->vertices[i].degree, g->vertices[i].w,
           g->vertices[i].id);
    ArcNode *e = g->vertices[i].firstarc;
    for (int j = 0; j < g->vertices[i].degree; ++j) {
      if (e->id != -1) {
        printf("-> %u(%d-%d) ", e->t, e->id,
               e->w);  //与顶点g->v[i]相连的边的尾结点、边的编号、边的权值
      }
      e = e->nextarc;
    }
    printf("\n");
  }
}

//广度优先搜索图
int BFS(Graph *g, int start, int key) {
  /*
  start -- 从编号为 start 的顶点开始搜索
  key -- 想要搜索到的顶点编号 key
  */
  printf("BFS --  ");
  int nv = g->nv;  //记录没有被搜到的顶点数量
//  printf("%d",nv);
//  getchar();
  int visit[nv];
  memset(visit, 0, sizeof(visit));

  queue<int> q;  //新建队列

  while (nv > 0) {
    q.push(start);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();  //队头出列
      visit[cur] = 1;
      nv--;
      printf("%d - ", cur);  //打印访问路径 path
      if (cur == key) {
        printf("done!\n");
        return 0;
      }
      //将邻接点入队列
      int i = 0;
      ArcNode *p = g->vertices[cur].firstarc;
      while (p != NULL) {
        i = p->t;
        if (!visit[i]) {
          q.push(i);  //没有入过队列的邻接点从队尾入队
          printf(" push (%d) ",i); //debug
          visit[i] = 1;
        }
        p = p->nextarc;
      }
    }
    if (nv > 0 && q.empty()) {
    	printf("random nv- %d\n",nv);//debug
      start = rand() % (g->nv);  //随机选点重新开始
      while(visit[start] == 1){
      	start = rand() % (g->nv);  //随机选点重新开始
	  }
    }
  }
  printf("failure to find !\n");
  return 0;
}

//深度优先搜索算法
int DFS(Graph *g, int start, int key) {
  /*
  start -- 从编号为 start 的顶点开始搜索
  key -- 想要搜索到的顶点编号 key
  */
  printf("DFS --  ");
  int nv = g->nv;
  int visit[nv];
  memset(visit, 0, sizeof(visit));

  stack<int> s;  //新建 栈
  while (nv > 0) {
    s.push(start);        //插入第一个顶点编号 start
    while (!s.empty()) {  //栈非空
      int cur = s.top();  //获得栈顶元素
      s.pop();            //栈顶元素出栈
      visit[cur] = 1;
      nv--;
      printf("%d - ", cur);  //打印访问路径 path
      if (cur == key) {      //找到顶点，结束搜索
        printf("done!\n");
        return 0;
      }
      //将邻接点入栈
      int i = 0;
      ArcNode *p = g->vertices[cur].firstarc;
      while (p != NULL) {
        i = p->t;
        if (!visit[i]) {
          s.push(i);  //把之前出栈结点的所有邻接点全部入栈
          printf(" push (%d) ",i); //debug
          visit[i] = 1;
        }
        p = p->nextarc;
      }
    }
    if (nv > 0 && s.empty()) {
      printf("random\n");//debug
      start = rand() % (g->nv);  //随机选点重新开始
      while(visit[start] == 1){
      	start = rand() % (g->nv);  //随机选点重新开始
	  }
    }
  }
  printf("failure to find !\n");
  return 0;
}

//克鲁斯卡尔 算法求最小生成树,并求连通片数量
//更改结构体--顶点结构体中添加连通片编号 cp； 边结构体添加被使用标记 used
//找到权值最小的边,返回边在边数组中的位置
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

void resetUse(Graph *g, int h, int t) {  //使(h,t)之间的边全部被用掉
  for (int i = 0; i < (g->ne); i++) {  //搜索以h结点为头以t为尾的边，更改used
    if ((g->e[i].id != -1) && (g->e[i].t == t) && (g->e[i].h == h)) {
      printf("used (1) - %d", g->e[i].id);
      getchar();
      g->e[i].used = 1;
      break;
    }
  }
}

void minGenTree(Graph *g) {
  printf("最小生成树：\n");
  int nv = g->nv;  //表示连通片个数
  int ne = g->ne;  //表示剩余边的数量
  int h, t, id, cph, cpt;
  int vt[g->nv];
  for (int a = 0; a < g->nv; a++) {
    vt[a] = 0;
  }

  while (nv > 1 && ne > 0) {
    id = getMinArc(g);  //权值最小的边在边数组中的位置
    g->e[id].used = 1;  //更改边数组的used信息
    ne--;
    h = g->e[id].h;  //头顶点编号
    t = g->e[id].t;  //尾顶点编号
    cph = g->vertices[h].cp;
    cpt = g->vertices[t].cp;
    printf("cph %d cpt %d\n", cph, cpt);
    if (cph != cpt) {
      nv--;
      g->vertices[h].cp = g->vertices[t].cp = cpt;

      if ((vt[h] == 1) && (vt[t] == 1)) {
        printf("修改连通片编号\n");
        getchar();
        for (int i = 0; i < (g->ne);
             i++) {  //搜索以h结点为头的边，更改对面结点的连通片编号
          if ((g->e[i].id != -1) && (g->e[i].used == 1) && (g->e[i].h == h)) {
            printf("used==%d - h %d - h' %d", g->e[i].used, h, g->e[i].h);
            g->vertices[g->e[i].t].cp = cpt;
            resetUse(g, g->e[i].t, h);  //让(h,t)之间不再会有边
          }
        }
        printf("继续搜索");
        getchar();
        for (int i = 0; i < (g->ne);
             i++) {  //搜索以h结点为尾的边，更改对面结点的连通片编号

          if ((g->e[i].id != -1) && (g->e[i].used == 1) && (g->e[i].t == h)) {
            printf("used==%d -%d - h %d", g->e[i].used, g->e[i].t, h);
            g->vertices[g->e[i].h].cp = cpt;
            resetUse(g, g->e[i].h, t);  //让(h,t)之间不再会有边
          }
        }
      }
      vt[h] = 1;
      vt[t] = 1;

      printf("连通片个数--%d eid %d (head %d -> tail %d) weight %d\n", nv,
             g->e[id].id, h, t, g->e[id].w);
    }
  }
}


//得到某边 (h,t) 的权重并返回
int getArcweight(Graph *g, int h, int t) {
  for (int i = 0; i < g->ne; i++) {
    if ((h == g->e[i].h) && t == g->e[i].t) {
//    	printf("weight %d", g->e[i].w);
//    	getchar();
      return g->e[i].w;
    }
  }
//   printf("the arc is not founded!");
  return INF;  //当两个顶点之间没有边存在时，视为，两点间距离无穷大
}


//克鲁斯卡尔算法求最短路径
int dijkstra(Graph *g, int start) {
  int nv = g->nv;
  int visit[nv];
  int dist[nv];  //存放到开始点的距离
  memset(visit, 0, sizeof(visit));
//  printf("begin!");
//  getchar();
  for (int i = 0; i < nv; i++) {  //初始化 dist 数组
    if (i == start) {
      dist[i] = 0;
    } else {
      dist[i] = getArcweight(g, start, i);
//      printf("%d -> %d = %d",start,i,dist[i]);//debug
//      getchar();
    }
  }
  printf("初始化完毕！");
  getchar();
  
  visit[start] = 1;

  int min, cur_min;               //记录边的最小权值和当前顶点
  for (int i = 0; i < nv; i++) {  //遍历所有顶点
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

  //打印 start 到其余所有顶点的最短路径值
	printf("最短路径:\n"); 
  for(int i = 0;i<nv;i++){
      if(i != start){
          printf("%d -> %d = %d \n",start,i,dist[i]);
      }
  }
}


int main() {
  int seed = 121;
  randgraph(5, 0.5, "draw.txt",
            seed);  //随机生成图；规定结点个数，结点连边概率，
  Graph *g = (Graph *)malloc(sizeof(Graph));
  printf("size of g = %ld\n", sizeof(Graph));
  initGraph(g, "draw.txt");
  printG(g);
  int w, h, t, id;

//  minGenTree(g);
//  printG(g);
//  getchar();
  
  printf("请输入想要搜索的顶点编号：\n");
  int key;
  scanf("%d",&key);
  printf("深度优先搜索结果：\n");
  DFS(g,0,key);
  getchar();
  printf("广度优先搜索结果：\n");
  BFS(g,0,key);
  getchar();
  
  printf("克鲁斯卡尔算法求最短路径：\n");
  printf("请输入起始点：\n");
  int start;
  scanf("%d",&start);//不要忘了取地址 
  dijkstra(g, start);
  getchar(); 
  
  
  return 0;
}

