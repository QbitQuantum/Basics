bool SkNormalMapSourceImpl::computeNormTotalInverse(const SkShaderBase::ContextRec& rec,
                                                    SkMatrix* normTotalInverse) const {
    SkMatrix total = SkMatrix::Concat(*rec.fMatrix, fMapShader->getLocalMatrix());
    if (rec.fLocalMatrix) {
        total.preConcat(*rec.fLocalMatrix);
    }

    return total.invert(normTotalInverse);
}