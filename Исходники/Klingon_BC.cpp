void TKlingonBC::Do_ai()
{
	// Destruction rules
	if (m_lstHealth[HLT_HULL]<=0)
	{
		Explode();
	}
	else
	{

		double tsx,tsy;
        m_blPhaserOn = false;
        if (m_lstHealth[HLT_SENSOR]<30)
		{
			m_pTarget=NULL;
		}
		else
		{
			if ((m_nTask==TSK_CONTACT)||(m_nTask==TSK_STRIKE))
			{
				m_pTarget=(TShip *) m_pEngine->Seek(ID_PLAYER,m_dViewDistance,m_dX,m_dY);
			}
			else
			{
				m_pTarget = (TShip *) m_pEngine->Seek(MEM_KLINGON,true,m_dViewDistance,m_dX,m_dY);
			}

			if ((m_pTarget!=NULL)&&(m_pTarget->m_blDestroyed)) m_pTarget=NULL;
		}

        if (((m_pTarget!=NULL)&&((m_pTarget->m_blDestroyed)||(m_pTarget->m_CloakState == CS_CLOAKED)))||(m_lstHealth[HLT_SENSOR]<30)||(m_lstHealth[HLT_COMPUTER]<30)) m_pTarget=NULL;

		if ((m_pTarget==NULL)||(m_pTarget->m_blDocked==true))
		{
			if ((m_AI==AI_CHASE)||(m_AI==AI_EVADE))
			{
				m_AI=AI_WANDER;
			}
	   }
	   else
	   {
			m_dTargetDistance = Distance(m_dX,m_dY,m_pTarget->GetX(),m_pTarget->GetY());
			if (m_AI==AI_WANDER) m_AI=AI_CHASE;

            if (m_nTask==TSK_STANDARD)
			{
				if ((m_lstHealth[HLT_PHOTON]<50)&&(m_lstHealth[HLT_PHASER]<=20)) m_AI=AI_EVADE;
            }
   }

if ((m_lstHealth[HLT_PHOTON]<40)||(m_nTorpedoes==0))
   {
	  if (! TryEnterDocking())
      {
          m_AI=AI_EVADE;
      }
   }
   else if (m_pTarget==NULL)
   {
       bool blShouldDock = false;
       for (size_t i=0;i<m_lstHealth.size();i++)
       {
           if (m_lstHealth[i] < (m_nMaxHealth-50)) blShouldDock = true;
           if (m_nTorpedoes<50) blShouldDock = true;
       }
       if (blShouldDock)
       {
           if(! TryEnterDocking())
           {
                 m_dWaypointX=rand() % SECTORSIZE;
                 m_dWaypointY=rand() % SECTORSIZE;
                 m_AI=AI_WANDER;
           }
       }
   }





switch(m_AI)
      {
      case AI_WANDER:
		  {
           SetSpeed(100);
           m_dAngleSeek=WayPoint(m_dWaypointX,m_dWaypointY);
		   double dDistance = Distance(m_dX,m_dY,m_dWaypointX,m_dWaypointY);
		   if (dDistance<40)
           {
                m_dWaypointX=rand() % SECTORSIZE;
                m_dWaypointY=rand() % SECTORSIZE;
           }
		   if ((m_nCloakCharge>=CLOAK_DELAY)&&((m_lstHealth[HLT_CLOAK]>60)||(m_nEnergy>500))&&((m_CloakState == CS_UNCLOAKED)||(m_CloakState == CS_DECLOAKING)))
			  {
					m_CloakState = CS_CLOAKING;
			  }
		  }
      break;

      case AI_CHASE:
        if (m_pTarget!=NULL)
           {
              if (((m_CloakState == CS_CLOAKED)||(m_CloakState == CS_CLOAKING))&&(m_dTargetDistance<1000))
			  {
					m_CloakState = CS_DECLOAKING;
					m_nCloakCharge=0;
			  }

			  tsx=m_pTarget->GetX()+cos(m_pTarget->GetAngle())*m_pTarget->GetSpeed();
              tsy=m_pTarget->GetY()+sin(m_pTarget->GetAngle())*m_pTarget->GetSpeed();
              m_dAngleSeek=WayPoint(tsx,tsy);
              SetSpeed(m_dTargetDistance/4);

			  double t=m_dAngleSeek-m_dAngle;
              if (t<0) t=-t;


			  if (m_nTask!=TSK_CONTACT)
			  {
                 if ((m_dTargetDistance<=600)&&(m_dTargetDistance>150)&&(t<0.1))
                 {
				     fire_photon();
				 }

                 if (m_dTargetDistance<100) m_AI=AI_EVADE;
			  }

           }
        else
           {
					m_dWaypointX=rand() % SECTORSIZE;
                    m_dWaypointY=rand() % SECTORSIZE;
					m_AI=AI_WANDER;
           }
      break;

      case AI_EVADE:
        if (m_pTarget!=NULL)
           {
              if (((m_CloakState == CS_CLOAKED)||(m_CloakState == CS_CLOAKING))&&(m_dTargetDistance<1000))
			  {
					m_CloakState = CS_DECLOAKING;
					m_nCloakCharge=0;
			  }


			  tsx=m_pTarget->GetX()+cos(m_pTarget->GetAngle())*m_pTarget->GetSpeed();
              tsy=m_pTarget->GetY()+sin(m_pTarget->GetAngle())*m_pTarget->GetSpeed();
              m_dAngleSeek=WayPoint(tsx,tsy);
              SetSpeed(m_dMaxSpeed);
			  double t=m_dAngleSeek-m_dAngle;
              if (t<0) t=-t;

			  if (m_nTask!=TSK_CONTACT)
			  {
                 if ((m_dTargetDistance<=600)&&(m_dTargetDistance>100)&&(t<0.1))
                 {
				     fire_photon();
				 }

                 if (m_dTargetDistance>400) m_AI=AI_CHASE;
			  }
			 m_dAngleSeek-=PI;
           }
        else
           {
               m_dWaypointX=rand() % SECTORSIZE;
               m_dWaypointY=rand() % SECTORSIZE;
               m_AI=AI_WANDER;
           }
      break;


    case AI_DOCK:
          if (! m_blDocked)
          {
              m_pBaseTarget = (TShip *) m_pEngine->Seekstarbase(m_Member,false,SECTORSIZE * 2,m_dX,m_dY);
              if ((m_pBaseTarget!=NULL) && ( !Dock(m_pBaseTarget) ))
              {
                  m_dAngleSeek=WayPoint(m_pBaseTarget->GetX(),m_pBaseTarget->GetY());
              }
          }
          else
          {
              bool can_go=true;
              if (m_blNoRelease) can_go=false;
              for (size_t i=0;i<m_lstHealth.size();i++)
              {
                 if (m_lstHealth[i]<m_nMaxHealth) can_go=false;
                 if (m_nTorpedoes<50) can_go=false;
              }

              if (can_go)
              {
                 m_blDocked = false;
                 m_blDocking = false;
                 m_blReleasing = true;
                 m_AI=AI_RELEASE;
              }
          }
    break;

     case AI_RELEASE:
          if (m_blReleasing)
          {
              Release(m_pBaseTarget);
          }
          else
          {
              m_blDocked = false;
              m_blDocking = false;
              m_blReleasing = false;
              m_dWaypointX=rand() % SECTORSIZE;
              m_dWaypointY=rand() % SECTORSIZE;
              m_AI=AI_WANDER;
          }
     break;


     default:

     break;

     }


//*******************************************************************************

DoEngineering();


if (m_nEnergy>0)
   {
      m_dSteer = m_lstHealth[HLT_THRUSTER]*0.0003;

      m_dAngleSeek = GetEvasiveAngle(m_dAngleSeek);

      Control();
   }
   else if (m_lstHealth[HLT_WARPCORE]<20)
   {
       m_lstHealth[HLT_HULL]=0;
   }
}

if (((m_nEnergy<20)||(m_lstHealth[HLT_CLOAK]<50))&&((m_CloakState == CS_CLOAKED)||(m_CloakState == CS_CLOAKING)))
{
	m_CloakState = CS_DECLOAKING;
	m_nCloakCharge=0;
}

if (m_dSpeed>(m_dMaxSpeed*m_lstHealth[HLT_IMPULSE])/100)
    {
        m_dSpeed=(m_dMaxSpeed*m_lstHealth[HLT_IMPULSE])/100;
    }

    if (m_dSpeed <0)
    {
        m_dSpeed =0;
    }

    if ((m_blDocked)&&
        ((m_pBaseTarget==NULL)||((m_pBaseTarget!=NULL)&&
        (m_pBaseTarget->m_blDestroyed))))
    {
       Die();
    }


}