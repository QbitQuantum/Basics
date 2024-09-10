	void update(float dt, vector<Planet*>& planets, paramStruct& params)
	{
		if(charging && charge < MAXCHARGE) charge += dt * 1.5f;
		
		pars = params;
		
		if(jumpInert > .0f)
			jumpInert-=dt;
		if(jumpInert < .0f)
			jumpInert = .0f;
		
		if(turn != params.turn)
		{
			charging = false;
			charge = .0f;
		}
		
		turn = params.turn;
		
		pos += vel * dt;
		
		if(pos.x > getWindowWidth())
		{
			pos.x = pos.x-getWindowWidth();
		}
		
		if(pos.x < 0)
		{
			pos.x = getWindowWidth()+pos.x;
		}
		
		if(pos.y > getWindowHeight())
		{
			pos.y = pos.y-getWindowHeight();
		}
		
		if(pos.y < 0)
		{
			pos.y = getWindowHeight()+pos.y;
		}
		
		Planet* closest = planets[0];
		float dst = 999999999.0f;
		vector<Planet*>::iterator it;
		for(it = planets.begin(); it < planets.end(); it++)
		{
			Vec2f moonToPlanet = ((*it)->pos - pos);
			
			if(moonToPlanet.length() < dst)
			{
				closest = (*it);
				dst = moonToPlanet.length();
			}
				
			
		//	vel += moonToPlanet.normalized() * 1.0f * (*it)->radius * (*it)->radius * 3.14 / (math<float>::max(moonToPlanet.length() * moonToPlanet.length(), 80.0f));

		//	vel += moonToPlanet.normalized() * params.distFactor * moonToPlanet.length();//20000.0f/(math<float>::max(moonToPlanet.length(), 100.0f));
			
		//	vel += (-params.repulse)* moonToPlanet.normalized() / moonToPlanet.length();
		}
		
		nearest = closest;
		
		Vec2f moonToPlanet = closest->pos - pos;
		
		if(!closestPlanet && moonToPlanet.length() > closest->radius * 2.5f)
		{
			vel += moonToPlanet.normalized() * 36.5f * pars.speed *
					closest->radius * closest->radius * closest->radius * (2.0f/3.0f) * M_PI 
					/ (math<float>::max(moonToPlanet.length() * moonToPlanet.length(), 80.0f));
		}
		if(!jumpInert && !closestPlanet && moonToPlanet.length() < closest->radius * 1.7f && losing.size() == 0)
		{
			closestPlanet = closest;
			
		}
		if(closestPlanet && !jumpInert && losing.size() == 0)
		{
			Vec2f m2cp = (closestPlanet->pos - pos);
			
			Vec2f r = pos - closestPlanet->pos;
			r.normalize();
			r.rotate(M_PI/1.97f);
		  
			vel = r * 300.0f * pars.speed;
			
			if(m2cp.length() < closestPlanet->radius)
			{
				pos += -m2cp.normalized() * (5.0f + closestPlanet->radius - m2cp.length());
			}
		}
		
		//vel /= planets.size();
		
		//
//		Vec2f newpos = (pos + vel * dt);
//		for(it = planets.begin(); it < planets.end(); it++)
//		{
//			if(newpos.distance((*it)->pos) < (*it)->radius * 1.5f)
//				vel -= ((*it)->pos - pos);
//		}
		
		closest = 0;
		delete closest;
		
		// particles
		
		vector<Particle*>::iterator pit;
		for(pit = losing.begin(); pit < losing.end(); pit++)
		{
			(*pit)->update(dt);
			if((*pit)->time > (*pit)->lt)
				losing.erase(pit);
		}
	}