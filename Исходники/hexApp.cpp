	void update(float dt)
	{
		Vec2f newpos = pos + vel;
		
		if(insidePolygon(newpos - tile->pos, (*tile->hex)))
		{
			pos = newpos;
			
		}
		else 
		{
			Vec2f newpos2 = pos + vel * 15.0f;
			
			Vec2f exitdir = newpos2 - tile->pos;
			
			bool wander = false;
			vector<Tile*>::iterator tileit;
			
			int idx = Tile::getIndexForAngle(math<float>::atan2(exitdir.x, exitdir.y));
			console() << idx << endl;
			
			for(tileit = tiles->begin(); tileit < tiles->end(); tileit++)
			{
				if(insidePolygon(newpos2 - (*tileit)->pos, *(*tileit)->hex) &&
				   tile->connections[idx] &&
				   !tile->state[idx] &&
				   !(*tileit)->state[(idx+3) % 6])
				{
					pos = newpos;
					wander = true;
					tile = tile->connections[idx];
				}
			}

			if(!wander)
			{
				Rand r;
				vel = Vec2f(rand->nextFloat(-PSPEED, PSPEED), rand->nextFloat(-PSPEED, PSPEED));
			}
		}
		
		
		expired += dt;
	}