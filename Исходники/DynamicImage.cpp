    void DynamicImage::update()
    {
        


        if (!sleep)
        {
            NxVec3 towardsVector = tarPos - curPos;

            switch (mode)
            {
            case 0:     //Linear
                if (towardsVector.magnitude() < LINEAR_VELOCITY)
                {
                    curPos = tarPos;
                    sleep = true;
                }
                else
                {
                    towardsVector.normalize();
                    curPos = curPos + (towardsVector * LINEAR_VELOCITY);
                }
                break;


            case 1:     //Halfling
                if (towardsVector.magnitude() < THRESHOLD)
                {
                    curPos = tarPos;
                    sleep = true;
                }
                else
                {
                    curPos = curPos + (towardsVector * 0.033f);
                }
                break;

            }
        }
    }