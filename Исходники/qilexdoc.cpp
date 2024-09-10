int QilexDoc::doc_insert_kinematic_chain(Rchain *kineengine, SoSeparator *kinechain)
{
   int error = 0;
   int i;

   SbVec3f joinax;

   float joinangle;
   
   SbName joints[] = {"joint1", "joint2", "joint3", "joint4","joint5", "joint6",
                   "joint7", "joint8", "joint9", "joint10","joint11", "joint12",
                   "joint13", "joint14", "joint15", "joint16","joint17", "joint18",
                   "joint19", "joint20", "joint21", "joint22","joint23", "joint24",  };
   
   SoEngineList compR(kineengine->dof);
   SoNodeList Rots(kineengine->dof);

   SoSearchAction lookingforjoints;
   SoTransform *pjoint = new SoTransform;

      // Identifie the rotations and assing the job
   i = 0;

   while (i < kineengine->dof && error == 0)
   {
      lookingforjoints.setName(joints[i]);
      lookingforjoints.setType(SoTransform::getClassTypeId());
      lookingforjoints.setInterest(SoSearchAction::FIRST);
      lookingforjoints.apply(kinechain);

      //  assert(lookingforjoints.getPath() != NULL);
      SoNode * pnode = lookingforjoints.getPath()->getTail();;

      pjoint = (SoTransform *) pnode;

      if(NULL != pjoint)
      {
         Rots.append((SoTransform *) pjoint);
         compR.append(new SoQtComposeRotation);
         // cal comprobar si l'articulació es de rotació o translació: arreglar...
         ((SoTransform *) Rots[i])->rotation.getValue(joinax, joinangle);
         ((SoQtComposeRotation *) compR[i])->axis.setValue(joinax);

         ((SoTransform *) Rots[i])->rotation.connectFrom(&((SoQtComposeRotation *) compR[i])->rotation);
      }
      else
      {
         error = 5; // not a valid Model3d file
      }
      i++ ;
   }

   if (error == 0)
   {
      SoSeparator *axisworld = new SoSeparator;
      axisworld->unrefNoDelete();
		
		SoCoordinateAxis *AxisW   = new SoCoordinateAxis();
	   AxisW->fNDivision = 1;
      AxisW->fDivisionLength = 200;
		axisworld->addChild(AxisW);

      //kinechain->insertChild(AxisW,1);
      view->addNoColObject(axisworld);
		
    /*  lookingforjoints.setName("tool");
      lookingforjoints.setType(SoSeparator::getClassTypeId());
      lookingforjoints.setInterest(SoSearchAction::FIRST);
      lookingforjoints.apply(kinechain);

      if(lookingforjoints.getPath() != NULL)
      {
         SoNode * pnode = lookingforjoints.getPath()->getTail();;
      	
			SoCoordinateAxis *AxisT   = new SoCoordinateAxis();
			AxisT->fNDivision = 1;
      	AxisT->fDivisionLength = 200;

			SoSeparator *axistool = new SoSeparator;
         axistool->ref();
         axistool = (SoSeparator *) pnode;
         axistool->addChild(AxisT);
			view->addNoColObject(axistool);			
      }
      */ 
      panel_control *panel = new panel_control(0, "Panel", kineengine);

      for (int i = 0; i < kineengine->dof; i++)
      {
         // connect(panel->ldial[i], SIGNAL(valueChange(double)),((SoQtComposeRotation *) compR[i]), SLOT(setValue_angle(double)));
         connect(panel->ldial[i], SIGNAL(valueChange(double)),&panel->kinechain->list_plug[i], SLOT(setValue(double)));
         connect(&panel->kinechain->list_plug[i], SIGNAL(valueChanged(double)),((SoQtComposeRotation *) compR[i]), SLOT(setValue_angle(double)));
         connect(&panel->kinechain->list_plug[i], SIGNAL(valueChanged(double)),panel->ldial[i], SLOT(setValue(double)));
      }

      view->addRobotCell(kinechain);

      panel->show();
      panel->update_limits();
      //panel->kinechain->setconsole_mode(true); Ja estava comentada
      panel->kinechain->setconsole_mode(false);
      panel->kinechain->do_ready();
		connect(view, SIGNAL(pick_point(Rhmatrix)),panel, SLOT(move_pickpoint(Rhmatrix )));
      //panel->kinechain->setconsole_mode(false); Ja estava comentada
   }