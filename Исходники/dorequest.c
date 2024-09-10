/* 产生访存请求 */
int readrequest(Ptr_MemoryAccessRequest ptr_memAccReq)
{
	printf("请输入访存请求(输入x结束程序):\n");
	char c;
	unsigned long addr;
	BYTE value;
	int i,num;
	c=getchar();//读取请求类型
	//printf("#c的值是%c#\n",c);
	if(c!='s'&&c!='x'&&c!='y'){//如果c不是s或x则读取请求地址
		scanf(" %lu",&addr);//读取请求地址
		ptr_memAccReq->command=0;//不是命令	
	}
	switch(c){
		case 'r':
			ptr_memAccReq->reqType = REQUEST_READ;
			ptr_memAccReq->virAddr = addr;
			scanf(" %u",&(ptr_memAccReq->pid));
			printf("产生请求：\n地址：%lu\t类型：读取\tPID:%u\n", ptr_memAccReq->virAddr,ptr_memAccReq->pid);
            break;
        case 'w':
			ptr_memAccReq->reqType = REQUEST_WRITE;
			ptr_memAccReq->virAddr = addr;
            scanf(" %c",&value);//读入要写入的值
            ptr_memAccReq->value = value;
            scanf(" %u",&(ptr_memAccReq->pid));
            printf("产生请求：\n地址：%lu\t类型：写入\t值：%02X\tPID:%u\n", ptr_memAccReq->virAddr, ptr_memAccReq->value,ptr_memAccReq->pid);
            break;
        case 'e':
        	ptr_memAccReq->reqType = REQUEST_EXECUTE;
        	ptr_memAccReq->virAddr = addr;
        	scanf(" %u",&(ptr_memAccReq->pid));
            printf("产生请求：\n地址：%lu\t类型：执行\tPID:%u\n", ptr_memAccReq->virAddr,ptr_memAccReq->pid);
            break;
        case 's'://随机产生请求
        	ptr_memAccReq->command=0;//不是命令
        	scanf(" %d",&num);
        	printf("将产生%d条随机请求\n",num);
        	for(i=1;i<=num;i++){
        		do_request(ptr_memAccReq);
        		writereq(ptr_memAccReq);	
        	}
        	printf("%d条随机请求产生完毕\n",num);
        	break;
        case 'x':
        	ptr_memAccReq->command=-2;
        	printf("#发送退出程序命令#");
        	break;
        case 'y'://发送y命令
        	ptr_memAccReq->command=-1;
        	printf("#发送打印页表命令#");
        	break;
        default:
        	printf("请求格式有误，请重新输入\n");
    }
    if(c=='x'||c=='y'){//将命令写入fifo文件
		writereq(ptr_memAccReq);
	}
 	if(c=='r'||c=='w'||c=='e'){//将单条请求写入fifo文件
    	writereq(ptr_memAccReq);
    }
    if(c=='x')
    	return -1;//退出本程序
    while(c=getchar()!='\n')//越过行尾回车
    	;
    return 0;
    
}