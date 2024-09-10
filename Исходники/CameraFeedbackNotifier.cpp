	void CCameraFeedbackNotifier::calculateEnemyPosition(Vector3 vPosEnemy) { 
		//Obtengo la posición del enemigo
		Ogre::Vector3 vEnemyPos = vPosEnemy;
		//Obtengo mi posición (entidad a la que han dañado)
		Ogre::Vector3 vMyPos = this->_entity->getPosition();

		//Obtengo el vector en el que estoy mirando, y me quedo sólo en el plano horizontal (quitando la altura)
		Vector3 vMyDirVision = _entity->getOrientation()*Vector3::NEGATIVE_UNIT_Z;
		vMyDirVision = Vector3(vMyDirVision.x,0,vMyDirVision.z);
		//Obtengo el vector desde el enemigo a mi posición; y me quedo sólo con el plano horizontal (quitando la altura)
		Vector3 vEnemyDirVision = vPosEnemy - vMyPos;
		vEnemyDirVision = Vector3(vEnemyDirVision.x, 0, vEnemyDirVision.z);

		//Ángulo entre ambos vectores
		Ogre::Radian rad = vMyDirVision.angleBetween(vEnemyDirVision);
		//Convierto los radianes a float porque en el mensaje mando float
		float fRadianes = (float)rad.valueRadians();

		//Cambio de sistema de coordenadas para tener la posición del enemigo respecto 
		//al jugador. Antonio el crack matemático! ^^
		Matrix4 mat;
		mat.makeTransform(_entity->getPosition(),Vector3::UNIT_SCALE,_entity->getOrientation());
		mat.inverse();
		Vector3 vec = mat * vPosEnemy; //este vector es la posicion del enemigo respecto a mi
		if (vec.x > 0) 
		{
			//El enemigo está a la derecha, así que tengo que multiplicar
			//por -1 para que se oriente bien la flecha de daño
			fRadianes *= -1.0f;
		}

		//Mando el mensaje
		std::shared_ptr<Logic::CMessageImpact> impact = std::make_shared<Logic::CMessageImpact>();
		impact->setDirectionImpact(fRadianes);							 
		_entity->emitMessage(impact);
	}