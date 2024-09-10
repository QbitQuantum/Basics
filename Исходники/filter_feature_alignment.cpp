typename ALIGNER_TYPE::Result FilterFeatureAlignment::RansacOperation(MeshModel& mFix, MeshModel& mMov, typename ALIGNER_TYPE::Parameters& param, CallBackPos *cb)
{
    typedef ALIGNER_TYPE AlignerType;
    typedef typename AlignerType::MeshType MeshType;
    typedef typename AlignerType::FeatureType FeatureType;
    typedef typename MeshType::ScalarType ScalarType;
    typedef typename AlignerType::Result ResultType;

    //enables needed attributes. MM_VERTMARK is used by the getClosest functor.
    mFix.updateDataMask(MeshModel::MM_VERTMARK|FeatureType::getRequirements());
    mMov.updateDataMask(MeshModel::MM_VERTMARK|FeatureType::getRequirements());

    AlignerType aligner;
    param.log = &mylogger; //set the callback used to print infos inside the procedure
    ResultType res = aligner.init(mFix.cm, mMov.cm, param, cb);
    if(res.exitCode==ResultType::FAILED) return res;

    //perform RANSAC and get best transformation matrix
    res = aligner.align(mFix.cm, mMov.cm, param, cb);

    //apply transformation. If ransac don't find a good matrix, identity is returned; so nothing is wrong here...
    mMov.cm.Tr = res.tr * mMov.cm.Tr;

    return res;
}