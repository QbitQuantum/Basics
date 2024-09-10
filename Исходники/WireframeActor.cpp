	void WireframeActor::drawActor(Graphics2D& g,long gameTime,float x1, float y1,double scale)
	{
		if(relative)
		{
			if(visible)
			{
				g.setColor(color);
				if(filled)
				{
					g.fillRect((x1 - View::x),(y1 - View::y),(float)(width*scale),(float)(height*scale));
				}
				else
				{
					g.drawRect((x1 - View::x),(y1 - View::y),(float)(width*scale),(float)(height*scale));
				}
			}
		}
		else
		{
			if(visible)
			{
				g.setColor(color);
				if(filled)
				{
					g.fillRect((x1),(y1),(float)(width*scale),(float)(height*scale));
				}
				else
				{
					g.drawRect((x1),(y1),(float)(width*scale),(float)(height*scale));
				}
			}
	    }
	}