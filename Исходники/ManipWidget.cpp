void ManipWidget::orientToCamera(void)
{
	assert(isActive); // why would we need to orient inactive manipwidget?

	SbVec3f cameraPos = viewer->getCamera()->position.getValue();
	SbRotation cameraRot = viewer->getCamera()->orientation.getValue();

	SbVec3f widgetPos = applyMatrix(
							localToWorldMatrix(),
							SbVec3f(0, 0, 0));
	SbVec3f d = cameraPos - widgetPos;
	d.normalize();

	// compensate for rotation
	SbVec3f trans;
	SbRotation rot, scaleOrient;
	SbVec3f scale;
	localToWorldMatrix().inverse().getTransform(trans, rot, scale, scaleOrient);
	rot.multVec(d, d);

	cameraUpdatedVirtual(d, cameraRot * rot);
}