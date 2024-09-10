// 取消 OpenGL ，在程序结束前调用，释放渲染环境，设备环境以及最终窗口句柄。
void DisableOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( ghRC );
	ReleaseDC( ghWnd, ghDC );
}