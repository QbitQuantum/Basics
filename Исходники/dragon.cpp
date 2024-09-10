void CDragonEnemy::OnPrepare() 
{
     float dirToPlayer;  // the angle of the enemy-player vector

     CVector diff;       // the vector from the enemy to the player
     diff.x = position.x - player->position.x;
     diff.z = position.z - player->position.z;
     diff.Normalize();

     // find the angle in the world of the vector from the enemy to the player
     // in relation the negative z-axis
     dirToPlayer = RAD2DEG(diff.Angle(CVector(0,0,-1)));

     // seed random generator
     srand((unsigned int)time(NULL));

     ProcessAI();
     // now do Ogro prep
     // set modelState based on AIstate
     switch (aiState)
     {
     case AI_SCARED:
          direction = (dirToPlayer - 90) + ((rand()%90)-45);          // set the direction of the enemy
		  // -90 to 90 degrees
		//	modelState = MODEL_RUN;
		//	velocity = CVector(0.0, 0.0, 15.0);
			modelState = MODEL_JUMP;
          break;
     case AI_UNCARING:
          direction = float(rand() % 360);
          if ((rand() % 4) != 0)
          {
               modelState = MODEL_IDLE;
               velocity = CVector(0.0, 0.0, 0.0);
          }
          else
          {
              velocity = CVector(0.0, 0.0, 15.0);
              modelState = MODEL_RUN;
          }
          break;
     case AI_DEAD:
          modelState = MODEL_DIE;
          velocity = CVector(0.0, 0.0, 0.0);
		  if(nextFrame == 178)
			  PlaySound();
          if (nextFrame == stateStart)
          {
			  		  
               // time to kill the monster
               isDead = true;
          }
          break;
     default:
          break;
     }

     // do prep for MD2 Model states
     CEntity::OnPrepare();
}