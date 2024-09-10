void HeadTrackedStereoCameraDecorator::getViewing(Matrix &result, 
                                           UInt32  OSG_CHECK_ARG(width ),
                                           UInt32  OSG_CHECK_ARG(height))
{
    Node *pUser = getUser();

    if(pUser == NULL)
    {
        FWARNING(("HeadTrackedStereoCameraDecorator::getViewing: no user!\n"));

        Camera *pCamera = getDecoratee();

        if(pCamera == NULL)
        {
            result.setIdentity();

            return;
        }

        pCamera->getBeacon()->getToWorld(result);

        result.invert();
    }
    else
    {
        pUser->getToWorld(result);

        result.invert();
    }
}