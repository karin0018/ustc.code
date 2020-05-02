#ifndef _HUFFMANTREE_CPP_
#define _HUFFMANTREE_CPP_
//�������� �����������洢�ռ�洢��

#include <stdio.h>
#include <stdlib.h>

//�������󳤶�
#define MCL 30
//����Ҷ�ڵ���,8bit��unsigned char
#define n 256
//������������2n-1
#define m 511

//��������㣬��������ָ�븸�ڵ㣬���Һ���
typedef struct{
	unsigned char id;
	long w;
	int parent,lchild,rchild;
} HTNode;

typedef struct{
	unsigned code; //ǰ�涼��0�����lenλ�Ǳ���
	int len;   //���볤��
} HCode;      //�����������

void printHtree1(HTNode ht[]); //��������
//����ͷ�ļ����������html�ļ����鿴ͼ



/*** ���´�������������� ***/
//�����������/������,���볤��Ϊn=256��Ȩ����w��ÿ���ַ����ֵĴ����� �������������±�
int createHTree(HTNode ht[], long *w){
	long allw=0;
	int numZero = 0;
	for(int i=0;i<m;++i){
		ht[i].id = i;
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
		ht[i].w = 0;
		if (i<n){
			ht[i].w = w[i];
			if (w[i]==0) numZero++; //ͳ��û���ֵ��ַ�����
			allw += w[i];
		}
	} //��ʼ������������ÿ����㹹��һ����

	int i=n,j;
	long min1,min2;
	while (i<m-numZero){
		min1=min2=allw+10; //��������wֵ
		unsigned pos1,pos2;
		for(j=0;j<i;j++){
			if (ht[j].w == 0) //����ȨֵΪ0�Ľ��
				continue;
			if (ht[j].parent == -1)
				if (ht[j].w < min1){
					pos2=pos1;
					min2=min1;
					pos1 = j;
					min1 = ht[j].w;
				} //min1<min2,�ҵ���min1��С��ht[j].w����ômin1���min2�� ht[j].w���min1
				else{
					if (ht[j].w < min2){ //min1 <= ht[j].w < min2
						pos2=j;
						min2=ht[j].w;
					}
				}
		}//�ڲ�for�������ҵ�pos1,pos2��С������Ȩֵ��׼�������Ҷ�ڵ�
		ht[i].lchild = pos1; //СȨֵΪ����
		ht[i].rchild = pos2;
		ht[i].w = min1+min2;
	//debug
		printf("No. %d - > %d \n", ht[i].id, ht[i].w);
        printf("lchild id %c w %d rchild id %c w %d \n", ht[i].lchild,
        ht[ht[i].lchild].w, ht[ht[i].rchild].id, ht[ht[i].rchild].w);
		getchar();
	//end debug
		ht[pos1].parent = ht[pos2].parent =i;
		i++;
	}
	return m-numZero-1;//���ظ����±�
}

//�������������ṹ�������׵�ַ��t�Լ��������±�ridx������������ (���������
void printHtree0(HTNode t[],int ridx){
	if (ridx>=0){ //�ݹ����
		if (t[ridx].w>0)
			printf("%3d->%5d\n",ridx<n?t[ridx].id:t[ridx].id+n,t[ridx].w);
		printHtree0(t,t[ridx].lchild);
		printHtree0(t,t[ridx].rchild);
	}
}

//ֱ�ӵ������ӡ������������
void printHtree1(HTNode ht[]){
	printf("\n��������(�������)��\n");
	for(int i=0;i<m;++i)
		if (i<n)
			printf("%2x %3d -> %5d => p:%3d lc:%3d rc:%3d\n",ht[i].id,ht[i].id, ht[i].w, ht[i].parent, ht[i].lchild,ht[i].rchild);
		else
			printf("%2x %3d -> %5d => p:%3d lc:%3d rc:%3d\n",ht[i].id,ht[i].id+256, ht[i].w, ht[i].parent, ht[i].lchild,ht[i].rchild);
}

/*** ���´�������ļ��ʹ��ļ������ɹ���������� ***/
//��filename�ж����ƶ�ȡ�ַ���ͳ��ÿ���ַ����ֵĴ�����д��w������
//w���鳤��Ϊ256������ַ�����256����ôû���ֵ��ַ�ȨֵΪ0
unsigned char *parseFile(const char filename[], long *w,long *fsize){
	FILE *fp = fopen(filename,"rb");
	if(fp == NULL){
        printf("�޷����ļ�!\n");
        exit(0);
    }
    fseek(fp,0,SEEK_END);
	*fsize = ftell(fp);
	rewind(fp);
	unsigned char *dataArray;
	dataArray = (unsigned char *)malloc(sizeof(unsigned char)*(*fsize));
	if (!dataArray) {
		printf("�ļ�̫���ڴ治�����������!\n");
		exit(0);
	}
	fread(dataArray,sizeof(unsigned char),*fsize,fp); //��ȡ��ѹ���ļ�
	fclose(fp);

	for (int i=0;i<n;++i) //Ȩֵ���
		w[i] = 0;

	for(int i=0;i<*fsize;++i) //Ȩֵ+1������Ӧ�ַ�����
		w[dataArray[i]]++;

	return dataArray;
}

