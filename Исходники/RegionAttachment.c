void spRegionAttachment_updateOffset (spRegionAttachment* self) {
	float regionScaleX = self->width / self->regionOriginalWidth * self->scaleX;
	float regionScaleY = self->height / self->regionOriginalHeight * self->scaleY;
	float localX = -self->width / 2 * self->scaleX + self->regionOffsetX * regionScaleX;
	float localY = -self->height / 2 * self->scaleY + self->regionOffsetY * regionScaleY;
	float localX2 = localX + self->regionWidth * regionScaleX;
	float localY2 = localY + self->regionHeight * regionScaleY;
	float radians = self->rotation * DEG_RAD;
	float cosine = COS(radians), sine = SIN(radians);
	float localXCos = localX * cosine + self->x;
	float localXSin = localX * sine;
	float localYCos = localY * cosine + self->y;
	float localYSin = localY * sine;
	float localX2Cos = localX2 * cosine + self->x;
	float localX2Sin = localX2 * sine;
	float localY2Cos = localY2 * cosine + self->y;
	float localY2Sin = localY2 * sine;
	self->offset[SP_VERTEX_X1] = localXCos - localYSin;
	self->offset[SP_VERTEX_Y1] = localYCos + localXSin;
	self->offset[SP_VERTEX_X2] = localXCos - localY2Sin;
	self->offset[SP_VERTEX_Y2] = localY2Cos + localXSin;
	self->offset[SP_VERTEX_X3] = localX2Cos - localY2Sin;
	self->offset[SP_VERTEX_Y3] = localY2Cos + localX2Sin;
	self->offset[SP_VERTEX_X4] = localX2Cos - localYSin;
	self->offset[SP_VERTEX_Y4] = localYCos + localX2Sin;
}