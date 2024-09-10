void TransformationMatrix::blend(const TransformationMatrix& from, double progress)
{
    if (from.isIdentity() && isIdentity())
        return;
        
    // decompose
    DecomposedType fromDecomp;
    DecomposedType toDecomp;
    from.decompose(fromDecomp);
    decompose(toDecomp);

    // interpolate
    blendFloat(fromDecomp.scaleX, toDecomp.scaleX, progress);
    blendFloat(fromDecomp.scaleY, toDecomp.scaleY, progress);
    blendFloat(fromDecomp.scaleZ, toDecomp.scaleZ, progress);
    blendFloat(fromDecomp.skewXY, toDecomp.skewXY, progress);
    blendFloat(fromDecomp.skewXZ, toDecomp.skewXZ, progress);
    blendFloat(fromDecomp.skewYZ, toDecomp.skewYZ, progress);
    blendFloat(fromDecomp.translateX, toDecomp.translateX, progress);
    blendFloat(fromDecomp.translateY, toDecomp.translateY, progress);
    blendFloat(fromDecomp.translateZ, toDecomp.translateZ, progress);
    blendFloat(fromDecomp.perspectiveX, toDecomp.perspectiveX, progress);
    blendFloat(fromDecomp.perspectiveY, toDecomp.perspectiveY, progress);
    blendFloat(fromDecomp.perspectiveZ, toDecomp.perspectiveZ, progress);
    blendFloat(fromDecomp.perspectiveW, toDecomp.perspectiveW, progress);
    
    slerp(&fromDecomp.quaternionX, &toDecomp.quaternionX, progress);
        
    // recompose
    recompose(fromDecomp);
}