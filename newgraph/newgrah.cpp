/*
基于邻接表的图的创建；
增加、删除顶点；
增加、删除边；
查找顶点，修改顶点和边
*/

#include <stdio.h>
#include <stdlib.h>

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
  int used;//是否被使用--最小生成树中使用 
  struct ArcNode *nextarc;  //指向下一条弧指针
} ArcNode, ArcList[MAXE];   //边数组

// define vertex's strcut
typedef struct Vnode {
  int id;                //顶点编号
  int w;                 //顶点权值
  int degree;            //顶点出度，顶点邻接链表的长度
  int cp; 				//连通片编号 
  ArcNode *firstarc;     //指向第一条依附该顶点的弧
} Vnode, AdjList[MAXV];  //顶点数组

//定义图结点
typedef struct {
  AdjList vertices;
  ArcList e;//边数组
  int nv;
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
    g->vertices[h].degree++;
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
	for(int a=0;a<g->nv;a++){
		g->vertices[a].cp = a;
	} 
	for(int b = 0; b<g->ne;b++){
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
    	if(e->id != -1){
			printf("-> %u(%d-%d) ", e->t, e->id, e->w);  //与顶点g->v[i]相连的边的尾结点、边的编号、边的权值
		}
      e = e->nextarc; 
	}
    printf("\n");
  }
}

//从图的顶点编号找到顶点，返回输出顶点权值以及相关联的边的详细信息
void getVertex(Graph *g,int id) {

    if(g->vertices[id].id == -1){
  	  printf("the vertex has been deleted!");
  	  exit(0);
    }
    printf("ID(%u)-degree(%d)-weight(%d) -ArcList (eid|w)：%u ",
    g->vertices[id].id, g->vertices[id].degree, g->vertices[id].w,
    g->vertices[id].id);
    ArcNode *e = g->vertices[id].firstarc;
    for (int j = 0; j < g->vertices[id].degree; ++j) {
    	if(e->id != -1){
			printf("-> %u(%d-%d) ", e->t, e->id, e->w);  //与顶点g->v[i]相连的边的尾结点、边的编号、边的权值
		}
		e = e->nextarc;
    }
    printf("\n");
}

//增加一个孤立顶点
void addVertex(Graph *g,int w) {
  g->vertices[g->nv].id = g->nv;
  g->vertices[g->nv].w = w;
  g->vertices[g->nv].degree = 0;
  (g->nv)++;
  printf("the new vertex is added successfully!");
}

//增加一条边，head 结点的出度++，更改其邻接链表
void addArc(Graph *g,int h,int t,int w) {
  if (h > g->nv || t > g->nv) {
    printf("the head or tail vertex is not founded!");
    exit(0);
  }
  //头插，修改邻接表
  ArcNode *arc = new ArcNode;
  arc->id = g->ne;
  arc->h = h;
  arc->t = t;
  arc->w = w;
  arc->nextarc = g->vertices[h].firstarc;
  g->vertices[h].firstarc = arc; 
  //修改边数组 
  g->e[g->ne].h = h;
  g->e[g->ne].id = g->ne;
  g->e[g->ne].t = t;
  g->e[g->ne].w = w;
  for(arc = g->vertices[h].firstarc;arc!=NULL;arc = arc->nextarc){
    printf("root %d ,arc head %d,tail %d weight %d\n",h,arc->h,arc->t,arc->w); 
	getchar();
  }
  (g->ne)++;
  (g->vertices[h].degree)++;
}

void ClearList(Graph *g,ArcNode *p){//p 是头指针的地址
	while(p != NULL){
		g->e[p->id].id = -1 ;//在边数组中删掉该边
		p->id = -1;
		p = p->nextarc;
	}
}

