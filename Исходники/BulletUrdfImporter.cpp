int BulletURDFImporter::convertLinkVisualShapes(int linkIndex, const char* pathPrefix, const btTransform& localInertiaFrame) const
{
    int graphicsIndex = -1;
    btAlignedObjectArray<GLInstanceVertex> vertices;
	btAlignedObjectArray<int> indices;
	btTransform startTrans; startTrans.setIdentity();
	btAlignedObjectArray<MyTexture> textures;
	
    const UrdfModel& model = m_data->m_urdfParser.getModel();
	UrdfLink* const* linkPtr = model.m_links.getAtIndex(linkIndex);
	if (linkPtr)
	{

		const UrdfLink* link = *linkPtr;
	
		for (int v = 0; v < link->m_visualArray.size();v++)
		{
			const UrdfVisual& vis = link->m_visualArray[v];
			btTransform childTrans = vis.m_linkLocalFrame;
			btHashString matName(vis.m_materialName.c_str());
			UrdfMaterial *const * matPtr = model.m_materials[matName];
			if (matPtr)
			{
				UrdfMaterial *const  mat = *matPtr;
				//printf("UrdfMaterial %s, rgba = %f,%f,%f,%f\n",mat->m_name.c_str(),mat->m_rgbaColor[0],mat->m_rgbaColor[1],mat->m_rgbaColor[2],mat->m_rgbaColor[3]);
				m_data->m_linkColors.insert(linkIndex,mat->m_rgbaColor);
			}
			convertURDFToVisualShapeInternal(&vis, pathPrefix, localInertiaFrame.inverse()*childTrans, vertices, indices,textures);
		
		
		}
	}
	if (vertices.size() && indices.size())
	{
//		graphicsIndex  = m_data->m_guiHelper->registerGraphicsShape(&vertices[0].xyzw[0], vertices.size(), &indices[0], indices.size());
		//graphicsIndex  = m_data->m_guiHelper->registerGraphicsShape(&vertices[0].xyzw[0], vertices.size(), &indices[0], indices.size());
		
		//CommonRenderInterface* renderer = m_data->m_guiHelper->getRenderInterface();
		
		if (1)
		{
			int textureIndex = -1;
			if (textures.size())
			{
				
				textureIndex = m_data->m_guiHelper->registerTexture(textures[0].textureData,textures[0].m_width,textures[0].m_height);
			}
			graphicsIndex = m_data->m_guiHelper->registerGraphicsShape(&vertices[0].xyzw[0], vertices.size(), &indices[0], indices.size(),B3_GL_TRIANGLES,textureIndex);
			
		}
	}
	
	//delete textures
	for (int i=0;i<textures.size();i++)
	{
		free( textures[i].textureData);
	}
	return graphicsIndex;
}