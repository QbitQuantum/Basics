bool NETHER::RobotCollision(ROBOT *r,bool complete)
{
	int i;
	List<BUILDING> l;
	BUILDING *b;
	List<ROBOT> l2;
	ROBOT *rt;
	float m1[16]={1,0,0,0,
				  0,1,0,0,
				  0,0,1,0,
				  r->pos.x,r->pos.y,r->pos.z,1};
	float m2[16]={1,0,0,0,
				  0,1,0,0,
				  0,0,1,0,
				  0,0,0,1}; 

	/* Collision with the ship: */ 
	{
		float m2[16]={1,0,0,0,
				 	  0,1,0,0,
					  0,0,1,0,
					  shipp.x,shipp.y,shipp.z,1}; 
		if (r->cmc.collision_simple(m1,&(ship->cmc),m2)) return true;
	}

	if (!complete) return false;

	/* Collision with buildings: */  
	l.Instance(buildings);
	l.Rewind();
	while(l.Iterate(b)) {
		if (((b->pos.x-r->pos.x)*(b->pos.x-r->pos.x)+
			 (b->pos.y-r->pos.y)*(b->pos.y-r->pos.y)+
			 (b->pos.z-r->pos.z)*(b->pos.z-r->pos.z))<COLISION_TEST_THRESHOLD) {
			m2[12]=b->pos.x;
			m2[13]=b->pos.y;
			m2[14]=b->pos.z;

			switch(b->type) {
				case B_FENCE:
					if (r->cmc.collision_simple(m1,&(building_tile[5]->cmc),m2)) return true;
					break;
				case B_WALL1:
					if (r->cmc.collision_simple(m1,&(building_tile[0]->cmc),m2)) return true;
					break;
				case B_WALL2:
					if (r->cmc.collision_simple(m1,&(building_tile[1]->cmc),m2)) return true;
					break;
				case B_WALL3:
					if (r->cmc.collision_simple(m1,&(building_tile[2]->cmc),m2)) return true;
					break;
				case B_WALL4:
					if (r->cmc.collision_simple(m1,&(building_tile[3]->cmc),m2)) return true;
					break;
				case B_WALL5:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					break;
				case B_WALL6:
					if (r->cmc.collision_simple(m1,&(building_tile[7]->cmc),m2)) return true;
					break;
				case B_WARBASE:
					if (r->cmc.collision_simple(m1,&(building_tile[8]->cmc),m2)) return true;
					//m2[13]=b->pos.y-2;
					//m2[14]=b->pos.z+1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			case B_FACTORY_ELECTRONICS:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					m2[12]=b->pos.x+0.5;
					m2[13]=b->pos.y+0.5;
					m2[14]=b->pos.z+1;
					if (r->cmc.collision_simple(m1,&(piece_tile[0][7]->cmc),m2)) return true;
					//m2[12]=b->pos.x;
					//m2[13]=b->pos.y-1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			case B_FACTORY_NUCLEAR:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					m2[12]=b->pos.x+0.5;
					m2[13]=b->pos.y+0.5;
					m2[14]=b->pos.z+1;
					if (r->cmc.collision_simple(m1,&(piece_tile[0][6]->cmc),m2)) return true;
					//m2[12]=b->pos.x;
					//m2[13]=b->pos.y-1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			case B_FACTORY_PHASERS:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					m2[12]=b->pos.x+0.5;
					m2[13]=b->pos.y+0.5;
					m2[14]=b->pos.z+1;
					if (r->cmc.collision_simple(m1,&(piece_tile[0][5]->cmc),m2)) return true;
					//m2[12]=b->pos.x;
					//m2[13]=b->pos.y-1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			case B_FACTORY_MISSILES:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					m2[12]=b->pos.x+0.5;
					m2[13]=b->pos.y+0.5;
					m2[14]=b->pos.z+1;
					if (r->cmc.collision_simple(m1,&(piece_tile[0][4]->cmc),m2)) return true;
					//m2[12]=b->pos.x;
					//m2[13]=b->pos.y-1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			case B_FACTORY_CANNONS:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					m2[12]=b->pos.x+0.5;
					m2[13]=b->pos.y+0.5;
					m2[14]=b->pos.z+1;
					if (r->cmc.collision_simple(m1,&(piece_tile[0][3]->cmc),m2)) return true;
					//m2[12]=b->pos.x;
					//m2[13]=b->pos.y-1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			case B_FACTORY_CHASSIS:
					if (r->cmc.collision_simple(m1,&(building_tile[4]->cmc),m2)) return true;
					m2[12]=b->pos.x+0.5;
					m2[13]=b->pos.y+0.5;
					m2[14]=b->pos.z+1;
					if (r->cmc.collision_simple(m1,&(piece_tile[0][1]->cmc),m2)) return true;
					//m2[12]=b->pos.x;
					//m2[13]=b->pos.y-1;
					//if (b->owner!=0) if (r->cmc.collision_simple(m1,&(building_tile[6]->cmc),m2)) return true;
					break;
			} /* switch */ 
			} /* if */ 
	} /* while */ 

	/* Collision with the robots: */ 
	for(i=0;i<2;i++) {
		l2.Instance(robots[i]);
		l2.Rewind();
		while(l2.Iterate(rt)) {
			if (((rt->pos.x-r->pos.x)*(rt->pos.x-r->pos.x)+
				 (rt->pos.y-r->pos.y)*(rt->pos.y-r->pos.y)+
				 (rt->pos.z-r->pos.z)*(rt->pos.z-r->pos.z))<COLISION_TEST_THRESHOLD) {
				if (rt!=r) {
					m2[12]=rt->pos.x;
					m2[13]=rt->pos.y;
					m2[14]=rt->pos.z; 
					if (r->cmc.collision_simple(m1,&(rt->cmc),m2)) return true;
				} /* if */ 
			} /* if */ 
		} /* while */ 
	} /* while */ 

	return false;
} /* NETHER::RobotCollision */ 