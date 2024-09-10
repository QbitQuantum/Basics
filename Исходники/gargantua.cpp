//=========================================================
// RunTask
//=========================================================
void CGargantua::RunTask( Task_t *pTask )
{
	switch ( pTask->iTask )
	{
	case TASK_DIE:
		if ( gpGlobals->time > m_flWaitFinished )
		{
			pev->renderfx = kRenderFxExplode;
			pev->rendercolor.x = 255;
			pev->rendercolor.y = 0;
			pev->rendercolor.z = 0;
			StopAnimation();
			pev->nextthink = gpGlobals->time + 0.15;
			SetThink( SUB_Remove );
			int i;
			int parts = MODEL_FRAMES( gGargGibModel );
			for ( i = 0; i < 10; i++ )
			{
				CGib *pGib = GetClassPtr( (CGib *)NULL );

				pGib->Spawn( GARG_GIB_MODEL );
				
				int bodyPart = 0;
				if ( parts > 1 )
					bodyPart = RANDOM_LONG( 0, pev->body-1 );

				pGib->pev->body = bodyPart;
				pGib->m_bloodColor = BLOOD_COLOR_YELLOW;
				pGib->m_material = matNone;
				pGib->SetAbsOrigin( GetAbsOrigin() );
				pGib->SetAbsVelocity( UTIL_RandomBloodVector() * RANDOM_FLOAT( 300, 500 ));
				pGib->SetNextThink( 1.25 );
				pGib->SetThink( SUB_FadeOut );
			}

			Vector vecOrigin = GetAbsOrigin();

			MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, vecOrigin );
				WRITE_BYTE( TE_BREAKMODEL);

				// position
				WRITE_COORD( vecOrigin.x );
				WRITE_COORD( vecOrigin.y );
				WRITE_COORD( vecOrigin.z );

				// size
				WRITE_COORD( 200 );
				WRITE_COORD( 200 );
				WRITE_COORD( 128 );

				// velocity
				WRITE_COORD( 0 ); 
				WRITE_COORD( 0 );
				WRITE_COORD( 0 );

				// randomization
				WRITE_BYTE( 200 ); 

				// Model
				WRITE_SHORT( gGargGibModel );	//model id#

				// # of shards
				WRITE_BYTE( 50 );

				// duration
				WRITE_BYTE( 20 );// 3.0 seconds

				// flags

				WRITE_BYTE( BREAK_FLESH );
			MESSAGE_END();

			return;
		}
		else
			CBaseMonster::RunTask(pTask);
		break;

	case TASK_FLAME_SWEEP:
		if ( gpGlobals->time > m_flWaitFinished )
		{
			FlameDestroy();
			TaskComplete();
			FlameControls( 0, 0 );
			SetBoneController( 0, 0 );
			SetBoneController( 1, 0 );
		}
		else
		{
			BOOL cancel = FALSE;

			Vector angles = g_vecZero;

			FlameUpdate();
			CBaseEntity *pEnemy = m_hEnemy;
			if ( pEnemy )
			{
				Vector org = GetAbsOrigin();
				org.z += 64;
				Vector dir = pEnemy->BodyTarget(org) - org;
				angles = UTIL_VecToAngles( dir );
				angles.y -= GetAbsAngles().y;
				if ( dir.Length() > 400 )
					cancel = TRUE;
			}
			if ( fabs(angles.y) > 60 )
				cancel = TRUE;
			
			if ( cancel )
			{
				m_flWaitFinished -= 0.5;
				m_flameTime -= 0.5;
			}
			// FlameControls( angles.x + 2 * sin(gpGlobals->time*8), angles.y + 28 * sin(gpGlobals->time*8.5) );
			FlameControls( angles.x, angles.y );
		}
		break;

	default:
		CBaseMonster::RunTask( pTask );
		break;
	}
}