void SimpleSpriteRenderer::render(RenderItem *item) {
	Texture *texture = NULL;
	if (item->textureName[0]) {
		texture = context->glResourceManager->getTexture(item->textureName);
		if (!texture) {
			char buf[1024];
			sprintf(buf, "Texture not found %s", item->textureName);
			logmsg(buf);
		}
	}
	Matrix4f bbMat;
	BOOL32 isBB = item->renderType == RenderItem::RENDERTYPE_BB;
	Vector4f newUvs = item->uvs;
	if (isBB) {
		// calculate billboard matrix
		Vector3f dir = context->world->camera->pos - item->pos;
		dir.normalize();
		Vector3f newY = context->world->camera->invRotMatrix * Vector3f(0,1,0);
		Vector3f newX = context->world->camera->invRotMatrix * Vector3f(1,0,0);
		bbMat.data[0] = newX.x;
		bbMat.data[1] = newX.y;
		bbMat.data[2] = newX.z;
		bbMat.data[4] = newY.x;
		bbMat.data[5] = newY.y;
		bbMat.data[6] = newY.z;
		bbMat.data[8] = dir.x;
		bbMat.data[9] = dir.y;
		bbMat.data[10] = dir.z;
		// uvs will need flipping to avoid switching to LHS to flip Y
		newUvs.y = newUvs.w;
		newUvs.w = item->uvs.y;
	}
	context->quadRenderer->render(texture, item->pos, item->orientation.v.z, newUvs, Vector2f(item->scale.x, item->scale.y), item->colorFilter, item->flags & RENDERITEM_FLAG_IS_OPAQUE, isBB, bbMat);
}