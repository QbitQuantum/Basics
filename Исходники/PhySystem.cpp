//<<<<<<<<<<<<<<<<<<<<<<<两球碰撞>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool Ball::isIntersect(Ball* ball, Vector3& n){
	double sqDist = SqDistPointBall(c, *ball);
	bool isHit = ((sqDist <=  (ball->radius+radius)*(ball->radius+radius)) ? true : false);
	if(isHit){
		n = c - ball->c;
		n.normalize();
		if(isCollinear(n, ball->speed) && isCollinear(n, speed)){//两速度向量与两球球心连线共线
			Vector3 u1, u2;
			u1 = speed - (1.0 + e) * ball->mass * (speed - ball->speed) / (mass + ball->mass);
			u2 = ball->speed + (1.0 + e) * mass * (speed - ball->speed) / (mass + ball->mass);
			speed = u1;
			ball->speed = u2;
		}
		else {//斜碰
			Vector3 vt1, vt2, vn1, vn2, ut1, ut2, un1, un2;	//切线速度，法线速度
			double cosine;							//余弦
			cosine = dot(speed, -n) / speed.length();
			vn1 = speed.length()*cosine*(-n);
			vt1 = speed - vn1;
			if (ball->speed.length() >0.001) {
				cosine = dot(ball->speed,n) / ball->speed.length();
				vn2 = ball->speed.length()*cosine*n;
				vt2 = ball->speed - vn2;
			}

			ut1 = vt1;
			ut2 = vt2;
			un1 = vn1 - (1.0 + e)*ball->mass*(vn1-vn2)/(mass+ball->mass);
			un2 = vn2 + (1.0 + e)*mass*(vn1-vn2)/(mass+ball->mass);

			speed = ut1 + un1;
			ball->speed = ut2 + un2;
		}
	}
	return false;
}