GoalStateOfHealth::~GoalStateOfHealth()
{
    if( _player->isOverActivity() )
    {	
        Virtues* virtues = getScene()->getCareer()->getVirtues();
        assert( _finite( getGoalScore() ) );
        virtues->evolution.score += getGoalScore();
        if( virtues->evolution.score < 0 )
        {
            virtues->evolution.score = 0;
        }
        if( virtues->evolution.health == 0 )
        {
            bool creditsIsAffected = true;            
            // credits is not affected for licensed character
            creditsIsAffected = !_scene->getCareer()->getLicensedFlag();
            // credits is not affected in developer edition
			if ( Gameplay::iGameplay->_cheatsEnabled )
			{
				creditsIsAffected = false;
			}
            #ifdef GAMEPLAY_DEVELOPER_EDITION
                creditsIsAffected = false;
            #endif
            getCore()->logMessage( "creditsIsAffected=%d", creditsIsAffected );

            if( creditsIsAffected ) virtues->evolution.credits--;
            if( virtues->evolution.credits > 0 )
            {
                virtues->evolution.health = 0.125f;
            }
        }
    }
}