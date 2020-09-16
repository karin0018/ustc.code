/*
�����ڽӱ��ͼ�Ĵ�����
���ӡ�ɾ�����㣻
���ӡ�ɾ���ߣ�
���Ҷ��㣬�޸Ķ���ͱ�
*/

#include <stdio.h>
#include <stdlib.h>

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
  int used;//�Ƿ�ʹ��--��С��������ʹ�� 
  struct ArcNode *nextarc;  //ָ����һ����ָ��
} ArcNode, ArcList[MAXE];   //������

// define vertex's strcut
typedef struct Vnode {
  int id;                //������
  int w;                 //����Ȩֵ
  int degree;            //������ȣ������ڽ�����ĳ���
  int cp; 				//��ͨƬ��� 
  ArcNode *firstarc;     //ָ���һ�������ö���Ļ�
} Vnode, AdjList[MAXV];  //��������

//����ͼ���
typedef struct {
  AdjList vertices;
  ArcList e;//������
  int nv;
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
    g->vertices[h].degree++;
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
	for(int a=0;a<g->nv;a++){
		g->vertices[a].cp = a;
	} 
	for(int b = 0; b<g->ne;b++){
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
    	if(e->id != -1){
			printf("-> %u(%d-%d) ", e->t, e->id, e->w);  //�붥��g->v[i]�����ıߵ�β��㡢�ߵı�š��ߵ�Ȩֵ
		}
      e = e->nextarc; 
	}
    printf("\n");
  }
}

//��ͼ�Ķ������ҵ����㣬�����������Ȩֵ�Լ�������ıߵ���ϸ��Ϣ
void getVertex(Graph *g,int id) {

    if(g->vertices[id].id == -1){
  	  printf("the vertex has been deleted!");
  	  exit(0);
    }
    printf("ID(%u)-degree(%d)-weight(%d) -ArcList (eid|w)��%u ",
    g->vertices[id].id, g->vertices[id].degree, g->vertices[id].w,
    g->vertices[id].id);
    ArcNode *e = g->vertices[id].firstarc;
    for (int j = 0; j < g->vertices[id].degree; ++j) {
    	if(e->id != -1){
			printf("-> %u(%d-%d) ", e->t, e->id, e->w);  //�붥��g->v[i]�����ıߵ�β��㡢�ߵı�š��ߵ�Ȩֵ
		}
		e = e->nextarc;
    }
    printf("\n");
}

//����һ����������
void addVertex(Graph *g,int w) {
  g->vertices[g->nv].id = g->nv;
  g->vertices[g->nv].w = w;
  g->vertices[g->nv].degree = 0;
  (g->nv)++;
  printf("the new vertex is added successfully!");
}

