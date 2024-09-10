	IVElement::IVElement(string ivfile, KthReal sc) {
		for(int i=0;i<3;i++){
			position[i]= 0.0f;
			orientation[i]=0.0f;
		}
		orientation[2]=1.0f;
		orientation[3]=0.0f;
		scale=sc;

		trans= new SoTranslation;
		rot = new SoRotation;
		sca = new SoScale();
		color = new SoMaterial;

		posVec = new SoSFVec3f;
		trans->translation.connectFrom(posVec);
		posVec->setValue((float)position[0],(float)position[1],(float)position[2]);

		rotVec = new SoSFRotation;
		rotVec->setValue(SbVec3f((float)orientation[0],(float)orientation[1],
				(float)orientation[2]),(float)orientation[3]);
		rot->rotation.connectFrom(rotVec);

		scaVec= new SoSFVec3f;
		scaVec->setValue((float)scale,(float)scale,(float)scale);
		sca->scaleFactor.connectFrom(scaVec);

		SoInput input;
		ivmodel = new SoSeparator;
		ivmodel->ref();
		ivmodel->addChild(sca);

		if(input.openFile(ivfile.c_str()))
			ivmodel->addChild(SoDB::readAll(&input));
		else
		{
			//ivmodel->addChild(new SoSphere());
			static const char *str[] = { 
				"#VRML V1.0 ascii\n",
				"DEF pointgoal Separator {\n",
				"  Separator {\n",
				"    MaterialBinding { value PER_PART }\n",
				"    Coordinate3 {\n",
				"      point [\n",
				"        0.0 0.0 0.0\n",
				"      ]\n",
				"    }\n",
				"    DrawStyle { pointSize 5 }\n",
				"    PointSet { }\n",
				"   }\n",
				"}\n",
				NULL
			};
			input.setStringArray(str);
			SoSeparator *sep = SoDB::readAll(&input);
			sep->ref();
			while (sep->getNumChildren() > 0)
			{
				ivmodel->addChild(sep->getChild(0));
				sep->removeChild(0);
			}
			sep->unref();
			
		}

		ivmodel->ref();

	}