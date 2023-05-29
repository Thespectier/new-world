//Your code begin.
//ʾ�������ο�����Ҳ���������޸����
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct ListNode            //���ṹ������������Ƶ��������
{
	int     tag;                   //��������Ƿ���뵽����� 
	int     partweight;            //�ַ��Ĵ�Ȩ·���� 
    char      c;                    //�����ַ�
    int      frequency;            // �ַ���Ƶ��
    char     *code;            // �ַ��ı���(�Թ������������Ч)
    struct ListNode *parent;            //����˫�׽��(�Թ������������Ч)
    struct ListNode *left;                //����������(�Թ������������Ч)
    struct ListNode *right;                // ����������(�Թ������������Ч)
    struct ListNode *next;                // ���ĺ�̽��(��Ƶ����������Ч)
}ListNode;

int  creatlist(ListNode *frelist);
void sortlist(ListNode *frelist);
void creattree(ListNode *frelist);
void creatcode(ListNode *frelist, int listlength);
void printtree(ListNode *frelist, int listlength);
 
 
int main()
{
    ListNode *frelist;
    int listlength;
    frelist = (ListNode*)malloc(sizeof(ListNode)); 
    listlength = creatlist(frelist);
    sortlist(frelist);
    creattree(frelist);
	creatcode(frelist,listlength);
	printtree(frelist,listlength); 
    return 0;
}

int creatlist(ListNode *frelist)
{
	char ch;  //��ŵ�ǰ�����ַ� 
	int listlength = 0;  //ͳ�Ʊ� 
    ListNode *p,*q,*tail;  //βָ��������ɽ��ָ���Լ��������ַ����ָ�� 
    frelist->next = NULL; 
    tail = frelist;      
    // �Ƚ��ȳ��������� 
	while((ch=getchar())!= EOF ){    //���ַ���Ϊ�����ַ�ʱ 
        if(!frelist->next){        // ������Ϊ�ձ�ʱ��������һ���ַ��ڵ� 
            p = (ListNode*)malloc(sizeof(ListNode));
            p->c = ch; p->frequency = 1; p->tag = 1;
            tail->next = p; tail = tail->next;
            tail->next = NULL;
            listlength++;
        }
        else{              //����Ϊ��ʱ���������������ǰ�ַ��������������У����ߴ����������� 
            for(q=frelist->next;(q->next)&&(q->c!=ch);q=q->next); //������Ѱ�Ƿ�����ڱ��� 
            if(q->c==ch) q->frequency++;    //����ʱƵ�ȼ�һ 
            else{                           //������ʱ�����µĽ�� 
                p = (ListNode*)malloc(sizeof(ListNode));
                p->c = ch; p->frequency = 1; p->tag = 1;
                tail->next = p; tail = tail->next;
                tail->next = NULL;
                listlength++;
            }
        }
    }
    return listlength;
}


void sortlist(ListNode* frelist)
{
	//ѡ�������㷨��Ƶ�ȱ���еݼ����� 
	ListNode *head,*tail,*p,*max,*pre; //headָ��ָ��ÿ��������㣬pΪ��ǰ�ȽϽڵ㣬preΪ��ǰ���ڵ�	                                     
	for(tail=frelist;tail->next;tail=tail->next); //tailָ���β������ÿ�ֱȽϵĽ��� 
	for(head=frelist;head->next!=tail;){   //ÿ���ҵ�����������head��
        for(max=pre=head,p=head->next;p;){    //��head����ʼÿ�ֵıȽ� 
            if(max->next->frequency<p->frequency){
                max = pre;                    //max�ĺ�̽ڵ�Ƶ��Ϊ��� 
            }
            pre = p;  p = p->next;    
        }                            
		//�������Ƶ�Ƚ��Ļ�λ  
        p = max->next;
        max->next = p->next;
        p->next = head->next;
        head->next = p;
        head = p;        //headָ�����ڵ����һλ�ÿ�ʼ��һ������    
    }	
}

void creattree(ListNode *frelist)
{
	ListNode *p,*tail,*p1,*p2;  //pΪ��ʱ�ڵ㣬p1,p2Ϊÿ�ֵ���С��㣬tail���ָ���β�� 
	for(tail=frelist;tail->next;tail=tail->next); // ʹtail���ָ���β 
	// �������������������нڵ�������������ʱ����ѭ���� 
	while(1){              
    	for(p=frelist->next;p->tag!=1;p=p->next); //�������н�㣬ʹpָ��δ������������н�� 
    	if(p==tail) break;     //��pָ���βʱ����ʾ���н�������������У��˳�ѭ�� 
    	else{                 //�����н��δ�����������ʱ��p1,p2ָ��Ƶ����С������㲢�����½�� 
            for(p1=p;p;p=p->next){                      
                if((p->tag)&&(p1->frequency>p->frequency)){
                	p1 = p;
				}
			}
			p1->tag = 0;      //���p1����������� 
			for(p=frelist->next;p->tag==0;p=p->next);
            for(p2=p;p;p=p->next){
                if((p->tag)&&(p2->frequency>p->frequency)){
                	p2 = p;
				}
			}
			p2->tag = 0;     //���p2�����������
			//�����½��ʹ�����Һ���Ϊp1��p2; 
			p=(ListNode*)malloc(sizeof(ListNode));
			p->frequency = p1->frequency+p2->frequency;
			p->left = p1; p->right = p2; p->tag = 1;
			p1->parent = p; p2->parent = p;
			tail->next = p; tail = tail->next;
			tail->next = NULL; 
			tail->parent = NULL;
		}
	}
	//��ɹ����������� 
}

void creatcode(ListNode *frelist, int listlength)
{
	char *cd;                   //�ݴ��ַ����� 
	int i,start;                // i���ڼ�����start����ȷ���ַ�������ʼλ�� 
	ListNode *head,*son,*dad;  // headָ��ǰ�����ַ���㣬son,dad������Դ������� 
	cd = (char*)malloc(listlength*sizeof(char)); 
	cd[listlength-1] = '\0';    
	//�����ַ��ڵ������ 
	for(i=1,head=frelist->next;i<=listlength;i++,head=head->next){
		start = listlength-1;    //��β���ַ�����β����ʼ��ű��� 
		for(son=head,dad=son->parent;son->parent;son=dad,dad=dad->parent){ //�ӵ�ǰ��㿪ʼ��Դ 
			if(dad->left==son) cd[--start]='0';    //sonΪdad�����ʱ ����0��Ϊ�Ҷ���ʱ����1 
			else  cd[--start]='1';
		}                                                         
		//Ϊ�ַ��������ռ䲢���Ʊ��룬���õ��ַ���������еĴ�Ȩ·���� 
		head->code=(char*)malloc((listlength-start)*sizeof(char));
		strcpy(head->code,cd+start);    //���Ʊ��� 
		head->partweight = (listlength-start-1)*head->frequency;  //�����Ȩ·���� 
	}
    free(cd);         //�ͷ��ݴ�ռ� 
}

void printtree(ListNode *frelist,int listlength)
{
	int treeweight,i; //treeweight���������������Ȩ�أ�i���ڼ��� 
	ListNode *p;      //pָ��ǰ�ַ���㣻
	//�����ַ��ڵ�����������������Ȩ�� 
	for(treeweight=0,p=frelist->next,i=1;i<=listlength;p=p->next,i++){
        if(p->c!='\n'){
            printf("'%c' %d %s\n",p->c, p->frequency,p->code);
        }
        else{
            printf("'\\n' %d %s\n",p->frequency,p->code);
        }
        treeweight+=p->partweight;
    }
    printf("%d\n",treeweight); //�����Ȩ�� 
    
}
