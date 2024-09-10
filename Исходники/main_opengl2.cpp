int main(int argc, char* argv[])
{


#ifdef __APPLE__
	MacOpenGLWindow* window = new MacOpenGLWindow();
#else
	Win32OpenGLWindow* window = new Win32OpenGLWindow();
#endif
	btgWindowConstructionInfo wci(g_OpenGLWidth,g_OpenGLHeight);
	wci.m_openglVersion = 2;	
	window->createWindow(wci);
	window->setWindowTitle("MyTest");
#ifdef _WIN32
	glewInit();
#endif

    
	window->startRendering();
	float color[4] = {1,1,1,1};
//	prim.drawRect(0,0,200,200,color);
	
    
	
	window->endRendering();

    
	
	window->setKeyboardCallback(MyKeyboardCallback);


	{
		BasicDemo* demo = new BasicDemo;
		demo->myinit();
		demo->initPhysics();
		
		do
		{
			window->startRendering();
			demo->clientMoveAndDisplay();

			render.init();
			render.renderPhysicsWorld(demo->getDynamicsWorld());
			window->endRendering();
		} while (!window->requestedExit());

		demo->exitPhysics();
		delete demo;
	}


	window->closeWindow();
	delete window;

	return 0;
}