		/**
		 * Method is used to initialize and configure engine context.
		 */
		void ContextManager::initializeContextManager()
		{
			initializeContext();
			resizeWindow(resolutionWidth, resolutionHeight);
			initializeOpenGL();

			contextWindow->setActive();
			sf::Mouse::setPosition(sf::Vector2i(resolutionWidth/2,resolutionHeight/2),*contextWindow);
			contextWindow->setMouseCursorVisible(false);
		}