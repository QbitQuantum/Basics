/**
* player 以确定得姿势（指倒着跑和正跑），跑到 target 所需要的周期数
* This function returns the minimum cycles for a player to go to a target position with 
* a certain posture, forward or backward.
* @param player the player to caculate.
* @param target the target position to go to.
* @param inverse true means running backwards.
* @param buffer 
* @return an integer to show the minimum cycles caculated.
*/
int Dasher::CycleNeedToPointWithCertainPosture(const PlayerState & player, Vector target, const bool inverse, double *buf)
{
	int cycle = 0; //用的周期

	const double & decay = player.GetPlayerDecay();
	const double & speedmax = player.GetEffectiveSpeedMax();
	const double & stamina = player.GetStamina();
	const double & stamina_inc_max = player.GetStaminaIncMax();
	const double & dash_max = ServerParam::instance().maxDashPower();
	const Vector & pos = player.GetPos();
	const Vector & vel = player.GetVel();

	const double accrate = player.GetDashPowerRate() * player.GetEffort();
	double speed = vel.Mod();

	const Vector predict_pos_1 = pos + vel;
	const Vector predict_pos_2 = predict_pos_1 + vel * decay;
	const double dir = (target - pos).Dir();
	double dis = (target - predict_pos_1).Mod();

	const double kick_area = player.IsGoalie()? ServerParam::instance().catchAreaLength(): (player.GetKickableArea() - GETBALL_BUFFER);

	if (dis <= kick_area){
		dis = pos.Dist(target);
		if (buf) *buf = 0;
		return 1;
	}

	double facing;
	if (player.IsBodyDirValid()) {
		facing = player.GetBodyDir();
	}
	else if (speed > 0.26){
		facing = vel.Dir();
	}
	else {
		facing = dir; //认为不用转身
	}

	double diffang = fabs(GetNormalizeAngleDeg(dir - facing));
	const double oneturnang = player.GetMaxTurnAngle();
	const double stamina_recovery_thr = ServerParam::instance().recoverDecThr() * ServerParam::instance().staminaMax();

	double angbuf = FLOAT_EPS;
	angbuf = ASin(kick_area / dis);
	angbuf = Max(angbuf , 15.0);

	if (inverse) {
		diffang = 180.0 - diffang;
		facing = GetNormalizeAngleDeg(180.0 + facing);
	}

	//I 调整阶段
	if(diffang <= angbuf){ //不需要转身
		target = (target - pos).Rotate(-facing);
		dis = fabs(target.X());
		double y = fabs(target.Y());
		if(y < kick_area){
			dis -= sqrt(kick_area * kick_area - y * y);
		}
		speed *= Cos(vel.Dir() - facing); //身体方向上的投影
	}
	else if(diffang <= oneturnang){
		cycle += 1;
		target -= predict_pos_1;
		speed *= Cos(vel.Dir() - dir); //取得目标方向的投影
		speed *= decay;//进行投影.垂直方向1个周期后衰减到10+厘米了,并且在1turn时可加入考虑修正掉
		dis = target.Mod();
		dis -= kick_area;
	}
	else{ //认为转身两下（不细致）
		cycle += 2;
		target -= predict_pos_2;
		speed *= Cos(vel.Dir() - dir); //取得目标方向的投影
		speed *= decay * decay;//进行投影.垂直方向1个周期后衰减到10+厘米了,并且在1turn时可加入考虑修正掉
		dis = target.Mod();
		dis -= kick_area;
	}

	if (dis <= 0){
		if(buf != NULL){
			*buf = -dis / ( speed / decay);
			*buf = Min(*buf , 0.99);
		}
		return Max(cycle, 0);
	}

	//II 加速 & 消耗体力阶段
	const double stamina_used_per_cycle = inverse? dash_max * 2.0: dash_max;
	const int full_cyc = int((stamina - stamina_recovery_thr) / (stamina_used_per_cycle - stamina_inc_max)); //满体力阶段
	int acc_cyc = 0;//加速阶段
	const double speedmax_thr = speedmax * decay * 0.98;
	const double accmax = accrate * dash_max;

	while(acc_cyc < full_cyc && speed < speedmax_thr){
		speed += accmax;
		if(speed > speedmax){
			speed = speedmax;
		}
		dis -= speed;
		if(dis <= 0){//还没加速到最大就跑到了...
			cycle += acc_cyc + 1;
			if(buf != NULL){
				*buf = -dis /( speed / decay );
				*buf = Min(*buf , 0.99);
			}
			return Max(cycle, 0);
		}
		speed *= decay;
		++ acc_cyc;
	}

	cycle += acc_cyc;

	//III 满体匀速阶段
	int aver_cyc = full_cyc - acc_cyc;
	double aver_cyc_dis = aver_cyc * speedmax;
	if(aver_cyc_dis >= dis){
		if(buf != NULL){
			double realcyc = cycle + dis / speedmax;
			cycle = int( ceil(realcyc) );
			*buf = cycle - realcyc;
			return Max(cycle, 0);

		}
		else{
			cycle = int(ceil( cycle + dis / speedmax));
			return Max(cycle, 0);
		}
	}
	else{
		cycle += aver_cyc;
		dis -= aver_cyc_dis;
	}

	//IV 没体(0消耗)减速阶段
	double acc_tired = stamina_inc_max * accrate;
	double speed_tired = acc_tired / (1 - decay);
	double speed_tired_thr = speed_tired * decay;
	speed *= decay;
	while(dis > 0 && fabs(speed - speed_tired_thr) > 0.004){
		speed += acc_tired;
		dis -= speed;
		speed *= decay;
		++cycle;
	}

	if(dis <= 0){
		if(buf != NULL){
			*buf = -dis / ( speed / decay);
			*buf = Min(*buf , 0.99);
		}
		return Max(cycle, 0);
	}

	//V 没体(0消耗)匀速阶段

    if( buf != NULL){
        double realcyc = cycle + dis / speed_tired;
        cycle = int( ceil( realcyc ) );
        *buf = cycle - realcyc;
        return Max(cycle, 0);
    }
    else{
    	cycle = cycle + int(ceil ( dis / speed_tired));
    	return Max(cycle, 0);
    }
}