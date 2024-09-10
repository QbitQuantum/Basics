CullVisitor::value_type CullVisitor::computeNearestPointInFrustum(const osg::Matrix& matrix, const osg::Polytope::PlaneList& planes,const osg::Drawable& drawable)
{
    // OSG_WARN<<"CullVisitor::computeNearestPointInFrustum("<<getTraversalNumber()<<"\t"<<planes.size()<<std::endl;

    osg::TriangleFunctor<ComputeNearestPointFunctor> cnpf;
    cnpf.set(_computed_znear, matrix, &planes);
    
    drawable.accept(cnpf);

    return cnpf._znear;
}