void fir(int x,int y,int h, int c1) // ѕроцедура рисовани¤ елочки 
//ѕараметры: x,y Ц координаты вершины h Ц высота; st Ц стиль закраски c1 - цвет линий и закраски
{
    int a = int((h*2/sqrt(3)));
    triangle(x, y, h, c1);
    triangle(x, y+h, h, c1);
    triangle(x, y+2*h, h, c1);

    setcolor(BROWN);
    setfillstyle(1, BROWN);
    moveto(x+a/2-5, y+2*h);
    lineto(x+a/2-5, y+h+2*h);
    lineto(x+a/2+5, y+h+2*h);
    lineto(x+a/2+5, y+2*h);
    lineto(x+a/2-5, y+2*h);
    floodfill(x+a/2-5+1, y+2*h+1, BROWN);
}