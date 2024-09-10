// 菜单
int Menu(char *cmd, LinkList head)
{
    
    // 进入到程序主循环
    while(1) {
        
        // 打印帮助信息
        PrintHelp();

        // 输入操作命令
        *cmd = getchar();
        printf("cmd = %c\n", *cmd);
        
        // 清空标准输入缓存
        setbuf(stdin, NULL);
        
        // 清空屏幕
        system("clear");
        
        // 列出所有联系人 
        List(head);
        
        // 根据输入操作
        switch (*cmd) {
            
            // 查询联系人
            case '1': 
                Search(head); 
                break;
            
            // 添加联系人并保存到文件
            case '2': 
                New(head); 
                Save(head); 
                break;
            
            // 更新联系人并保存到文件
            case '3': 
                Update(head); 
                Save(head);
                break;
            
            // 删除联系人并保存到文件
            case '4': 
                Remove(head);
                Save(head);
                break;
            
            // 退出系统
            case '5':
                exit(0);
            
            
            default : 
                printf("Input Error. Try Again\n");
                continue;
        }
        
        getchar();
    
    }

	return 0;
}