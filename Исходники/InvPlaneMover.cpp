// internal callback
void InvPlaneMover::dragFinishCB(void *me, SoDragger *drag)
{

    InvPlaneMover *mee = static_cast<InvPlaneMover *>(me);

    if (mee->show_)
    {

        SbVec3f t = ((SoJackDragger *)drag)->translation.getValue();

        int i;
        for (i = 0; i < 3; ++i)
            t[i] *= mee->scale_->scaleFactor.getValue()[i];

        SbRotation r = ((SoJackDragger *)drag)->rotation.getValue();

        SbVec3f n;
        SbVec3f ax;
        float angle;
        r.getValue(ax, angle);

        SbVec3f axN;
        mee->fullRot_->rotation.getValue().multVec(ax, axN);

        r.setValue(axN, angle);

        r.multVec(mee->nnn_, n);

        // we have to rotate the translation around the x-axis
        // (because we have a y-axis dragger)
        SbVec3f tt;
        n.normalize();

        // snap normal to the closest coordinate axis
        // here done by snaping it to the axis with the biggest projection onto it.
        if (mee->motionMode_ == InvPlaneMover::SNAP)
        {
            int axis;
            float mmax;
            int dir = 1;
            SbVec3f nn;

            if (n[0] * n[0] < n[1] * n[1])
            {
                axis = 1;
                mmax = n[1];
                if (n[1] < 0)
                    dir = -1;
                else
                    dir = +1;
                //dir = (int) copysign(1,n[1]);
            }
            else
            {
                axis = 0;
                mmax = n[0];
                if (n[0] < 0)
                    dir = -1;
                else
                    dir = +1;
                //dir = (int) copysign(1,n[0]);
            }
            if (mmax * mmax < n[2] * n[2])
            {
                axis = 2;
                if (n[2] < 0)
                    dir = -1;
                else
                    dir = +1;
                //dir = (int) copysign(1,n[2]);
            }

            switch (axis)
            {
            case 0:
                nn.setValue(1, 0, 0);
                break;
            case 1:
                nn.setValue(0, 1, 0);
                break;
            case 2:
                nn.setValue(0, 0, 1);
                break;
            }
            n = dir * nn;
        }

        tt = t[1] * n;

        float d;
        d = n.dot(tt + mee->distOffset_);

        float data[4];
        data[0] = n[0];
        data[1] = n[1];
        data[2] = n[2];
        data[3] = d;

        // send feedback message to contoller
        ((InvPlaneMover *)me)->sendFeedback(data);
    }
}