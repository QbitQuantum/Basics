void BodyLinkViewImpl::doInverseKinematics(Vector3 p, Matrix3 R)
{
    InverseKinematicsPtr ik = currentBodyItem->getCurrentIK(currentLink);

    if(ik){
        currentBodyItem->beginKinematicStateEdit();

        if(KinematicsBar::instance()->isPenetrationBlockMode()){
            PenetrationBlockerPtr blocker = currentBodyItem->createPenetrationBlocker(currentLink, true);
            if(blocker){
                Position T;
                T.translation() = p;
                T.linear() = R;
                if(blocker->adjust(T, Vector3(p - currentLink->p()))){
                    p = T.translation();
                    R = T.linear();
                }
            }
        }
        if(ik->calcInverseKinematics(p, R)){
            currentBodyItem->notifyKinematicStateChange(true);
            currentBodyItem->acceptKinematicStateEdit();
        }
    }
}