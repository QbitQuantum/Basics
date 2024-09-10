void SpriteRenderNode::render() {
	if(!hidden && (!scene->isPaused() || renderWhenPaused)) {
		bool renderSprites = scene->getAttribute(RENDER_SPRITES)->getBooleanValue();
		if(renderSprites) {
			pantheios::log(pantheios::debug, "Rendering Sprite ", HashedStringInserter(texture), " for ", GameObjectInserter(*(getOwner())));
			
			Texture* tex = CalicoAPI::getResourceManager()->getTexture(texture);
			assert(tex != NULL);
			
			if(tex != NULL) {
				if(needToRegenerateVBO) {
					generateVBO();
				}
				
				Rect2D boundsRect = getWorldRect();
				
				Transform* ownerTransform = owner->getTransform();
				Vector3 ownerPosition = *(ownerTransform->getPosition());
				Rect2D spriteBounds(Vector2(ownerPosition.X() + boundsRect.min.X(), ownerPosition.Y() + boundsRect.min.Y()), 
									Vector2(ownerPosition.X() + boundsRect.max.X(), ownerPosition.Y() + boundsRect.max.Y()));
				Rect2D cameraBounds = layer->getCamera()->getWorldBounds();
				
				// only draw if the sprite is actually on-screen
				
				// TODO - this is buggy!
//				if(spriteBounds.intersects(cameraBounds)) {
					glPushMatrix();
					glMultMatrixf(ownerTransform->ToGlWorldMatrix(flip));
					
					tex->bind();
					
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glEnableClientState(GL_COLOR_ARRAY);
					
					glBindBuffer(GL_ARRAY_BUFFER, vbo);
					glVertexPointer(2, GL_FLOAT, sizeof(VertexPt), 0);
					glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VertexPt), (unsigned char*) (sizeof(GLfloat) * 2));
					glTexCoordPointer(2, GL_FLOAT, sizeof(VertexPt), (unsigned char*) (sizeof(GLfloat) * 2 + sizeof(GLubyte) * 4));
					
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
					
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					
					glPopMatrix();
//				}
			}
		}
	}
}