void GraphicsContextPlatformPrivate::rotate(float degreesAngle)
{
    XFORM xform = TransformationMatrix().rotate(degreesAngle);
    ModifyWorldTransform(m_hdc, &xform, MWT_LEFTMULTIPLY);
}