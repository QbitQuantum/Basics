PassRefPtr<TransformOperation> RotateTransformOperation::blend(const TransformOperation* from, double progress, bool blendToIdentity)
{
    if (from && !from->isSameType(*this))
        return this;
    
    if (blendToIdentity)
        return RotateTransformOperation::create(m_x, m_y, m_z, m_angle - m_angle * progress, m_type);
    
    const RotateTransformOperation* fromOp = static_cast<const RotateTransformOperation*>(from);
    
    // Optimize for single axis rotation
    if (!fromOp || (fromOp->m_x == 0 && fromOp->m_y == 0 && fromOp->m_z == 1) || 
                   (fromOp->m_x == 0 && fromOp->m_y == 1 && fromOp->m_z == 0) || 
                   (fromOp->m_x == 1 && fromOp->m_y == 0 && fromOp->m_z == 0)) {
        double fromAngle = fromOp ? fromOp->m_angle : 0;
        return RotateTransformOperation::create(fromOp ? fromOp->m_x : m_x, 
                                                fromOp ? fromOp->m_y : m_y, 
                                                fromOp ? fromOp->m_z : m_z, 
                                                UI::blend(fromAngle, m_angle, progress), m_type);
    }

    const RotateTransformOperation* toOp = this;

    // Create the 2 rotation matrices
    TransformationMatrix fromT;
    TransformationMatrix toT;
    fromT.rotate3d((float)(fromOp ? fromOp->m_x : 0),
                   (float)(fromOp ? fromOp->m_y : 0),
                   (float)(fromOp ? fromOp->m_z : 1),
                   (float)(fromOp ? fromOp->m_angle : 0));

    toT.rotate3d((float)(toOp ? toOp->m_x : 0),
                 (float)(toOp ? toOp->m_y : 0),
                 (float)(toOp ? toOp->m_z : 1),
                 (float)(toOp ? toOp->m_angle : 0));
    
    // Blend them
    toT.blend(fromT, progress);
    
    // Extract the result as a quaternion
    TransformationMatrix::DecomposedType decomp;
    toT.decompose(decomp);
    
    // Convert that to Axis/Angle form
    double x = -decomp.quaternionX;
    double y = -decomp.quaternionY;
    double z = -decomp.quaternionZ;
    double length = sqrt(x * x + y * y + z * z);
    double angle = 0;
    
    if (length > 0.00001) {
        x /= length;
        y /= length;
        z /= length;
        angle = rad2deg(acos(decomp.quaternionW) * 2);
    } else {
        x = 0;
        y = 0;
        z = 1;
    }
    return RotateTransformOperation::create(x, y, z, angle, ROTATE_3D);
}