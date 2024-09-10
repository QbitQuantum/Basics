void drawSnake(int z)           //画出蛇身及头尾
{
   int i=0,j=0;
   if (snakeLength[0] < SNAKE_MIN_LEN)
      return;
   if(z==1)
   if (snakeLength[1] < SNAKE_MIN_LEN)
      return;
for(j=0;j<z+1;j++)
{
   setTextColor(myColors[BS_SHEAD+7*j]);
   gotoTextPos((MAP_BASE_X + mySnake[j][0].x)*2, MAP_BASE_Y + mySnake[j][0].y);
   printf(mySharps[BS_SHEAD]);
   setTextColor(myColors[BS_SBODY+7*j]);
   for (i = 1; i < snakeLength[j] - 1; i++)
   {
      gotoTextPos((MAP_BASE_X + mySnake[j][i].x)*2, MAP_BASE_Y + mySnake[j][i].y);
      printf(mySharps[BS_SBODY]);
   }
   setTextColor(myColors[BS_STAIL+7*j]);
   gotoTextPos((MAP_BASE_X + mySnake[j][snakeLength[j]-1].x)*2, MAP_BASE_Y + mySnake[j][snakeLength[j]-1].y);
   printf(mySharps[BS_STAIL]);
}
   return;
}