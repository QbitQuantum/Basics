///---------------------------------------------------------------------------------
///
///---------------------------------------------------------------------------------
Vector3 InputSystem::GetWNormalizedMouseFarPosition( OpenGLRenderer* renderer )
{
    if (!renderer)
        return Vector3::ZERO;

    Vector2 mousePos = GetMousePosition();
    Vector2 halfDisplaySize( renderer->GetDisplayWidth() * 0.5f, renderer->GetDisplayHeight() * 0.5f );
    Vector2 offset = mousePos - halfDisplaySize;
    Vector2 ndcCoords( RangeMap( offset.x, -halfDisplaySize.x, halfDisplaySize.x, -1.0f, 1.0f ), RangeMap( offset.y, -halfDisplaySize.y, halfDisplaySize.y, -1.0f, 1.0f ) );

    Matrix4f perspectiveToWorld = MatrixMultiply( renderer->GetViewMatrix(), renderer->GetPerspectiveMatrix() );
    perspectiveToWorld.Invert();

    Vector4f farWorldPosVec = perspectiveToWorld.TransformVector( Vector4f( ndcCoords.x, ndcCoords.y, 1.0f, 1.0f ) );

    Vector3 farWorldPos( farWorldPosVec.x / farWorldPosVec.w, farWorldPosVec.y / farWorldPosVec.w, farWorldPosVec.z / farWorldPosVec.w );

    return farWorldPos;
}