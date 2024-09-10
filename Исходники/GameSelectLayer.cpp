bool LsTouch::isParentAllVisible(LsTouchEvent* lsTe)
{
    bool bRef = true;
    CCNode* nLsTe = dynamic_cast<CCNode*>(lsTe);
    CCNode* parent = getParent();
    do
    {
        if (!parent)
        {
            bRef = false;
            break;
        }
        if (nLsTe == parent)
        {
            break;
        }
        if (!parent->isVisible())
        {
            bRef = false;
            break;
        }
        parent = parent->getParent();
    } while (1);

    return bRef;
}