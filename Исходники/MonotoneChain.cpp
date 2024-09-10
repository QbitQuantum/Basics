void
MonotoneChain::computeSelect(const Envelope& searchEnv,
                             size_t start0, size_t end0,
                             MonotoneChainSelectAction& mcs )
{
    const Coordinate& p0=pts[start0];
    const Coordinate& p1=pts[end0];
    mcs.tempEnv1.init(p0,p1);

    //Debug.println("trying:"+p0+p1+" [ "+start0+","+end0+" ]");
    // terminating condition for the recursion
    if(end0-start0==1)
    {
        //Debug.println("computeSelect:"+p0+p1);
        mcs.select(*this,start0);
        return;
    }
    // nothing to do if the envelopes don't overlap
    if (!searchEnv.intersects(mcs.tempEnv1))
        return;
    // the chains overlap,so split each in half and iterate (binary search)
    unsigned int mid=(start0+end0)/2;

    // Assert: mid != start or end (since we checked above for end-start <= 1)
    // check terminating conditions before recursing
    if (start0 < mid)
    {
        computeSelect(searchEnv,start0,mid,mcs);
    }
    
    if (mid < end0)
    {
        computeSelect(searchEnv,mid,end0,mcs);
    }
}