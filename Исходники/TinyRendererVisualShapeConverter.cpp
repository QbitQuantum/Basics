void TinyRendererVisualShapeConverter::convertVisualShapes(int linkIndex, const char* pathPrefix, const btTransform& localInertiaFrame, const UrdfModel& model, class btCollisionObject* colObj)
{
    
	
	UrdfLink* const* linkPtr = model.m_links.getAtIndex(linkIndex);
	if (linkPtr)
	{

		const UrdfLink* link = *linkPtr;
	
		for (int v = 0; v < link->m_visualArray.size();v++)
		{
			btAlignedObjectArray<MyTexture2> textures;
			btAlignedObjectArray<GLInstanceVertex> vertices;
			btAlignedObjectArray<int> indices;
			btTransform startTrans; startTrans.setIdentity();
			int graphicsIndex = -1;

			const UrdfVisual& vis = link->m_visualArray[v];
			btTransform childTrans = vis.m_linkLocalFrame;
			btHashString matName(vis.m_materialName.c_str());
			UrdfMaterial *const * matPtr = model.m_materials[matName];
            
            float rgbaColor[4] = {1,1,1,1};
            
			if (matPtr)
			{
				UrdfMaterial *const  mat = *matPtr;
                for (int i=0;i<4;i++)
                    rgbaColor[i] = mat->m_rgbaColor[i];
				//printf("UrdfMaterial %s, rgba = %f,%f,%f,%f\n",mat->m_name.c_str(),mat->m_rgbaColor[0],mat->m_rgbaColor[1],mat->m_rgbaColor[2],mat->m_rgbaColor[3]);
				//m_data->m_linkColors.insert(linkIndex,mat->m_rgbaColor);
			}
			
			TinyRendererObjectArray** visualsPtr = m_data->m_swRenderInstances[colObj];
            if (visualsPtr==0)
            {
                m_data->m_swRenderInstances.insert(colObj,new TinyRendererObjectArray);
            }
            visualsPtr = m_data->m_swRenderInstances[colObj];
            btAssert(visualsPtr);
            TinyRendererObjectArray* visuals = *visualsPtr;
            
			convertURDFToVisualShape(&vis, pathPrefix, localInertiaFrame.inverse()*childTrans, vertices, indices,textures);

            if (vertices.size() && indices.size())
            {
                TinyRenderObjectData* tinyObj = new TinyRenderObjectData(m_data->m_rgbColorBuffer,m_data->m_depthBuffer);
				unsigned char* textureImage=0;
				int textureWidth=0;
				int textureHeight=0;
				if (textures.size())
				{
					textureImage = textures[0].textureData;
					textureWidth = textures[0].m_width;
					textureHeight = textures[0].m_height;
				}
				
                tinyObj->registerMeshShape(&vertices[0].xyzw[0],vertices.size(),&indices[0],indices.size(),rgbaColor,
										   textureImage,textureWidth,textureHeight);
                visuals->m_renderObjects.push_back(tinyObj);
            }
			for (int i=0;i<textures.size();i++)
			{
				delete textures[i].textureData;
			}
		}
	}
}