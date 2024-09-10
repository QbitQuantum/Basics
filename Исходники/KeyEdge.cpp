void KeyEdge::prepareSculptPreserveTangents_()
{
    const bool preserveTangentEdges = false;
    if (!preserveTangentEdges)
        return;


    // find instant edges where tangency must be preserved
    sculpt_beginLeftDer_ = geometry()->der(0);
    sculpt_beginRightDer_ = geometry()->der(geometry()->length());
    sculpt_keepRightAsLeft_.clear();
    sculpt_keepLeftAsLeft_.clear();
    sculpt_keepLeftAsRight_.clear();
    sculpt_keepRightAsRight_.clear();
    sculpt_keepMyselfTangent_ = false;
    if (preserveTangentEdges)
    {
        double dotThreshold = 0.9;
        if(startVertex_)
        {
            KeyEdgeSet leftEdges =  startVertex_->spatialStar();
            leftEdges.remove(this);
            foreach(KeyEdge * ie, leftEdges)
            {
                if(ie->endVertex_ == startVertex_)
                {
                    Eigen::Vector2d rightDer = ie->geometry()->der(ie->geometry()->length());
                    double dot = rightDer.dot(sculpt_beginLeftDer_);
                    if(dot > dotThreshold)
                        sculpt_keepRightAsLeft_ << ie;
                }
                if(ie->startVertex_ == startVertex_)
                {
                    Eigen::Vector2d rightDer = - ie->geometry()->der(0);
                    double dot = rightDer.dot(sculpt_beginLeftDer_);
                    if(dot > dotThreshold)
                        sculpt_keepLeftAsLeft_ << ie;
                }
            }
        }
        if(endVertex_)
        {
            KeyEdgeSet rightEdges =  endVertex_->spatialStar();
            rightEdges.remove(this);
            foreach(KeyEdge * ie, rightEdges)
            {
                // For now, disabling tangent preservation for 0-edge loops
                if(ie == this)
                    continue;

                if(ie->startVertex_ == endVertex_)
                {
                    Eigen::Vector2d leftDer = ie->geometry()->der(0);
                    double dot = leftDer.dot(sculpt_beginRightDer_);
                    if(dot > dotThreshold)
                        sculpt_keepLeftAsRight_ << ie;
                }
                if(ie->endVertex_ == endVertex_)
                {
                    Eigen::Vector2d leftDer = - ie->geometry()->der(ie->geometry()->length());
                    double dot = leftDer.dot(sculpt_beginRightDer_);
                    if(dot > dotThreshold)
                        sculpt_keepRightAsRight_ << ie;
                }
            }
        }
        if(endVertex_ && (endVertex_ == startVertex_))
        {
            // For now, disabling tangent preservation for 0-edge loops
            // What's below doesn't work, because continueSculpt assume
            // no resampling has occured since prepareSculpt

            //double dot = sculpt_beginRightDer_.dot(sculpt_beginLeftDer_);
            //if(dot > dotThreshold)
            //{
            //    sculpt_keepMyselfTangent_ = true;
            //}
        }
    }
}