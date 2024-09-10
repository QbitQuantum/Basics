EnemyShip1::EnemyShip1(int arrivalTime, float hp, float atkspd, float xpos, float ypos, float xvel, float yvel,PlayerShip* p) : EnemyShip(arrivalTime,hp,atkspd,xpos,ypos,xvel,yvel,46,46,p)
{
	rec = Rectf( Vec2f(pos.x-width/2,pos.y-height/2), Vec2f(pos.x+width/2,pos.y+height/2));
	bulletType = 1;
}