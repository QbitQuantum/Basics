int CEnemyFairy16::Run()
{
	const v = 2;
	if( count < 60 ) {
		x -= v;
	}
	else if( count < 240 ) {
		if( count%10 == 0) {
			CTamaNormal tama;
			tama.x = GetX();
			tama.y = GetY();
			tama.type = 13;
			tama.color = 0;
			tama.v = 1.0 + 0.3 * GetDifficult();

			CDanmakuHorizon d(&tama);
			d.w = 1;
			if( GetDifficult() == DIFF_LUNATIC) {
				d.n = 4;
				d.m = 4;
			}else {
				d.n = 1 * ( GetDifficult() + 1 );
				d.m = 1 * ( GetDifficult() + 1 );
			}
			double angle = Atan2( g_pPlayer->GetX() - GetX(), g_pPlayer->GetY() - GetY());
			d.offset = angle + 360/d.m/4;
			d.Fire();
			g_pMaterial->sndFire.Play(0);
		}
	}
	else{
		x += v;
	}
	return CEnemyBase::Run();
}