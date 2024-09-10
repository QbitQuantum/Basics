void MenuScene::onLButtonDown(int x, int y)
{
    if (x > 385 && x < (385 + 164)) // Login Button
    {
        if (y > 178 && y < (178 + 22))
            login();

#ifdef DEF_MAKEACCOUNT
        if (y > 216 && y < (216 + 22))
            newAccount();
#endif

        if (y > 255 && y < (255 + 22))
            onExit();
    }
}