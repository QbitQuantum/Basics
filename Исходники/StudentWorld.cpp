int StudentWorld::move()
{
    int score = getScore();
    int lives = getLives();
    int level = getLevel();
    ostringstream oss;
    string s;
        oss << "Score: " << score << "  Level: " << level << "  Lives: " << lives << "  Bonus: " << m_bonus;
        s = oss.str();
    setGameStatText(s);
    
    m_player->doSomething();
    
    for (int i = 0; i < Actors.size(); i++)
    {
        if (Actors[i]->isAlive() == false)
        {
            delete Actors[i];
            Actors.erase(Actors.begin() + i);
            i--;
            break;
        }
        Actors[i]->doSomething();
    }
    
    if (m_bonus > 0)
    {
        m_bonus--;
    }

    if (anyLiveZumi() == false)
    {
        Exit* exit;
        int EX, EY;
        for (int i = 0; i < Actors.size(); i++)
        {
                Exit *bp = dynamic_cast<Exit*>(Actors[i]);
                if (bp != nullptr)
                {
                    exit = bp;
                    Actors[i]->revealit();
                    EX = Actors[i]->getX();
                    EY = Actors[i]->getY();
                }
        }
        int PX = m_player->getX();
        int PY = m_player->getY();
        if (PX == EX && PY == EY)
        {
            exit->setDead();
            increaseScore(m_bonus);
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }

    if (m_player->isAlive() == false)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}