//删除一个指定 id 的顶点，以及它所关联的所有边
void delVertex(Graph *g,int id) {
  int degree = g->vertices[id].degree; 
  g->delne += degree;
  g->nv--;
//把最后一个顶点的信息覆盖过来 ,顶点编号同时修改 
  int nv = g->nv ;
  g->vertices[id].w = g->vertices[nv].w;
  g->vertices[id].degree =  g->vertices[nv].degree;
  ClearList(g,g->vertices[id].firstarc);//清空原邻接链表 
  g->vertices[id].firstarc = g->vertices[nv].firstarc;
  g->vertices[nv].firstarc = NULL;
  
  for(int j = 0;j< g->ne;j++){
  	if(g->e[j].t == id){
  		g->e[j].id = -1;
  		int h = g->e[j].h;
  		ArcNode *arc ;
    	arc=g->vertices[h].firstarc;
		for(;arc != NULL ; arc=arc->nextarc){
			if (arc->t == id){  //找到删除位置
				arc->id = -1;        //删掉该边
				g->e[id].id = -1 ;//在边数组中删掉该边 
				g->delne ++;
				printf("the arc is deleted successfully!\n");
			}
		}
	  }
  }
  printf("the vertex is deleted successfully!\n");
}


//删除指定编号的边
void delArc(Graph *g,int id){
    if(id>g->ne){
        printf("the arc is not exit!");
        exit(0);
    }
    int h;//找到弧的头顶点
    h = g->e[id].h;
    ArcNode *arc;
    arc = g->vertices[h].firstarc;
	for(;arc;arc=arc->nextarc){
		if (arc->id == id){  //找到删除位置
			arc->id = -1;   //在邻接表中删掉该边 
			g->e[id].id = -1 ;//在边数组中删掉该边 
			g->vertices[h].degree--;//顶点度数-- 
			g->delne ++;//被标记要删除的边++ 
			printf("the arc is deleted successfully!\n");
		}
	}
}

//得到某边 (h,t) 的权重并返回
int getArcweight(Graph *g,int h,int t){
    for(int i = 0 ;i<g->ne;i++){
        if((h == g->e[i].h) && t== g->e[i].t){
            return g->e[i].w;
        }
    }
    printf("the arc is not founded!");
    return -1;
}

//根据顶点编号修改顶点权重 
void  resetVex(Graph *g,int id,int w){
	int flag = 0;	
	for(int i=0;i < g->nv;i++){
		if(g->vertices[i].id == id){
			g->vertices[i].w = w;
			printf("the weight has been changed successfully!\n");
			flag++;
			break;
		}
	}
	if(flag == 0)
		printf("the number of vertex is not found!\n");		
}
//根据边的编号修改边的权重 
void resetArc (Graph *g, int id,int w){
	if(g->e[id].id == -1){
		printf("this arc has been delete!");
		exit(0);
	}
	else if (id < g->ne){
		g->e[id].w = w;
		int h =g->e[id].h;
		int t = g->e[id].t;
		ArcNode *e = g->vertices[h].firstarc;
        for (int j = 0; j < g->vertices[h].degree; ++j) {
    	if((e->id != -1)&&(e->t == t)){
    		e->w = w;
			printf("-> %u(%d-%d) ", e->t, e->id, e->w);  //与顶点g->v[i]相连的边的尾结点、边的编号、边的权值
		}
		e = e->nextarc;
    }		
		 
		printf("done!\n");
		getchar();
	}
	else {
		printf("the arc is not found !");
	}	
}
 
 
//克鲁斯卡尔 算法求最小生成树
//更改结构体--顶点结构体中添加连通片编号 cp； 边结构体添加被使用标记 used
//找到权值最小的边,返回边在边数组中的位置 
int getMinArc(Graph *g){
	int min = INF;
	int id;
	for(int i = 0;i<g->ne;i++){
		if((g->e[i].id != -1)&&(g->e[i].used == 0)){
			printf("unused - id %d",g->e[i].id);//debug
			getchar();
			if(min > g->e[i].w){
				min = g->e[i].w;
				id = g->e[i].id ;
				printf("%d",id);//debug
				getchar();
			}
		}
	}
	return id;
} 

void resetUse(Graph *g,int h,int t){//使(h,t)之间的边全部被用掉
	for(int i = 0;i< (g->ne);i++){//搜索以h结点为头以t为尾的边，更改used 
		if((g->e[i].id != -1)&&(g->e[i].t == t)&&(g->e[i].h==h)){
			printf("used (1) - %d",g->e[i].id);
			getchar();
			g->e[i].used = 1;
			break;
		}
	}	 
	
} 
 
