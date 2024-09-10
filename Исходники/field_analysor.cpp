//检查球是否被机器人捕捉
//通过半径判断
bool Simulator::RobotBallCollisionRadius(SimRobot &r, SimBall &b, double dt)
{
    static int iDribbleBy=-1;
    //球相对机器人坐标
    MyVector2d ball_rel  = b.pos - r.pos.p;
    //球相对机器人矢量旋转到X轴方向
    MyVector2d robot_ball = ball_rel.rotate(-r.pos.dir);
    //球在机器人内部
    //bool ball_in_front = (robot_ball.x > -20) &&
    //                  (fabs(robot_ball.y) < 60);
    //球在机器人前方
    //bool ball_on_front = ball_in_front && (robot_ball.x < 120);

    double dist = ball_rel.length();
    //计算球相对机器人方向与机器人正方向的角度差
    double da=anglemod(ball_rel.angle()-r.pos.dir);
    if(da>M_PI)
    {
        da-=M_2PI;
    }
    if(da<-M_PI)
    {
        da+=M_2PI;
    }

    //检查球与机器人是否碰撞
    if (dist > robotHalfSize + BALL_RADIUS)
    {
        return (false);
    }
    bool bBounce=false;

    //if(ball_on_front)
    if(fabs(da)<M_PI/4)
    {
        if (r.vcmd.kick_power)
        {
            long kick_power=labs(r.vcmd.kick_power);
            if(kick_power>giShootPowerMax)
            {
                kick_power=giShootPowerMax;
            }
            b.vel.set(DVAR(OMNIBOT_KICKER_SPEED)*kick_power*1.0/giShootPowerMax,0);
            b.vel=b.vel.rotate(r.pos.dir);
            printf("Kicked=%d\r\n",r.vcmd.kick_power);

            b.pos.set(OMNIBOT_RADIUS+BALL_RADIUS+10,0);
            b.pos=b.pos.rotate(r.pos.dir);
            b.pos+= r.pos.p;
            return true;
        }
        else
        {
            //计算球相对机器人速度
            MyVector2d brel = b.vel - r.vel.v;
            //计算相对速度在机器人正方向上投影
            MyVector2d n(1,0);
            n = n.rotate(r.pos.dir);
            MyVector2d p = n.perp();
            MyVector2d bdrib(dot(brel, n), dot(brel, p));

            MyVector2d bpos=b.pos-r.pos.p;
            double bposx=dot(bpos, n);
            double bposy=dot(bpos, p);
            if(bposx<OMNIBOT_RADIUS-5)
            {
                b.vel.set(0,0);
                if(r.vcmd.dribble_power>0)
                {
                    b.pos.set(OMNIBOT_RADIUS-18,0);
                }
                else
                {
                    b.pos.set(OMNIBOT_RADIUS-18,bposy);

                }
                b.pos=b.pos.rotate(r.pos.dir);
                b.pos+= r.pos.p;
                //iDribbleBy=r.id;
            }
            //else if(bposx<OMNIBOT_RADIUS-5)
            //{
            //	b.pos.set(OMNIBOT_RADIUS-18,0);
            //	b.pos=b.pos.rotate(r.pos.dir);
            //	b.pos+= r.pos.p;
            //}
            //if(r.vcmd.dribble_power>0 &&


            //if (bposx<OMNIBOT_RADIUS-5 && (bdrib.x < 0.001 || (r.vcmd.dribble_power>0) || iDribbleBy>=0) )
            //{
            //	//printf("Dribble!!!!... %4.3f,%4.3f\n",bdrib.x,bdrib.y);
            //	double dlimit;
            //	dlimit = DVAR(OMNIBOT_DRIB_CATCH_SPEED)*3;

            //	if (fabs(bdrib.x) < dlimit)
            //	{
            //		b.vel.x = 0;
            //	}
            //	else
            //	{
            //	//	b.vel.x *= DVAR(OMNIBOT_DRIB_BOUNCE_DECAY);
            //	}

            //	//b.vel = r.vel.v.rotate(r.pos.dir);
            //	//b.vel += r.vel.v;
            //	b.vel.set(0,0);
            //	b.pos.set(OMNIBOT_RADIUS-18,0);
            //	b.pos=b.pos.rotate(r.pos.dir);
            //	b.pos+= r.pos.p;
            //	iDribbleBy=r.id;
            //}
            //else
            //{
            //	iDribbleBy=-1;
            //}
            return true;
        }
    }
    else
    {
        iDribbleBy=-1;
        bBounce=true;
    }
    if(!bBounce)
    {
        return true;
    }
    /* last final catch all check to prevent screw ups */
    //如果机器人与球相撞，球被弹开到机器人半径加球半径的位置
    b.pos = r.pos.p + ball_rel.norm() * (robotHalfSize + BALL_RADIUS);
    b.vel=r.vel.v.rotate(r.pos.dir)-b.vel;

    b.pos = b.pos + b.vel*dt;

    /* find the closest point on teh line segment to our robot
   * center and check if it is close enough. If so we hit the ball
   */
    //  MyVector2d closest;
    //	dist = ball_seg.Distance(r.pos, closest);
    //	if (dist > robotHalfSize + BALL_RADIUS)
    //		return (false);

    /* TO DO: need to work this part out still */


    return (true);
}