//����һ���ߣ�head ���ĳ���++���������ڽ�����
void addArc(Graph *g,int h,int t,int w) {
  if (h > g->nv || t > g->nv) {
    printf("the head or tail vertex is not founded!");
    exit(0);
  }
  //ͷ�壬�޸��ڽӱ�
  ArcNode *arc = new ArcNode;
  arc->id = g->ne;
  arc->h = h;
  arc->t = t;
  arc->w = w;
  arc->nextarc = g->vertices[h].firstarc;
  g->vertices[h].firstarc = arc; 
  //�޸ı����� 
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

void ClearList(Graph *g,ArcNode *p){//p ��ͷָ��ĵ�ַ
	while(p != NULL){
		g->e[p->id].id = -1 ;//�ڱ�������ɾ���ñ�
		p->id = -1;
		p = p->nextarc;
	}
}

//ɾ��һ��ָ�� id �Ķ��㣬�Լ��������������б�
void delVertex(Graph *g,int id) {
  int degree = g->vertices[id].degree; 
  g->delne += degree;
  g->nv--;
//�����һ���������Ϣ���ǹ��� ,������ͬʱ�޸� 
  int nv = g->nv ;
  g->vertices[id].w = g->vertices[nv].w;
  g->vertices[id].degree =  g->vertices[nv].degree;
  ClearList(g,g->vertices[id].firstarc);//���ԭ�ڽ����� 
  g->vertices[id].firstarc = g->vertices[nv].firstarc;
  g->vertices[nv].firstarc = NULL;
  
  for(int j = 0;j< g->ne;j++){
  	if(g->e[j].t == id){
  		g->e[j].id = -1;
  		int h = g->e[j].h;
  		ArcNode *arc ;
    	arc=g->vertices[h].firstarc;
		for(;arc != NULL ; arc=arc->nextarc){
			if (arc->t == id){  //�ҵ�ɾ��λ��
				arc->id = -1;        //ɾ���ñ�
				g->e[id].id = -1 ;//�ڱ�������ɾ���ñ� 
				g->delne ++;
				printf("the arc is deleted successfully!\n");
			}
		}
	  }
  }
  printf("the vertex is deleted successfully!\n");
}


//ɾ��ָ����ŵı�
void delArc(Graph *g,int id){
    if(id>g->ne){
        printf("the arc is not exit!");
        exit(0);
    }
    int h;//�ҵ�����ͷ����
    h = g->e[id].h;
    ArcNode *arc;
    arc = g->vertices[h].firstarc;
	for(;arc;arc=arc->nextarc){
		if (arc->id == id){  //�ҵ�ɾ��λ��
			arc->id = -1;   //���ڽӱ���ɾ���ñ� 
			g->e[id].id = -1 ;//�ڱ�������ɾ���ñ� 
			g->vertices[h].degree--;//�������-- 
			g->delne ++;//�����Ҫɾ���ı�++ 
			printf("the arc is deleted successfully!\n");
		}
	}
}

//�õ�ĳ�� (h,t) ��Ȩ�ز�����
int getArcweight(Graph *g,int h,int t){
    for(int i = 0 ;i<g->ne;i++){
        if((h == g->e[i].h) && t== g->e[i].t){
            return g->e[i].w;
        }
    }
    printf("the arc is not founded!");
    return -1;
}

//���ݶ������޸Ķ���Ȩ�� 
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
//���ݱߵı���޸ıߵ�Ȩ�� 
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
			printf("-> %u(%d-%d) ", e->t, e->id, e->w);  //�붥��g->v[i]�����ıߵ�β��㡢�ߵı�š��ߵ�Ȩֵ
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
 
 
//��³˹���� �㷨����С������
//���Ľṹ��--����ṹ���������ͨƬ��� cp�� �߽ṹ����ӱ�ʹ�ñ�� used
//�ҵ�Ȩֵ��С�ı�,���ر��ڱ������е�λ�� 
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

void resetUse(Graph *g,int h,int t){//ʹ(h,t)֮��ı�ȫ�����õ�
	for(int i = 0;i< (g->ne);i++){//������h���Ϊͷ��tΪβ�ıߣ�����used 
		if((g->e[i].id != -1)&&(g->e[i].t == t)&&(g->e[i].h==h)){
			printf("used (1) - %d",g->e[i].id);
			getchar();
			g->e[i].used = 1;
			break;
		}
	}	 
	
} 
 
void minGenTree(Graph *g){
	printf("��С��������\n"); 
	int nv = g->nv;//��ʾ��ͨƬ���� 
	int ne = g->ne;//��ʾʣ��ߵ����� 
	int h,t,id,cph,cpt;
	int vt[g->nv] ;
	for(int a =0;a<g->nv;a++){
		vt[a]=0;
	} 
	
	while(nv > 1 && ne > 0){
        id = getMinArc(g);//Ȩֵ��С�ı��ڱ������е�λ��
		g->e[id].used = 1;//���ı������used��Ϣ 
		ne--; 
		h = g->e[id].h;//ͷ������ 
		t = g->e[id].t;//β������ 
		cph = g->vertices[h].cp;
		cpt = g->vertices[t].cp;
		printf("cph %d cpt %d\n",cph,cpt);
		if(cph != cpt){
		    nv--;
			g->vertices[h].cp = g->vertices[t].cp=cpt;
			
			if((vt[h]==1)&&(vt[t]==1)){
				printf("�޸���ͨƬ���\n");
				getchar();
				for(int i = 0;i< (g->ne);i++){//������h���Ϊͷ�ıߣ����Ķ��������ͨƬ��� 
					if((g->e[i].id != -1)&&(g->e[i].used == 1)&&(g->e[i].h==h)){
						printf("used==%d - h %d - h' %d",g->e[i].used,h,g->e[i].h);
						g->vertices[g->e[i].t].cp = cpt;
						resetUse(g,g->e[i].t,h);//��(h,t)֮�䲻�ٻ��б� 
					}
				}
				printf("��������");
				getchar(); 
				for(int i = 0;i< (g->ne);i++){//������h���Ϊβ�ıߣ����Ķ��������ͨƬ��� 
					
					if((g->e[i].id != -1)&&(g->e[i].used == 1)&&(g->e[i].t==h)){
						printf("used==%d -%d - h %d",g->e[i].used,g->e[i].t,h);
						g->vertices[g->e[i].h].cp = cpt;
						resetUse(g,g->e[i].h,t);//��(h,t)֮�䲻�ٻ��б� 
						
					}
				}	
				
			}
			vt[h] = 1;
			vt[t] = 1;
			
			printf("��ͨƬ����--%d eid %d (head %d -> tail %d) weight %d\n",nv,g->e[id].id,h,t,g->e[id].w);
		}		
	}

} 
 

int main() {
  int seed = 121;
  randgraph(6, 0.4, "draw.txt",
            seed);  //�������ͼ���涨��������������߸��ʣ�
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

