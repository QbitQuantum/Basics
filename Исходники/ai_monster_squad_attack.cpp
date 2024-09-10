Fvector   CMonsterSquad::calc_monster_target_dir (CBaseMonster* monster, const CEntity* enemy)
{
	VERIFY(monster);
	VERIFY(enemy);

	const Fvector enemy_pos = enemy->Position();
	Fvector home2enemy = enemy_pos;
	home2enemy.sub(monster->Home->get_home_point());

	const float home2enemy_mag = home2enemy.magnitude();

	// enemy pos == home pos?
	const float near_zero = 0.00001f;
	if ( home2enemy_mag < near_zero )
	{
		Fvector enemy2monster = monster->Position();
		enemy2monster.sub(enemy_pos);
		const float enemy2monster_mag = enemy2monster.magnitude();
		// monster pos == enemy pos?
		if ( enemy2monster_mag < near_zero )
		{
			VERIFY2(false, "Enemy and Monster should not have same pos!");
			Fvector dir = { 1.f, 0.f, 0.f }; // happy with random dir then :)
			return dir;
		}

		enemy2monster.normalize();
		return enemy2monster;
	}

	const u8 squad_size  = squad_alife_count();
	VERIFY(squad_size);

	u8 squad_index = get_index(monster);
	if ( squad_index == -1 )
	{
		squad_index = 0;
	}

	float heading, pitch;
	home2enemy.getHP(heading, pitch);

	// 2pi * index/num - encircle
	heading += M_PI * 2.f * squad_index / squad_size;
	heading = angle_normalize(heading);

	Fvector dir;
	dir.setHP(heading, pitch);
	dir.normalize();

	return dir;
}