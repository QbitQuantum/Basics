void M2Object::DrawSSAO( const mat4& world, const mat4& view, const mat4& proj ) {		
	/*if (!animated) {


	}
	else*/ {		
		static size_t fps = 0;
		mat4* frameMatrices = NULL;

		M2Mesh* mesh = Owner_->mesh_;

		renderer->resetToDefaults();
		Direct3D11Renderer* Dx11R = (Direct3D11Renderer*)renderer;

		if (animGeom)	
		{
			std::vector<mat4> temp;

			temp.resize(header.nBones);
			for (size_t i=0; i<header.nBones; i++) 
				temp[i] = bones[i].rdmat;

			//float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
			//renderer->clear(true, true, false, ClearColor, 1.f);
			int num =  numPass;	
			//num = 2;
			noVec4 ocolor, ecolor;
			for (int i = 0; i < num; i++)						
			{
				const RenderData& rd = render_data[i];

				if (!UpdateColors(rd.colorIndex, rd.opacity, rd.unlit, ocolor, ecolor))
					continue;

				renderer->reset();	
				renderer->setShader(rd.shader);
				renderer->setVertexFormat(rd.vf);
				renderer->setVertexBuffer(0, rd.vb);
				renderer->setIndexBuffer(rd.ib);								
				
				renderer->setShaderConstant4x4f("g_mWorld", world);
				//renderer->setShaderConstant4x4f("g_mViewProj", view * proj);
				renderer->setShaderConstant4x4f("g_mView", view);

				//mat4 invView = transpose(view);
				//renderer->setShaderConstant4x4f("InvView", invView);
				//renderer->setShaderConstant3f("g_localEye", invView.getTrans());
				renderer->setShaderConstant4x4f("g_mWorldViewProjection",  world *view * proj);
				//renderer->setShaderConstant4x4f("View", view);
				//renderer->setShaderConstant4x4f("Projection", proj);	
				renderer->setShaderConstantArray4x4f("g_matrices", &temp[0], header.nBones);				

				renderer->setTexture("g_txDiffuse", rd.baseTex);
				renderer->setSamplerState("g_samLinear", render_data[0].diffuseSampler);

				renderer->apply();
								

				//ID3D11ShaderResourceView* srv = Dx11R->getTextureSRV(rd.baseTex);
				//D3D11Context()->PSSetShaderResources(0, 1, &srv);				
								
				ID3D11ShaderResourceView* aoSRV[] ={ GetApp()->SSAORender_->GetAOSRV() };
				D3D11Context()->PSSetShaderResources(1, 1, aoSRV);				
				
				//renderer->setShaderConstantArray4x4f("g_matrices", &temp[0], header.nBones);				
				renderer->drawElements(rd.prim, rd.startIndex, rd.endIndex, 0, rd.vertexEnd);															
				
				
			}
		}
		else 
		{
			noVec4 ocolor, ecolor;
			for (int i = 0; i < numPass; i++)
			{
				const RenderData& rd = render_data[i];

				if (!UpdateColors(rd.colorIndex, rd.opacity, rd.unlit, ocolor, ecolor))
					continue;
				
				renderer->reset();	
				renderer->setShader(rd.shader);
				renderer->setVertexFormat(rd.vf);
				renderer->setVertexBuffer(0, rd.vb);
				renderer->setIndexBuffer(rd.ib);								

				renderer->setShaderConstant4x4f("World", world);
				//renderer->setShaderConstant4x4f("g_mViewProj", view * proj);
				renderer->setShaderConstant4x4f("View", view);

				//mat4 invView = transpose(view);
				//renderer->setShaderConstant4x4f("InvView", invView);
				//renderer->setShaderConstant3f("g_localEye", invView.getTrans());
				renderer->setShaderConstant4x4f("Projection",  proj);

				renderer->setTexture("g_txDiffuse", rd.baseTex);
				renderer->setSamplerState("g_samLinear", render_data[0].diffuseSampler);

				renderer->apply();
				
				//ID3D11ShaderResourceView* srv = Dx11R->getTextureSRV(rd.baseTex);
				//D3D11Context()->PSSetShaderResources(0, 1, &srv);										

				ID3D11ShaderResourceView* aoSRV[] ={ GetApp()->SSAORender_->GetAOSRV() };
				D3D11Context()->PSSetShaderResources(1, 1, aoSRV);				

				renderer->drawElements(rd.prim, rd.startIndex, rd.endIndex, 0, rd.vertexEnd);											
			}
		}
	}
}