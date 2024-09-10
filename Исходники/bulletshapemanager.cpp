    virtual void apply(osg::Drawable &drawable)
    {
        if (!mTriangleMesh)
            mTriangleMesh.reset(new btTriangleMesh);

        osg::Matrixf worldMat = osg::computeLocalToWorld(getNodePath());
        osg::TriangleFunctor<GetTriangleFunctor> functor;
        functor.setTriMesh(mTriangleMesh.get());
        functor.setMatrix(worldMat);
        drawable.accept(functor);
    }