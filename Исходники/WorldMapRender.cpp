	void onUpdate(float dt)
	{
		Quad::onUpdate(dt);

		Vector sz = parent->scale;

		if (sz.x < zoomMin)
			sz.x = sz.y = zoomMin;
		if (sz.x > zoomMax)
			sz.x = sz.y = zoomMax;
		
		if (sz.x > 1.0f)
		{
			scale.x = (1.0f/sz.x);
			scale.y = (1.0f/sz.y);
		}
		else
		{
			scale = Vector(1,1);
		}

		Vector wp = getWorldPosition();

		if (blink)
		{
			blinkTimer += dt;
			if (blinkTimer > blinkPeriod)
			{
				if (alphaMod == 0)
					alphaMod = 1;
				else
					alphaMod = 0;

				blinkTimer = 0;
			}
		}

		if (canMove)
		{
			if (mover == 0)
			{
				if (core->mouse.buttons.left && (core->mouse.position - wp).isLength2DIn(GEM_GRAB))
				{
					core->sound->playSfx("Gem-Move");
					mover = this;
					//offset = Vector(position - core->mouse.position);
					//position += core->mouse.position - wp;
					//offset = Vector(0, 4);
				}
			}
			else if (mover == this)
			{
				//position = core->mouse.position;
				position += (core->mouse.position - wp)/parent->scale.x;
				if (!core->mouse.buttons.left)
				{
					mover = 0;
					core->sound->playSfx("Gem-Place");
					//position += offset;
					//offset = Vector(0,0);
					//offset = Vector(0,0);
					gemData->pos = position;
				}
			}
		}


		if (textBG)
		{
			textBG->position = getWorldPosition() + Vector(0, -20);
		}

		if ((core->mouse.position - wp).isLength2DIn(GEM_GRAB))
		{
			//text->alpha.interpolateTo(1, 0.1);
			/*
			if (!gemData->userString.empty())
			textBG->alpha.interpolateTo(1, 0.1);
			*/
			if (!gemData->userString.empty())
				textBG->show();
		}
		else
		{
			/*
			text->alpha.interpolateTo(0, 0.1);
			textBG->alpha.interpolateTo(0, 0.1);
			*/
			if (textBG->alpha == 1)
				textBG->hide();
		}
	}