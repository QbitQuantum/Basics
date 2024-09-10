// If you are getting segfaults in this function it may be ecause you are
// compliling the plugin with differently from pybullet, try complining the
// plugin with distutils too.
void EGLRendererVisualShapeConverter::convertVisualShapes(
	int linkIndex, const char* pathPrefix, const btTransform& localInertiaFrame,
	const UrdfLink* linkPtr, const UrdfModel* model,
	int collisionObjectUniqueId, int bodyUniqueId, struct  CommonFileIOInterface* fileIO)
{
	btAssert(linkPtr);  // TODO: remove if (not doing it now, because diff will be 50+ lines)
	if (linkPtr)
	{
		bool useVisual;
		int cnt = 0;

		if (linkPtr->m_visualArray.size() > 0)
		{
			useVisual = true;
			cnt = linkPtr->m_visualArray.size();
		}
		else
		{
			// We have to see something, take collision shape. Useful for MuJoCo xml, where there are no explicit visual shapes.
			useVisual = false;
			cnt = linkPtr->m_collisionArray.size();
		}

		for (int v1 = 0; v1 < cnt; v1++)
		{
			btAlignedObjectArray<MyTexture3> textures;
			btAlignedObjectArray<GLInstanceVertex> vertices;
			btAlignedObjectArray<int> indices;
			btTransform startTrans;
			startTrans.setIdentity();
			//int graphicsIndex = -1;

			const UrdfShape* vis;
			if (useVisual)
			{
				vis = &linkPtr->m_visualArray[v1];
			}
			else
			{
				vis = &linkPtr->m_collisionArray[v1];
			}
			// see note at function header
			btTransform childTrans = vis->m_linkLocalFrame;

			int colorIndex = linkIndex;  //colObj? colObj->getBroadphaseHandle()->getUid() & 3 : 0;
			if (colorIndex < 0)
				colorIndex = 0;
			colorIndex &= 3;
			btVector4 color;
			color = sColors[colorIndex];
			float rgbaColor[4] = {(float)color[0], (float)color[1], (float)color[2], (float)color[3]};
			//if (colObj->getCollisionShape()->getShapeType()==STATIC_PLANE_PROXYTYPE)
			//{
			//	color.setValue(1,1,1,1);
			//}
			if (model)
			{
				if (useVisual)
				{
					btHashString matName(linkPtr->m_visualArray[v1].m_materialName.c_str());
					UrdfMaterial* const* matPtr = model->m_materials[matName];
					if (matPtr)
					{
						for (int i = 0; i < 4; i++)
						{
							rgbaColor[i] = (*matPtr)->m_matColor.m_rgbaColor[i];
						}
						//printf("UrdfMaterial %s, rgba = %f,%f,%f,%f\n",mat->m_name.c_str(),mat->m_rgbaColor[0],mat->m_rgbaColor[1],mat->m_rgbaColor[2],mat->m_rgbaColor[3]);
						//m_data->m_linkColors.insert(linkIndex,mat->m_rgbaColor);
					}
					else
					{
						///programmatic created models may have the color in the visual
						if (vis && vis->m_geometry.m_hasLocalMaterial)
						{
							for (int i = 0; i < 4; i++)
							{
								rgbaColor[i] = vis->m_geometry.m_localMaterial.m_matColor.m_rgbaColor[i];
							}
						}
					}
				}
			}
			else
			{
				if (vis && vis->m_geometry.m_hasLocalMaterial)
				{
					for (int i = 0; i < 4; i++)
					{
						rgbaColor[i] = vis->m_geometry.m_localMaterial.m_matColor.m_rgbaColor[i];
					}
				}
			}

			EGLRendererObjectArray** visualsPtr = m_data->m_swRenderInstances[collisionObjectUniqueId];
			if (visualsPtr == 0)
			{
				m_data->m_swRenderInstances.insert(collisionObjectUniqueId, new EGLRendererObjectArray);
			}
			visualsPtr = m_data->m_swRenderInstances[collisionObjectUniqueId];

			btAssert(visualsPtr);
			EGLRendererObjectArray* visuals = *visualsPtr;
			visuals->m_objectUniqueId = bodyUniqueId;
			visuals->m_linkIndex = linkIndex;

			b3VisualShapeData visualShape;
			visualShape.m_objectUniqueId = bodyUniqueId;
			visualShape.m_linkIndex = linkIndex;
			visualShape.m_localVisualFrame[0] = vis->m_linkLocalFrame.getOrigin()[0];
			visualShape.m_localVisualFrame[1] = vis->m_linkLocalFrame.getOrigin()[1];
			visualShape.m_localVisualFrame[2] = vis->m_linkLocalFrame.getOrigin()[2];
			visualShape.m_localVisualFrame[3] = vis->m_linkLocalFrame.getRotation()[0];
			visualShape.m_localVisualFrame[4] = vis->m_linkLocalFrame.getRotation()[1];
			visualShape.m_localVisualFrame[5] = vis->m_linkLocalFrame.getRotation()[2];
			visualShape.m_localVisualFrame[6] = vis->m_linkLocalFrame.getRotation()[3];
			visualShape.m_rgbaColor[0] = rgbaColor[0];
			visualShape.m_rgbaColor[1] = rgbaColor[1];
			visualShape.m_rgbaColor[2] = rgbaColor[2];
			visualShape.m_rgbaColor[3] = rgbaColor[3];
			{
				B3_PROFILE("convertURDFToVisualShape2");
				convertURDFToVisualShape2(vis, pathPrefix, localInertiaFrame.inverse() * childTrans, vertices, indices, textures, visualShape, fileIO, m_data->m_flags);
			}
			m_data->m_visualShapes.push_back(visualShape);

			if (vertices.size() && indices.size())
			{
				TinyRenderObjectData* tinyObj = new TinyRenderObjectData(m_data->m_rgbColorBuffer, m_data->m_depthBuffer, &m_data->m_shadowBuffer, &m_data->m_segmentationMaskBuffer, bodyUniqueId, linkIndex);
				unsigned char* textureImage1 = 0;
				int textureWidth = 0;
				int textureHeight = 0;
				bool isCached = false;
				int textureIndex = -1;

				if (textures.size())
				{
					textureImage1 = textures[0].textureData1;
					textureWidth = textures[0].m_width;
					textureHeight = textures[0].m_height;
					isCached = textures[0].m_isCached;
					textureIndex = m_data->m_instancingRenderer->registerTexture(textureImage1, textureWidth, textureHeight);
				}

				{
					B3_PROFILE("registerMeshShape");

					tinyObj->registerMeshShape(&vertices[0].xyzw[0], vertices.size(), &indices[0], indices.size(), rgbaColor,
											   textureImage1, textureWidth, textureHeight);
				}
				visuals->m_renderObjects.push_back(tinyObj);

				{
					B3_PROFILE("m_instancingRenderer register");

					// register mesh to m_instancingRenderer too.

					int shapeIndex = m_data->m_instancingRenderer->registerShape(&vertices[0].xyzw[0], vertices.size(), &indices[0], indices.size(), B3_GL_TRIANGLES, textureIndex);
					double scaling[3] = {1, 1, 1};
					visuals->m_graphicsInstanceId = m_data->m_instancingRenderer->registerGraphicsInstance(shapeIndex, &visualShape.m_localVisualFrame[0], &visualShape.m_localVisualFrame[3], &visualShape.m_rgbaColor[0], scaling);

					int segmentationMask = bodyUniqueId + ((linkIndex + 1) << 24);
					{
						int graphicsIndex = visuals->m_graphicsInstanceId;
						if (graphicsIndex >= 0)
						{
							if (m_data->m_graphicsIndexToSegmentationMask.size() < (graphicsIndex + 1))
							{
								m_data->m_graphicsIndexToSegmentationMask.resize(graphicsIndex + 1);
							}
							m_data->m_graphicsIndexToSegmentationMask[graphicsIndex] = segmentationMask;
						}
					}

					m_data->m_instancingRenderer->writeTransforms();
				}
			}
			for (int i = 0; i < textures.size(); i++)
			{
				if (!textures[i].m_isCached)
				{
					free(textures[i].textureData1);
				}
			}
		}
	}
}