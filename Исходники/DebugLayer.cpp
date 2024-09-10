	void DebugLayer::Render(void)
	{
		//Matrix tmp = this->projMat;
		//this->projMat = Matrix::CreateOrthographic(1.0f, 1.0f, 0.0f, 1.0f);
		/*this->renderer->PushMatrix(TRANSFORM_PROJECTION, Matrix::CreateOrthographicOffCenter(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));*/
		
		//create a projection so that the origin is at the top left of the physical screen
		//and the screen bounds are [0.0f, 1.0f]
		//Matrix proj = Matrix::CreateTranslation(-0.5f, 0.5f, 0.0f) * Matrix::CreateScale(2.0f, 2.0f, 1.0f); //* Matrix::CreateReflection(Plane(0.0f, 0.0f, 1.0f, 1.0f));
		//Matrix proj2 = Matrix::CreateOrthographicOffCenter(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		//proj.m[2][2] = 1.0f;

		Matrix proj = Matrix(Vector4( 2.0f,  0.0f,  0.0f,  0.0f), 
							 Vector4( 0.0f, -2.0f,  0.0f,  0.0f), 
							 Vector4( 0.0f,  0.0f,  1.0f,  0.0f), 
							 Vector4(-1.0f,  1.0f,  0.0f,  1.0f));

		this->renderer->SetTransform(TRANSFORM_PROJECTION, proj);
		this->renderer->BeginText();

		if(this->debugOptions.RenderFPS)
		{
			std::wstring FPSTxt = L"frame rate: ";
			FPSTxt = FPSTxt.append( std::to_wstring(timer->GetFramerate()) );

			this->renderer->RenderText(FPSTxt, 0.0f, 0.0f);
		}
		if(this->debugOptions.RenderRawMouseInput && this->inputController->GetCameraMode() == CAMERA_MODE_FPS_CAMERA)
		{
			std::wstring mouseText = L"Mouse Delta (";
			mouseText = mouseText.append( std::to_wstring(this->inputController->GetMouseDeltaX() ) );
			mouseText = mouseText.append( L" , " );
			mouseText = mouseText.append( std::to_wstring(this->inputController->GetMouseDeltaY() ) );
			mouseText = mouseText.append( L")" );

			this->renderer->RenderText(mouseText, 0.0f, 0.0625f);
		}
		if(this->debugOptions.RenderMatrices)
		{
			/*RECTF viewScreenRect;
			viewScreenRect.top = 0.0f;
			viewScreenRect.bottom = 
			this->debug_drawMatrix(this->Camera.GetView(), )*/
		}
		
		//render position
		std::wstring pos_text = L"Position (";
		pos_text.append(std::to_wstring(this->renderer->GetCamera().GetPos().x));
		pos_text.append(L", ");
		pos_text.append(std::to_wstring(this->renderer->GetCamera().GetPos().y));
		pos_text.append(L", ");
		pos_text.append(std::to_wstring(this->renderer->GetCamera().GetPos().z));
		pos_text.append(L")");
		this->renderer->RenderText(pos_text, 0.0f, 0.1f);

		this->renderer->EndText();

		/*this->projMat = tmp;
		this->SetTransform(TRANSFORM_PROJECTION, this->projMat);*/

		//this->console->Render();

		if(this->debugOptions.RenderAxes)
		{
			//axes should be transformed so that they appear in the upper lefthand corner of the screen
			//axes should take up one quarter of the screen when the orientation of the view is such that it is aligned
			//with the world x,y,z axes
			Matrix old_view = this->renderer->GetTransform(TRANSFORM_VIEW);
			Matrix rot = this->renderer->GetCamera().GetInvView();
			rot.Translation(Vector3(0.0f, 0.0f, 0.0f));

			Matrix transform = Matrix::CreateScale(0.125f, 0.125f, 0.125f) * rot * Matrix::CreateTranslation(0.1f, 0.6f, 0.5f);
			
			this->renderer->SetTransform(TRANSFORM_VIEW, Matrix::Identity());
			this->renderer->SetTransform(TRANSFORM_TYPE::TRANSFORM_WORLD, transform);
			
			//projecting in wrong direction in z axis for some reason
			Matrix proj = CreateOrthographicOffCenterLH(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 1.0f);
			/*Matrix proj = NBody::CreateOrthographicLH(
				2,//this->renderer->GetBBWidth(), 
				2,//this->renderer->GetBBHeight(),
				0.1f, 
				1.0f);*/

			this->renderer->SetTransform(TRANSFORM_PROJECTION, proj);
			this->renderer->BindShader(SHADER_TYPE_COLOR);

			//draw axes

			ID3D11Buffer *vBuff[] = {this->axesVBuffer};
			UINT stride[] = {sizeof(Vector4)};
			UINT offset[] = {0};

			this->renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			this->renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, vBuff, stride, offset);
			
			this->renderer->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			this->renderer->GetDeviceContext()->Draw(2, 0);

			this->renderer->SetColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
			this->renderer->GetDeviceContext()->Draw(2, 2);

			this->renderer->SetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
			this->renderer->GetDeviceContext()->Draw(2, 4);

			this->renderer->SetTransform(TRANSFORM_VIEW, old_view);
		}
	}