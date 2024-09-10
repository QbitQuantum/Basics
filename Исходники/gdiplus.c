LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (uMsg)
    {

        case WM_PAINT:
            
            
            hdc = BeginPaint(hwnd, &ps);

            int graphics;
            GdipCreateFromHDC(hdc, &graphics);//创建Graphics对象
            GdipCreatePen1(0x60FF2015, 1, 2, &pen);//创建画笔
            GdipDrawRectangle(graphics, pen, 20, 20, 120, 120);//画矩形
            GdipDrawLine(graphics, pen, 50, 60, 170, 340);//画直线

            GdipDeletePen(pen);//销毁画笔
            GdipDeleteGraphics(graphics);//销毁Graphics对象

            EndPaint(hwnd, &ps);
            return 0;//告诉系统，WM_PAINT消息我已经处理了，你那儿凉快哪儿玩去吧。
        case WM_CREATE:
            break;
        case WM_DESTROY://窗口已经销毁
            PostQuitMessage(0);//退出消息循环，结束应用程序
            return 0;
            break;
        case WM_LBUTTONDOWN://鼠标左键按下
                            //让无边框窗口能够拖动(在窗口客户区拖动)
            PostMessage(hwnd, WM_SYSCOMMAND, 61458, 0);
            break;
            /*case WM_MOUSEMOVE://鼠标移动
            int xPos, yPos;
            xPos = GET_X_LPARAM(lParam);//鼠标位置X坐标
            yPos = GET_Y_LPARAM(lParam);//鼠标位置Y坐标
            //不要用LOWORD和HIWORD获取坐标，因为坐标有可能是负的
            break;*/
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);//其他消息交给系统处理
}