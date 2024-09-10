double TransformErrFunction::evaluateReprojErrInt()
{
    double reprojErr = 0;
    for(TransformSet::const_iterator ppTrans = transformSet_->begin(); ppTrans != transformSet_->end(); ppTrans++)
    {
        int j = ppTrans->first.im1Id();
        int k = ppTrans->first.im2Id();

        if(j != alignTo_ && k != alignTo_ && (j > minIdToRefine_ || k > minIdToRefine_))
        {
            IdPair j0(j, alignTo_);
            IdPair k0(k, alignTo_);
            const Transform * Tj0 = (*transformSet_)[j0]->transform();
            const Transform * Tk0 = (*transformSet_)[k0]->transform();

            const Transform * Tjk = ppTrans->second->transform();
            int inlierCount = ppTrans->second->correspondences().size();

            Transform * Tj0_from_jk = Tk0->accumulate(Tjk);
            reprojErr += getErr(Tj0, Tj0_from_jk, inlierCount);
            delete Tj0_from_jk;
        }
        /*else if(j != alignTo_ ) //Here ppTrans->first.second == alignTo_. Don't calc reproj err for identity!
        {
            const Transform * Tj0 = ppTrans->second->transform();
            reprojErr += getErr(Tj0);

        }*/
    }
    return reprojErr * scaleCost_; //scaleCost_ makes errors initially about 1
}