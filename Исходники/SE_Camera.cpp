SE_Matrix4f SE_Camera::getWorldToViewMatrix() const
{
    SE_Matrix4f vtow = getViewToWorldMatrix();
    return vtow.inverse(); 
}