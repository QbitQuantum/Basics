void Mouse(int button, int state, int cursorX, int cursorY)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf("%d, %d\n", cursorX, cursorY);
        float x = 0, y = 0;
        coorTrans(cursorX, cursorY, x, y);
        if(DISTANCE(x, y, cx, cy) < r)
        {
            selected = !selected;
            DrawCircle();
        }
    }
}