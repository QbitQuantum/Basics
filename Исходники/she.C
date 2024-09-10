void Play(void)/*游戏实现过程*/
{
   srand((unsigned long)time(0));
   food.flag=1;/*1表示需出现新食物,0表示食物已存在*/
   snake.life=0;/*标志贪吃蛇活着*/
   snake.dir=1;/*方向向右*/
   snake.x[0]=300;snake.y[0]=240;/*定位蛇头初始位置*/
   snake.x[1]=300;snake.y[1]=240;
   snake.node=2;/*贪食蛇节数*/
   do
   {
      while(!kbhit())/*在没有按键的情况下,蛇自己移动身体*/
      {
	 if(food.flag==1)/*需要出现新食物*/
	 do
	 {
	     food.x=rand()%520+60;
	     food.y=rand()%370+60;
		food.flag=0;/*标志已有食物*/
	 }while(food.x%10!=0||food.y%10!=0);
	 if(food.flag==0)/*画出食物*/
	 {
              setcolor(GREEN);
	      setlinestyle(3,0,3);
              rectangle(food.x,food.y,food.x+10,food.y+10);
	 }
         for(i=snake.node-1;i>0;i--)/*实现蛇向前移动*/
         {
            snake.x[i]=snake.x[i-1];
	    snake.y[i]=snake.y[i-1];
	 }
      
	 switch(snake.dir)
	 {
	    case 1:snake.x[0]+=10;break;/*向右移*/
	    case 2: snake.x[0]-=10;break;/*向左移*/
	    case 3: snake.y[0]-=10;break;/*向上移*/
	    case 4: snake.y[0]+=10;break;/*向下移*/
	 }
	 for(i=3;i<snake.node;i++)
	 {
	    if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0])/*判断蛇是否吃到自己*/
	    {
               GameOver();/*游戏结束*/
               snake.life=1;/*蛇死*/
               break;
	    }
        }
	if(snake.x[0]<60||snake.x[0]>590||snake.y[0]<50||
	   snake.y[0]>440)/*蛇是否撞到墙壁*/
	{
	    GameOver();/*游戏结束*/
	    snake.life=1; /*蛇死*/
	    break;
	}
	if(snake.x[0]==food.x&&snake.y[0]==food.y)/*判断是否吃到食物*/
	{
           setcolor(0);/*用背景色遮盖调食物*/
           rectangle(food.x,food.y,food.x+10,food.y+10);
	   snake.node++;/*蛇的身体长一节*/
	   food.flag=1;/*需要出现新的食物*/
	}
	setcolor(4);/*画蛇*/
	for(i=0;i<snake.node;i++)
	 {     setlinestyle(0,0,1);
	   rectangle(snake.x[i],snake.y[i],snake.x[i]+10,
	       snake.y[i]+10);
	       }
	delay(speed);
	setcolor(0);/*用背景色遮盖蛇的的最后一节*/
	rectangle(snake.x[snake.node-1],snake.y[snake.node-1],
	snake.x[snake.node-1]+10,snake.y[snake.node-1]+10);
     }  /*endwhile（！kbhit）*/
    if(snake.life==1)/*如果蛇死就跳出循环*/
        break;
    key=bioskey(0);/*接收按键*/
       if(key==UP&&snake.dir!=4)/*判断是否往相反的方向移动*/
	  snake.dir=3;
       else
	 if(key==DOWN&&snake.dir!=3)/*判断是否往相反的方向移动*/
		   snake.dir=4;
	  else
	      if(key==RIGHT&&snake.dir!=2)/*判断是否往相反的方向移动*/
	     snake.dir=1;
	     else
	if(key==LEFT&&snake.dir!=1)/*判断是否往相反的方向移动*/
		snake.dir=2;
   }while(key!=ESC);/*ESC键退出游戏*/
}