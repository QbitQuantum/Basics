/*************************************************
Function: 	CreatMyList(n) 
Description: 建立链表
Calls:none
Called By: Loading()
Input: 文件指针，指向一个存字母的文件的指针
Output: // 对输出参数的说明。
Return: 返回头指针
Others: 
*************************************************/
WorData *CreatMyList(FILE *open)      
{
	char readin='\0';            //第一次没加此语句造成readin的值无法确定
	int i,j,flag;
	int k=0;
	WorData *p=NULL,*head=NULL,*q=NULL;

    while (1)      
	{
		if ((p=(WorData *)malloc(sizeof(WorData)))==NULL) 
		{
			printf("\nBuild Error 002");   return NULL;
		}
		else 
		{
			strset(p->english,'\0');      //5.23 add
			strset(p->chinese,'\0');
			p->next=NULL;
		}
		readin=fgetc(open);
		if (readin=='@') break;     //未加该行，第二while将死循环
		i=0;
		j=0;
		flag=0;          //未赋初值错误

    	while (readin!='#')
		{
			while (flag!=1)
			{
				if (readin >=20) p->english[i++]=readin;          //add   if (readin >=20)  控制字符不加入到单词中
				readin=fgetc(open);
				if(readin==' ') flag=1;
			}
		    p->chinese[j++]=readin;
	        readin=fgetc(open);
		}
	   readin=fgetc(open);          //由于在#号后还有一个换行符，未加该行，在第一个readin将读入换行符导致第二个while死循环
	   p->english[i]='\0';       
	   p->chinese[j]='\0';          //写入结束
		if (k==0) 
		{
			head=p;
			q=p;
		}
		else 
		{
			q->next=p;
			q=p;
		}
		k++;
	}
	fclose(open);
	return head;
}