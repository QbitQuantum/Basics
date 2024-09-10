CStarfire::CStarfire(ObjectType object,int x,int y,
					 int xspeed,int yspeed) : CObject(object,x,y,xspeed,yspeed){

	timeCreated = Timer.time();
}