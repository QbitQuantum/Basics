bool PenetrationBlockerImpl::adjust(Position& io_T, const Vector3& pushDirection)
{
    if(isPrevBlocked){
        if((io_T.translation() - prevBlockedPosition).dot(prevBlockedNormal) < 0.0){
            io_T.translation() = prevBlockedPosition;
            return true;
        }
    }

    bool blocked = false;
    s = pushDirection.normalized();
    
    for(size_t i=0; i < opponentLinks.size(); ++i){
        collisionDetector->updatePosition(i+1, opponentLinks[i]->position());
    }

    int loop;
    maxnormal = Vector3::Zero();
    
    for(loop = 0; loop < 100; ++loop){

        collisionDetector->updatePosition(0, io_T);

        maxsdepth = 0.0;
        maxdepth = 0.0;

        collisionDetector->detectCollisions(std::bind(&PenetrationBlockerImpl::onCollisionDetected, this, _1));
        
        if(maxsdepth > 0.0){
            io_T.translation() += (maxdepth - targetDepth) * maxnormal;
            blocked = true;
        } else {
            break;
        }
    }

    isPrevBlocked = blocked;
    prevBlockedPosition = io_T.translation();
    prevBlockedNormal = maxnormal;

    return blocked;
}