KHero* KBall::GetBallTaker()
{
    KHero*          pHandler    = NULL;
    KMovableObject* pGuide      = NULL;
    
    pGuide = GetGuide();
    KG_PROCESS_ERROR(pGuide);

    KGLOG_PROCESS_ERROR(pGuide->Is(sotHero));
    pHandler = (KHero*)pGuide;        
    
Exit0:
    return pHandler;
}