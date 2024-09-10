void SetColor(int color)//设置颜色
 {
     SetConsoleTextAttribute(hConsole, color);
//是API设置字体颜色和背景色的函数 格式：SetConsoleTextAttribute(句柄,颜色);
 }