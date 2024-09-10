void InstanceLoader::_readGeometryEntity(shared_ptr<XmlNode> node, shared_ptr<Entity> entity)
{
	shared_ptr<XmlNode> child = node->getFirstChild();
	Vector3 scaleFactor(1,1,1);
	entity->setParent(entity->getParent());
	shared_ptr<PointSpecification> point;
	point = entity->getReferentialPoint();

	while (child )
	{
		if (child->getName() == "Position" || child->getName() == "Location")
		{
                        if (child->hasProperty("entity"))
                        {
                           string entityName = child->getProperty("entity");
                           //shared_ptr<InstanceSpecification> instance = MascaretApplication::getInstance()->getEnvironment()->getInstance(entityName);
                           shared_ptr<InstanceSpecification> instance = _environment->getInstance(entityName);
                           if (instance) 
                           {
                              shared_ptr<Entity> entPos = shared_dynamic_cast<Entity>(instance);
                              if (entPos) 
                              {
                                 entPos->addChild(entity);
                                 if (child->hasProperty("point"))
                                 {
                                    string pointName = child->getProperty("point");
                                    shared_ptr<PointSpecification> pt = entPos->getPoint(pointName);
                                    if (pt)
                                    {
                                       Vector3 pos = pt->getGlobalPosition();
                                       Vector3 ori = pt->getGlobalOrientation();
                                       point->setGlobalPosition(pos);
                                       point->setGlobalOrientation(ori);
                                    }
                                    else cerr << "Erreur : " << entPos->getName() << " has no point : " << pointName << " ! " << endl;
                                 }
                                 else
                                 {
                                    Vector3 pos = entPos->getGlobalPosition();
                                    Vector3 ori = entPos->getGlobalOrientation();
                                    point->setGlobalPosition(pos);
                                    point->setGlobalOrientation(ori);
                                 }
                              }
                              else cerr << " Error : " << entityName << " is not an entity ! " << endl;
                           }
                           else cerr << " Error : " << entityName << " not found ! " << endl;
                               
                        }
                        else
                        {
                        	point->setLocalPosition(PositionVectorFromNodeProperties(child));
                        }
		}
		else if (child->getName() == "Orientation")
		{
			if (child->hasProperty("angle"))
			{
				point->setLocalRotation(RotationVectorFromNodeProperties(child));
			}
			else
			{
				point->setLocalOrientation(OrientationVectorFromNodeProperties(child));
			}
		}

		else if (child->getName() == "Shape")
		{
			string url = child->getProperty("url") ;
			bool movable = false;
			bool recursive = false;
			if (child->hasProperty("movable")) child->getPropertyBoolean("movable", movable);
			if (child->hasProperty("recursive")) child->getPropertyBoolean("recursive", recursive);

			#if BOOST_FILESYSTEM_VERSION == 2
			url = fs::complete(url,_basedir).file_string();
			#else
			url = fs::complete(url,_basedir).string();
			#endif

			string shader="";
			if(child->hasProperty("shader"))
			{
				shader=child->getProperty("shader");
			}
			string name="shape";
			if(child->hasProperty("name"))
			{
				name=child->getProperty("name");
			}
			shared_ptr<ShapeSpecification> specif(MascaretApplication::getInstance()->getVRComponentFactory()->createShape(name,url,movable,recursive,shader));
			entity->getProperty(name)->addValue(specif);
			//entity->set_DEP_current(specif);
			entity->setActiveShape(name);
		}
		else if (child->getName() == "Shapes")
		{
			bool movable = false;
			if (child->hasProperty("movable"))
			{
				child->getPropertyBoolean("movable", movable);
			}
			bool recursive = false;
			if (child->hasProperty("recursive")) child->getPropertyBoolean("recursive", recursive);

			vector<string> urls;
			vector<double> distances;

			vector<shared_ptr<XmlNode> > shapeNodes=child->getChildNodesByName("Shape");
			for(size_t i=0;i<shapeNodes.size();i++)
			{
				shared_ptr<XmlNode> shapeNode=shapeNodes[i];
				string url = shapeNode->getProperty("url") ;

				#if BOOST_FILESYSTEM_VERSION == 2
				url = fs::complete(url,_basedir).file_string();
				#else
				url = fs::complete(url,_basedir).string();
				#endif

				if(url.empty())
				{
					cerr << "Fichier " << shapeNode->getProperty("url") << " non trouvé pour l'entity "<< entity->getName() << endl;
				}
				urls.push_back(url);
				double dist=0;
				if(shapeNode->hasProperty("dist"))
				{
					shapeNode->getPropertyReal("dist",dist);
				}
				distances.push_back(dist);
			}
			string name="shape";
			if(child->hasProperty("name"))
			{
				name=child->getProperty("name");
			}
			shared_ptr<ShapeSpecification> specif(MascaretApplication::getInstance()->getVRComponentFactory()->createShape(name,distances,urls,movable,recursive));
			entity->getProperty(name)->addValue(specif);
			//entity->set_DEP_current(specif);
			entity->setActiveShape(name);
		}
		else if (child->getName() == "Scale")
		{
			child->getPropertyReal("sx",scaleFactor.x);
			child->getPropertyReal("sy",scaleFactor.y);
			child->getPropertyReal("sz",scaleFactor.z);

		}
		else if (child->getName() == "Animation")
		{
			string name = child->getProperty("name");
			bool running=false;
                        if (child->hasProperty("running"))
                           child->getPropertyBoolean("running",running);

			string file = "";
			if(!child->getProperty("url").empty())
			{
				#if BOOST_FILESYSTEM_VERSION == 2
				file = fs::complete(child->getProperty("url"),_basedir).file_string();
				#else
				file = fs::complete(child->getProperty("url"),_basedir).string();
				#endif
			}

			shared_ptr<AnimationSpecification> animation(MascaretApplication::getInstance()->getVRComponentFactory()->createAnimation(name, file));
			entity->getProperty(name)->addValue(animation);
                        if (running) entity->playAnimation(name);
		}
		else if (child->getName() == "Sound")
		{
			string name = child->getProperty("name");

			#if BOOST_FILESYSTEM_VERSION == 2
			string file = fs::complete(child->getProperty("url"),_basedir).file_string();
			#else
			string file = fs::complete(child->getProperty("url"),_basedir).string();
			#endif

			double gain = 1.0;
			double minDist = 1.0;
			double maxDist = 100.0;
			child->getPropertyReal("gain",gain);
			child->getPropertyReal("minDistance",minDist);
			child->getPropertyReal("maxDistance",maxDist);

			shared_ptr<SoundSpecification> sound(MascaretApplication::getInstance()->getVRComponentFactory()->createSound(name, file, gain,minDist,maxDist));
			entity->getProperty(name)->addValue(sound);
			sound->attachTo(entity->getReferentialPoint());
		}
		else if (child->getName() == "Inline")
		{
			XmlParser parser;

			#if BOOST_FILESYSTEM_VERSION == 2
			if (parser.parseFile(fs::complete(child->getProperty("url"),_basedir).file_string() ))
			#else
			if (parser.parseFile(fs::complete(child->getProperty("url"),_basedir).string() ))
			#endif
			{
				shared_ptr<XmlNode> root = parser.getRoot();
				_readGeometryEntity(root, entity);
			}
		}
		else if (child->getName() == "InternalOrientationAxe")
		{
			//TODO: Pourquoi non utilisé ?
			Axe _front = AxeFromNodeProperty(child, "frontAxe");
			Axe _left = AxeFromNodeProperty(child, "leftAxe");
			Axe _above = AxeFromNodeProperty(child, "aboveAxe");
			/*point->setFront(_front);
			point->setLeft(_left);
			point->setAbove(_above);*/
		}
		else if (child->getName() == "InternalOrientationVector")
		{
			//TODO:
		}
		else if (child->getName() == "State")
		{
			// TODO: Maybe it's not normal to found a State here ?
			_initializeStateMachine(child, entity);
		}
		child = child->getNext();
	}
	/*
    if (entity->getActiveShape())
    {
        entity->getActiveShape()->setScale(scaleFactor);
    }	 */
}