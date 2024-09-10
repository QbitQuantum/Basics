		void PathGroup::renderCurve(const Color& c) {
			Renderer* g = ARK2D::getRenderer();

			float ptimer = getTimer();
			g->setDrawColor(c);
			setTimer(0.0f);
			updateCurrent();
			float px = getLocation()->getX(); //paths.at(0)->subpaths.at(0)->points.at(0)->getX();
			float py = getLocation()->getY();//paths.at(0)->subpaths.at(0)->points.at(0)->getY();
			float du = getDuration();
			for(float i = 0.05f; i <= du; i += 0.05f)
			{
				setTimer(i);
				updateCurrent();

				Vector2<float>* f = getLocation();
				g->drawLine(int(px), int(py), int(f->getX()), int(f->getY()));

				px = f->getX();
				py = f->getY();
			}
			setTimer(ptimer);
			updateCurrent();
		}