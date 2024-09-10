void SurfaceAttach::setOutPlugs(MDataBlock dataBlock, const MFnNurbsSurface &fnSurface,
                                const double dataOffset, const bool dataReverse, const short dataGenus, const double dataStaticLength,
                                const MMatrix &dataParentInverse, const short dataDirection) {

    MTransformationMatrix tfm;
    MVector t;
    MEulerRotation r;

    MArrayDataHandle outputHandle = dataBlock.outputArrayValue(SurfaceAttach::out);
    std::int32_t count = outputHandle.elementCount();
    MDataHandle o;

    for (unsigned int k = 0; k < count; ++k) {
        outputHandle.jumpToElement(k);

        // Get Transformations
        tfm = this->matrix(fnSurface, outputHandle.elementIndex(), dataOffset, dataReverse, dataGenus,
                           dataStaticLength, dataParentInverse, dataDirection);
        t = tfm.translation(MSpace::Space::kWorld);
        r = tfm.eulerRotation();

        o = outputHandle.outputValue();
        o.child(SurfaceAttach::translate).set(t);
        o.child(SurfaceAttach::rotate).set(r.x, r.y, r.z);
    }

    // Mark Clean
    dataBlock.setClean(SurfaceAttach::translate);
    dataBlock.setClean(SurfaceAttach::rotate);
    dataBlock.setClean(SurfaceAttach::out);
}