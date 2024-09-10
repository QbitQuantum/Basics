void seekMonsters (Monster m[], Player p)
{
    float pX = p.getX() + p.getW() / 2;
    float pY = p.getY() + p.getH() / 2;
    //printf("Player X: %f\n",pX);
    //printf("Player Y: %f\n",pY);
    for (int i = 0; i < numMonsters; i ++)
    {
        if (m[i].isLive && m[i].canMove)
        {
            float mX = m[i].getX() + m[i].getW() / 2;
            float mY = m[i].getY() + m[i].getH() / 2;
            float diffX = pX - mX;
            float diffY = pY - mY;
            float distance = sqrt(diffX * diffX + diffY * diffY);
            float divider = m[i].getMaxSpeed() / distance;
            float mDx = divider * diffX;
            float mDy = divider * diffY;
            /*
            if (abs(mDx) < .2)
            {
                if (mDx < 0) mDx = -.21;
                if (mDx > 0) mDx = .21;
            }
            */
            m[i].setDx(mDx);
            m[i].setDy(mDy);
            //printf("Monster %d X: %f\n",i,mX);
            //printf("Monster %d Y: %f\n",i,mY);
            //printf("Distance %d: %f\n",i,distance);
            //printf("DX %d: %f\n",i,mDx);
            //printf("DY %d: %f\n",i,mDy);
        }
    }
}