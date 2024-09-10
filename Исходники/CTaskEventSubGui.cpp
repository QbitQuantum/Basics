//-----------------------------------------------
//
//
void CTaskEventSubGui::menuCallback(CCObject * pSender)
{
	CGameWorldScene* pWorldLayer =  ( CGameWorldScene* )getParent();
    pWorldLayer->EnableAllWorldButton( true );
    getParent()->removeChild(this,true);
}