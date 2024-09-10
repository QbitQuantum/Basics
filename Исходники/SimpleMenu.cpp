void SimpleMenu::Render()
{
    WFont * titleFont = WResourceManager::Instance()->GetWFont(fontId);
    titleFont->SetColor(ARGB(250,255,255,255));//reseting color on passes as this is a shared font now.
    WFont * mFont = WResourceManager::Instance()->GetWFont(fontId);
    if (0 == mWidth)
    {
        float sY = mY + SimpleMenuConst::kVerticalMargin;

        for (int i = 0; i < mCount; ++i)
        {
            float width = (static_cast<SimpleMenuItem*> (mObjects[i]))->GetEnlargedWidth() + 15;
            if (mWidth < width) mWidth = width;
        }

        float scaleFactor = titleFont->GetScale();
        titleFont->SetScale(SCALE_NORMAL);
        if ((!title.empty()) && (mWidth < titleFont->GetStringWidth(title.c_str()))) 
            mWidth = titleFont->GetStringWidth(title.c_str());
         titleFont->SetScale(scaleFactor);
        mWidth += 2 * SimpleMenuConst::kHorizontalMargin;

        if (mCenterHorizontal)
            mX = (SCREEN_WIDTH_F - mWidth) / 2;

        if (mCenterVertical)
            mY = (SCREEN_HEIGHT_F - mHeight) / 2;

        for (int i = 0; i < mCount; ++i)
        {
            float y = mY + SimpleMenuConst::kVerticalMargin + i * SimpleMenuConst::kLineHeight;
            SimpleMenuItem * smi = static_cast<SimpleMenuItem*> (mObjects[i]);
            smi->Relocate(mX + mWidth / 2, y);
            if (smi->hasFocus()) sY = y;
        }
        stars->Fire();
        selectionTargetY = selectionY = sY;
        timeOpen = 0;
    }

    JRenderer * renderer = JRenderer::GetInstance();

    float height = mHeight;
    if (timeOpen < 1) height *= timeOpen > 0 ? timeOpen : -timeOpen;

    float heightPadding = SimpleMenuConst::kLineHeight/2; // this to reduce the bottom padding of the menu
    renderer->FillRect(mX, mY, mWidth, height - heightPadding, ARGB(180,0,0,0));

    renderer->SetTexBlend(BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA);
    
    drawVertPole(mX, mY, height - heightPadding);
    drawVertPole(mX + mWidth, mY, height - heightPadding);
    drawHorzPole(mX, mY, mWidth);
    drawHorzPole(mX, mY + height - heightPadding, mWidth);
    //drawVertPole(mX, mY - 16, height + 32);
    //drawVertPole(mX + mWidth, mY - 16, height + 32);
    //drawHorzPole(mX - 16, mY, mWidth + 32);
    //drawHorzPole(mX - 25, mY + height, mWidth + 50);

    renderer->SetTexBlend(BLEND_SRC_ALPHA, BLEND_ONE);
    stars->Render();
    renderer->SetTexBlend(BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA);

    if (!title.empty()) 
    {
        float scaleFactor = titleFont->GetScale();
        titleFont->SetScale(SCALE_NORMAL);
        titleFont->DrawString(title.c_str(), mX + mWidth / 2, mY - 3, JGETEXT_CENTER);
        titleFont->SetScale(scaleFactor);
    }
    for (int i = startId; i < startId + maxItems; i++)
    {
        if (i > mCount - 1) break;
        SimpleMenuItem *currentMenuItem = static_cast<SimpleMenuItem*>(mObjects[i]);
        float currentY = currentMenuItem->getY() - SimpleMenuConst::kLineHeight * startId;
        float menuBottomEdge = mY + height - SimpleMenuConst::kLineHeight + 7;
        if (currentY < menuBottomEdge)
        {
            if (currentMenuItem->hasFocus())
            {
                WResourceManager::Instance()->GetWFont(Fonts::MAIN_FONT)->DrawString(currentMenuItem->getDescription().c_str(), mX
                                + mWidth + 10, mY + 15);
                mFont->SetColor(ARGB(255,255,255,0));
            }
            else
            {
                mFont->SetColor(ARGB(150,255,255,255));
            }
            (static_cast<SimpleMenuItem*> (mObjects[i]))->RenderWithOffset(-SimpleMenuConst::kLineHeight * startId);
        }
        mFont->SetScale(SCALE_NORMAL);
    }
    mFont->SetScale(SCALE_NORMAL);
}