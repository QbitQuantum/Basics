Vector3D OpenGLSceneViewCore::positionFromRotatedAxisPoint(Axis axis, NSPoint point, Quaternion rotation)
{
    DrawPlane(_camera->GetAxisX(), _camera->GetAxisY(), planeSize);
	
	Vector3D position = positionInSpaceByPoint(point);
	Vector3D result = _manipulated->selectionCenter();
	position = rotation.Conjugate().ToMatrix().Transform(position);
	result[(int)axis] = position[(int)axis];
	return result;
}