//�����κ��ַ�c���õ����Ĺ���������, ��genCodes()����
void getCode(HTNode ht[], int c,unsigned *code1, int *clen1){
	int clen = 0;        //���볤��
	unsigned code = 0;   //����
	int size = sizeof(code);  //��������bits��
	unsigned mask = 1<<(size*8-1); //���λΪ1����Ϊ0�������������λΪ1

	int parent = ht[c].parent;
	while(parent>=0){
		code = code >> 1;
		(ht[parent].lchild==c)?code:code|= mask; //������Һ��ӣ���ô���λ����Ϊ1���������0
		clen++;
		/*debug
		printf("%d",parent);
		getchar();
		*/
		c = parent;
		parent = ht[c].parent;
	}

	//code��ǰ��clenλ�ǹ��������룬�����ƶ������
	code=code>>(size*8-clen);
/*debug
    printf("0x%x - %d\n",code,clen); //check the code
    getchar();
*/
	*code1 = code;  //����ֵ
	*clen1 = clen;  //����ֵ
}

//�ӹ�������ht���������ı����hc�����hcΪencode()���������
void genHCodes(HCode hc[], HTNode ht[]){
	for(int i=0;i<n;++i)
		if (ht[i].w>0)
			getCode(ht,i,&(hc[i].code),&(hc[i].len));
}

/*** ����Ϊ�����ʵ�� ***/
//����,ԭ��olen������orgi��ѹ�������Ϊ��nlen������newc����Ҫ���ñ����hc
void encode(unsigned char *orgi, long olen, unsigned char *newc, long *nlen, HCode hc[]){
	int sizec = sizeof(unsigned int);  //Ҫȷ���ַ��������󳤶�ҪС��sizec*8-8
	long i=0; //orgi���±�
	long j=0; //newc���±�
	newc[j] = 0;
	unsigned code;
	int len;
	int usedbits=0; //newc[j]�б�ռ�õ�bits��
	while (i<olen){//��ԭʼ��������ַ�����
		int idx = orgi[i]; //���hc�±�
		code = hc[idx].code;
		len = hc[idx].len;
		while (len+usedbits>=8){//code��Ҫ����usedbits����һ�Σ�Ȼ���newc[j]λ�����
			unsigned code1 = code >> len+usedbits-8;
			newc[j] = newc[j] | code1; //����ǰһ�������ַ�
			/*debug
			printf("0x%x",newc[j]);
			getchar();
			*/
			len = len+usedbits-8;      //code������Ч����
			usedbits = 0;
			newc[++j]=0;
			//printf("\n����ĵ� %d ���ַ�Ϊ��#%2x\n",j-1,newc[j-1]);
		}//ѭ����ʹ��len+usedbits <8
		//��code��ǰ���λ��0,��Ϊ��Чλ��len
		code = code & ((1<<len)-1); //code�ͺ���k��1������ȫΪ0�����ݽ����룬��������lenλ
		code = code << 8-len-usedbits;//��ǰ�ƶ�����λ
		newc[j] = newc[j] | code;

		usedbits = len+usedbits;
		i++;
	}
	*nlen = j+1;
}

//���ɺͱ���ѹ���ļ�,ָ���ļ���fout�������õĹ������������ļ�
void zip(char fout[],HTNode ht[],int root,HCode hc[],unsigned char *content,long fsize){
	unsigned char *zipContent; //����������
	long zipsize;//ѹ�����ļ���С
	zipContent = (unsigned char *)malloc(sizeof(unsigned char)*(fsize+10000));//ѹ������ļ����ܸ��󣬿��ǽ�fsize����һ��
	if (!zipContent) {
		printf("�ļ�̫���ڴ治�����������!\n");
		exit(0);
	}
	encode(content,fsize,zipContent,&zipsize,hc); //����󷵻س���zipsize������zipContent

	FILE *fp = fopen(fout,"wb");
	if(fp == NULL){
        printf("�޷���д���ļ�!\n");
        exit(0);
    }
    long ht_size = sizeof(HTNode)*m;      //�����������Ĵ�С
    fwrite(&ht_size,sizeof(ht_size),1,fp);//������������Ĵ�С
	fwrite(&zipsize,sizeof(zipsize),1,fp);//����������ݵĴ�С
	fwrite(&fsize,sizeof(fsize),1,fp);    //����ԭʼ���ݵĴ�С
	fwrite(&root,sizeof(root),1,fp);      //��������������ڵ���±�
    fwrite(ht,sizeof(HTNode),m,fp);       //����������� ������Ҫ�õ�
    fwrite(zipContent,sizeof(unsigned char),zipsize,fp);//�������������
	fclose(fp);

	free(zipContent);	//�ͷ��ļ�����
	printf("ѹ���ļ� %s �Ѿ����ɣ�\n",fout);
}

