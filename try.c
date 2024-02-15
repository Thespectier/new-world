//Your code begin.
//示例仅供参考，你也可以自行修改设计
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct ListNode            //结点结构，哈夫曼树与频度链表共用
{
	int     tag;                   //用来标记是否加入到树结点 
	int     partweight;            //字符的带权路径长 
    char      c;                    //结点的字符
    int      frequency;            // 字符的频度
    char     *code;            // 字符的编码(对哈夫曼树结点有效)
    struct ListNode *parent;            //结点的双亲结点(对哈夫曼树结点有效)
    struct ListNode *left;                //结点的左子树(对哈夫曼树结点有效)
    struct ListNode *right;                // 结点的右子树(对哈夫曼树结点有效)
    struct ListNode *next;                // 结点的后继结点(对频度链表结点有效)
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
	char ch;  //存放当前输入字符 
	int listlength = 0;  //统计表长 
    ListNode *p,*q,*tail;  //尾指针和新生成结点指针以及已输入字符结点指针 
    frelist->next = NULL; 
    tail = frelist;      
    // 先进先出建立链表 
	while((ch=getchar())!= EOF ){    //当字符不为结束字符时 
        if(!frelist->next){        // 当链表为空表时，建立第一个字符节点 
            p = (ListNode*)malloc(sizeof(ListNode));
            p->c = ch; p->frequency = 1; p->tag = 1;
            tail->next = p; tail = tail->next;
            tail->next = NULL;
            listlength++;
        }
        else{              //链表不为空时，分两种情况：当前字符不存在于链表中，或者存在于链表中 
            for(q=frelist->next;(q->next)&&(q->c!=ch);q=q->next); //遍历找寻是否存在于表中 
            if(q->c==ch) q->frequency++;    //存在时频度加一 
            else{                           //不存在时生成新的结点 
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
	//选择排序算法对频度表进行递减排序 
	ListNode *head,*tail,*p,*max,*pre; //head指针指向每轮排序起点，p为当前比较节点，pre为其前驱节点	                                     
	for(tail=frelist;tail->next;tail=tail->next); //tail指向表尾，用于每轮比较的结束 
	for(head=frelist;head->next!=tail;){   //每次找到的最大结点放于head处
        for(max=pre=head,p=head->next;p;){    //从head处开始每轮的比较 
            if(max->next->frequency<p->frequency){
                max = pre;                    //max的后继节点频度为最大 
            }
            pre = p;  p = p->next;    
        }                            
		//进行最大频度结点的换位  
        p = max->next;
        max->next = p->next;
        p->next = head->next;
        head->next = p;
        head = p;        //head指向最大节点的下一位置开始下一轮排序    
    }	
}

void creattree(ListNode *frelist)
{
	ListNode *p,*tail,*p1,*p2;  //p为临时节点，p1,p2为每轮的最小结点，tail结点指向表尾。 
	for(tail=frelist;tail->next;tail=tail->next); // 使tail结点指向表尾 
	// 建立哈夫曼树，当所有节点加入哈夫曼树中时结束循环。 
	while(1){              
    	for(p=frelist->next;p->tag!=1;p=p->next); //遍历表中结点，使p指向未加入哈夫曼树中结点 
    	if(p==tail) break;     //当p指向表尾时，表示所有结点加入哈夫曼树中，退出循环 
    	else{                 //当仍有结点未加入哈夫曼树时，p1,p2指向频度最小两个结点并生成新结点 
            for(p1=p;p;p=p->next){                      
                if((p->tag)&&(p1->frequency>p->frequency)){
                	p1 = p;
				}
			}
			p1->tag = 0;      //标记p1加入哈夫曼树 
			for(p=frelist->next;p->tag==0;p=p->next);
            for(p2=p;p;p=p->next){
                if((p->tag)&&(p2->frequency>p->frequency)){
                	p2 = p;
				}
			}
			p2->tag = 0;     //标记p2加入哈夫曼树
			//生成新结点使其左右孩子为p1和p2; 
			p=(ListNode*)malloc(sizeof(ListNode));
			p->frequency = p1->frequency+p2->frequency;
			p->left = p1; p->right = p2; p->tag = 1;
			p1->parent = p; p2->parent = p;
			tail->next = p; tail = tail->next;
			tail->next = NULL; 
			tail->parent = NULL;
		}
	}
	//完成哈夫曼树建立 
}

void creatcode(ListNode *frelist, int listlength)
{
	char *cd;                   //暂存字符编码 
	int i,start;                // i用于计数，start用于确定字符编码起始位置 
	ListNode *head,*son,*dad;  // head指向当前所求字符结点，son,dad用于溯源法求编码 
	cd = (char*)malloc(listlength*sizeof(char)); 
	cd[listlength-1] = '\0';    
	//遍历字符节点求编码 
	for(i=1,head=frelist->next;i<=listlength;i++,head=head->next){
		start = listlength-1;    //从尾部字符数组尾部开始存放编码 
		for(son=head,dad=son->parent;son->parent;son=dad,dad=dad->parent){ //从当前结点开始溯源 
			if(dad->left==son) cd[--start]='0';    //son为dad左儿子时 编码0，为右儿子时编码1 
			else  cd[--start]='1';
		}                                                         
		//为字符分配编码空间并复制编码，及得到字符结点在树中的带权路径长 
		head->code=(char*)malloc((listlength-start)*sizeof(char));
		strcpy(head->code,cd+start);    //复制编码 
		head->partweight = (listlength-start-1)*head->frequency;  //计算带权路径长 
	}
    free(cd);         //释放暂存空间 
}

void printtree(ListNode *frelist,int listlength)
{
	int treeweight,i; //treeweight用于求哈夫曼树总权重，i用于计数 
	ListNode *p;      //p指向当前字符结点；
	//遍历字符节点进行输出，并计算总权重 
	for(treeweight=0,p=frelist->next,i=1;i<=listlength;p=p->next,i++){
        if(p->c!='\n'){
            printf("'%c' %d %s\n",p->c, p->frequency,p->code);
        }
        else{
            printf("'\\n' %d %s\n",p->frequency,p->code);
        }
        treeweight+=p->partweight;
    }
    printf("%d\n",treeweight); //输出总权重 
    
}
