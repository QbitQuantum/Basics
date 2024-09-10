	//Public - getTranslation Matrix to translate other objects in calling gameObject coordinate system
	myEngine::Matrix4x4 GameObject::getTranslationMatrix()
	{
		Matrix4x4 translationMatrix = getPositionMatrix();
		translationMatrix.invert();
		return(translationMatrix);
	}