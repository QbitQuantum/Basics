Bounds::Bounds(const agg::trans_affine& trans, 
               agg::path_storage* path, pathAttr* attr, double dilation,
               double scale)
{
    double centx = attr->mCentroid.x;
    double centy = attr->mCentroid.y;
    trans.transform(&centx, &centy);

    mValid = attr->boundingRect(path, trans, mMin_X, mMin_Y, mMax_X, mMax_Y, scale);
    
    if (mValid && mMin_X <= centx && mMax_X >= centx &&
                  mMin_Y <= centy && mMax_Y >= centy && dilation != 1.0)
    {
        mMin_X = dilation * (mMin_X - centx) + centx;
        mMax_X = dilation * (mMax_X - centx) + centx;
        mMin_Y = dilation * (mMin_Y - centy) + centy;
        mMax_Y = dilation * (mMax_Y - centy) + centy;
    }
}