bool CCTextFieldTTF::attachWithIME()
{
    bool bRet = CCIMEDelegate::attachWithIME();
    if (bRet)
    {
        // open keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
            if (getKeyboardType() ==KEY_BOARD_TYPE_NORMAL) {
                pGlView->setIMEKeyboardDefault();
            }
            else if (getKeyboardType() ==KEY_BOARD_TYPE_NUMBER) {
                pGlView->setIMEKeyboardNumber();
            }
            pGlView->setIMEKeyboardState(true);
        }
    }
    return bRet;
}