//��ȡѹ���ļ�����ѹ
void unzip(char zfile[],char ofile[]){
	FILE *fp = fopen(zfile,"rb");
	if(fp == NULL){
        printf("�޷���ѹ���ļ����ж�ȡ!\n");
        exit(0);
    }
    long ht_size1,zipsize1,fsize1;
    int root; //���ĸ�����±�
    fread(&ht_size1,sizeof(ht_size1),1,fp); //���������Ĵ�С(�ֽ�����
    fread(&zipsize1,sizeof(zipsize1),1,fp); //ѹ�������ݵĴ�С
    fread(&fsize1,sizeof(fsize1),1,fp);     //��ѹ�����ݵĴ�С
    fread(&root,sizeof(root),1,fp);         //�������������±�

	unsigned char *zcontent = (unsigned char *)malloc(zipsize1);//��Ŷ�ȡ�ı�������
	unsigned char *ocontent = (unsigned char *)malloc(fsize1);//����������
	HTNode ht1[m];
	fread(ht1,ht_size1,1,fp);//��ȡ��������
	fread(zcontent,zipsize1,1,fp); //��ȡ��������
	fclose(fp);

	fp = fopen(ofile,"wb");
	if(fp == NULL){
        printf("�޷��򿪽�ѹ���ļ����н�ѹ!\n");
        exit(0);
    }

	int idx = root; //�Ӹ���ʼ
	int j,k=0,i=0;//zcontent���±� k,ocontent���±�i

	for (int r = 0;r<zipsize1
	;r++){
      printf("0x%x\n",zcontent[r]);
      getchar();
    }

	while (i<fsize1){//����д���ѹ�����ݵ�ÿ���ֽ�
		j =128; //10000000
		while (j>0){
			//debug
			printf("0x%x",zcontent[k]);
			getchar();
			if ((zcontent[k] & j)>0){ //������ 1
				if (ht1[idx].rchild==-1){
					ocontent[i++] = ht1[idx].id;

					printf("%d",ht1[idx].id);
					printf("%c",ocontent[i-1]);
					getchar();
					//*debug*//
                    printf("%c",ocontent[i-1]);
            		getchar();

					idx = root;//��������һ���ַ��ĵ�һ��bit
					fprintf(fp,"%c",ocontent[i-1]);
					if (i>=fsize1) //�������
						break;
					j=j<<1;
				}else
					idx = ht1[idx].rchild;
			}else{//������ 0
				if (ht1[idx].lchild==-1){
					ocontent[i++] = ht1[idx].id;
					idx = root;//��������һ���ַ��ĵ�һ��bit
					fprintf(fp,"%c",ocontent[i-1]);
					if (i>=fsize1) //�������
						break;
					j=j<<1;
				}else
					idx = ht1[idx].lchild;
			}
			j=j>>1; //j����whileѭ��8�Σ����zcontent[k]��ÿһλ
		}
		if (i>=fsize1) //�������
						break;
		k++;//׼����ȡ��һ���ַ�
	}
	fclose(fp);
	free(ocontent);
	free(zcontent);
	printf("�ļ� %s �Ѿ��ɹ���ѹΪ %s ��\n",zfile,ofile);
}

int main(){
	HTNode ht[m];   //�ṹ�����飬��ʾ�������� : id,w,parent,lchild,rchild���������ɱ����ͽ�ѹ
	HCode hc[n];    //�ṹ�����飬��ʾ����������� :code,len�����ڱ����ļ�

	/*** ��ȡ�ļ��������ļ��ַ����ֹ��ɣ������������������ɹ���������� ***/
	char infile[]="data.txt";
	long wDist[256]; //�����ַ��ķֲ����ַ����ļ��г��ֵĴ�����
	long fsize;      //�ļ�����
    //��ȡ�ļ����ݣ�������ѹ���ļ�������Ȩֵ����wDist,�ļ�����content�ͳ���fsize
	unsigned char *content = parseFile(infile,wDist,&fsize);
	int root = createHTree(ht,wDist); //root�ǹ�������ht�ĸ������±�
	genHCodes(hc,ht);//���������ı����,���ڱ����ļ�

	//����Ĵ������ڲ��Թ�������
	//printHtree1(ht); //�����������������ӡ����
	//printHtree0(ht,root); //���������������
	//saveTree(ht,root,"aa1.html"); //ͼ��չʾ��������

	//���룬ѹ���ļ�,д���ļ� fout
	char zfile[256]="my.lzip";
	zip(zfile,ht,root,hc,content,fsize);


/*************************** ����Ϊ�������� ****************************/
	char ofile[256]="ndata.txt";
	unzip(zfile,ofile);

	free(content);
	return 1;
}

#endif
