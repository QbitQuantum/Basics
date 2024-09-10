	void SceneDisplayerWidget::paintGL()
	{
		if(sceneDisplayer!=nullptr)
		{
			sceneDisplayer->paint();
		}else
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.1f, 0.05f, 0.1f, 1.0f);
		}

		swapBuffers();
		update();
	}