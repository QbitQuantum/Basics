FullScreenBlur::FullScreenBlur(Camera* camera, float blurFactor)
:_screenDistance(0.0f)
,_parentCamera(camera)
,_screenImage(NULL)
,_screenTexture(NULL)
,_screenQuad(NULL)
{
	if( camera )
	{
		World* world = WorldSingleton::Get();
		Vector2f size = camera->GetViewportSize();

		this->_screenImage = new Image(
			(unsigned int)(size.width*world->GetWindowSize().width),
			(unsigned int)(size.height*world->GetWindowSize().height),
			RGB8 );

		this->_screenTexture = new Texture(this->_screenImage);

		this->_screenDistance = camera->GetNearDraw()+1.0f;

		this->_screenQuad = new Object();
		this->_screenQuad->StartRecording();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		this->_screenQuad->StopRecording();
		this->_screenQuad->SetPosition(0.0f, 0.0f, -this->_screenDistance/Tan(this->_parentCamera->GetFieldOfView()/2.0f));
		this->_screenQuad->SetScale(this->_screenDistance, this->_screenDistance, 1.0f);
		this->_screenQuad->SetColor(Object::Diffuse, Vector4f(1.0f, 1.0f, 1.0f, blurFactor));
		this->_screenQuad->SetColor(Object::Emission, Vector4f(1.0f, 1.0f, 1.0f, 0.0f));
		this->_screenQuad->SetTexture(this->_screenTexture);
		this->_screenQuad->SetRenderOrder(Entity::Foreground);
		this->_screenQuad->Parent(camera);
	}
}