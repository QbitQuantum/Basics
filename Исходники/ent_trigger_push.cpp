void EntTriggerPush::Touch(Entity &other)
{
//	Player	*player;
	float				height, time, dist;
	std::stringstream	sstr;

	if(!target)
		return;

	Vector3f	v = target->GetOrigin() - other.GetOrigin();

	height = v[1];
	time = (float)sqrt(height / (G_GRAVITY * 0.5));

	v[1] = 0;

	dist = v.length();
	v.normalize();
	v *= dist / time;
	v[1] = time * G_GRAVITY;

	sstr << "push" << " " << v[0] << " " << v[1] << " " << v[2];

	if(other.GetClassName() == "player")
	{
//		logstream() << "TOUCH: " << other.GetOrigin()[0] << " " << other.GetOrigin()[1] << " " << other.GetOrigin()[2] << "\n";
		EE.ThrowEvent_i(&other, sstr.str(), 0);

		//play sound
		EE.C_ExecCommand("s_play basehaste/sound/world/jumppad.wav");
	}
}