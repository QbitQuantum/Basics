		// start the draw loop
		void start()
		{
			printf("starting app\n");
			while (!mWindow.shouldClose() )
			{
				mWindow.setViewport();

				//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				onDraw();

				mWindow.swapBuffers();
				glfwPollEvents();
			}
		}