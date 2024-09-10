bool CElevatorState::GetControlDir(Fvector& dir)
{
	bool ret=true;
	VERIFY(m_ladder&&m_character);
	Fvector d;
	float dist;
	switch(m_state)
	{
	case	clbDepart		: 
	case	clbNoLadder		:
	case	clbNone			: 		break;			
	case 	clbNearUp		:		dist= m_ladder->DDUpperP(m_character,d);
									if(	dXZDotNormalized(d,m_character->CamDir())>look_angle_cosine&&
										!fis_zero(dist,EPS_L)&&m_character->ControlAccel().dotproduct(d)>0.f) dir.set(d);
									break;						
	case 	clbNearDown		:		
									dist=m_ladder->DDLowerP(m_character,d);
									if(dXZDotNormalized(d,m_character->CamDir())>look_angle_cosine&&
									   !fis_zero(dist,EPS_L)&&m_character->ControlAccel().dotproduct(d)>0.f) dir.set(d);
									break;					
	case 	clbClimbingUp	:		m_ladder->DDAxis(dir);
									m_ladder->DDToAxis(m_character,d);
									dir.add(d);dir.normalize();
									break;					
	case 	clbClimbingDown	:		m_ladder->DDToAxis(m_character,d);
									if(m_ladder->BeforeLadder(m_character)||d.dotproduct(dir)>0.f)
									{
										m_ladder->DDAxis(dir);
										dir.invert();
										dir.add(d);dir.normalize();
									}
									else 
									{
#ifdef DEBUG
										if(ph_dbg_draw_mask.test(phDbgLadder))
										{
											Msg("no c dir");
										}
#endif
										ret=false;
									}
									break;				
	}
	return ret;
}