void minGenTree(Graph *g){
	printf("最小生成树：\n"); 
	int nv = g->nv;//表示连通片个数 
	int ne = g->ne;//表示剩余边的数量 
	int h,t,id,cph,cpt;
	int vt[g->nv] ;
	for(int a =0;a<g->nv;a++){
		vt[a]=0;
	} 
	
	while(nv > 1 && ne > 0){
        id = getMinArc(g);//权值最小的边在边数组中的位置
		g->e[id].used = 1;//更改边数组的used信息 
		ne--; 
		h = g->e[id].h;//头顶点编号 
		t = g->e[id].t;//尾顶点编号 
		cph = g->vertices[h].cp;
		cpt = g->vertices[t].cp;
		printf("cph %d cpt %d\n",cph,cpt);
		if(cph != cpt){
		    nv--;
			g->vertices[h].cp = g->vertices[t].cp=cpt;
			
			if((vt[h]==1)&&(vt[t]==1)){
				printf("修改连通片编号\n");
				getchar();
				for(int i = 0;i< (g->ne);i++){//搜索以h结点为头的边，更改对面结点的连通片编号 
					if((g->e[i].id != -1)&&(g->e[i].used == 1)&&(g->e[i].h==h)){
						printf("used==%d - h %d - h' %d",g->e[i].used,h,g->e[i].h);
						g->vertices[g->e[i].t].cp = cpt;
						resetUse(g,g->e[i].t,h);//让(h,t)之间不再会有边 
					}
				}
				printf("继续搜索");
				getchar(); 
				for(int i = 0;i< (g->ne);i++){//搜索以h结点为尾的边，更改对面结点的连通片编号 
					
					if((g->e[i].id != -1)&&(g->e[i].used == 1)&&(g->e[i].t==h)){
						printf("used==%d -%d - h %d",g->e[i].used,g->e[i].t,h);
						g->vertices[g->e[i].h].cp = cpt;
						resetUse(g,g->e[i].h,t);//让(h,t)之间不再会有边 
						
					}
				}	
				
			}
			vt[h] = 1;
			vt[t] = 1;
			
			printf("连通片个数--%d eid %d (head %d -> tail %d) weight %d\n",nv,g->e[id].id,h,t,g->e[id].w);
		}		
	}

} 
 

int main() {
  int seed = 121;
  randgraph(6, 0.4, "draw.txt",
            seed);  //随机生成图；规定结点个数，结点连边概率，
  Graph *g = (Graph *)malloc(sizeof(Graph));
  printf("size of g = %ld\n", sizeof(Graph));
  initGraph(g, "draw.txt");
  printG(g);
  int w,h,t,id;

  minGenTree(g);
  printG(g); 
  getchar();
  
  printf("please input the weight of a vertex\n");
  scanf("%d",&w);
  addVertex(g,w);
  getchar();
  printG(g);

  printf("please input head vernum, tail vernum, weight\n");
  
  scanf("%d%d%d", &h, &t, &w);
  addArc(g,h,t,w);
  getchar();
  printG(g);

  printf("please input the vertex id that you want to delete \n");
  
  scanf("%d", &id);
  delVertex(g,id);
  getchar();
  printG(g);

  printf("please input the number of arc that you want to del \n");
  scanf("%d",&id);
  delArc(g,id);

  getchar();
  printG(g);
     

  printf("please input the number of vertex that you want to find :\n");
  scanf("%d",&id);
  getVertex(g,id);
  getchar();
  printG(g);
  
  printf("please input the number of head and tail ,then you will get the weight of this arc:\n");
  scanf("%d%d",&h,&t);
  w = getArcweight(g,h,t);
  printf("the arc's weight is : %d \n",w);
  getchar();
  printG(g); 

  printf("please input the vertex numer & weight that you want to change\n");
  scanf("%d%d",&id,&w);  
  resetVex(g,id,w);
  getchar();
  printG(g);  
  
  printf("please input the arc numer & weight that you want to change\n");
  scanf("%d%d",&id,&w);  
  resetArc(g,id,w);
  getchar();
  

  return 0;
}

