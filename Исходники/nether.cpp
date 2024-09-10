void NETHER::draw_status(void)
{
    /* Clear the color and depth buffers. */ 
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	/* Draw buttons: */ 
	{
		List<STATUSBUTTON> l;
		STATUSBUTTON *b;
		float angle,cf;

		l.Instance(buttons);
		l.Rewind();
		while(l.Iterate(b)) {
			if (b->status>=-16) {
				angle=(float(b->status)*90.0)/16.0;
				cf=float((16-abs(b->status)))/16.0;
				glPushMatrix();
				glTranslatef(b->x,b->y,0);
				glRotatef(angle,0,1,0);

				/* Draw button: */ 
				glColor3f(b->r*cf,b->g*cf,b->b*cf);
				glutSolidBox(b->sx/2,b->sy/2,10.0);
				glTranslatef(0,0,11);

				glColor3f(1.0,1.0,1.0);
				if (b->text1[0]!=0) {
					if (b->text2[0]!=0) {
						glTranslatef(0,-12,0);
						scaledglprintf(0.1f,0.1f,b->text2);
						glTranslatef(0,17,0);
						scaledglprintf(0.1f,0.1f,b->text1);
					} else {
						glTranslatef(0,-3,0);
						scaledglprintf(0.1f,0.1f,b->text1);
					} /* if */ 
				} /* if */ 

				glPopMatrix();
			} /* if */ 
		} /* while */ 
	}

	glPushMatrix();
	switch(act_menu) {
	case GENERAL_MENU:
		{
			STATUSBUTTON *b;
			b=getbutton(STATUS_BUTTON);
			if (b!=0 && b->status==0) {
				statistics[0][7]=robots[0].Length();
				statistics[1][7]=robots[1].Length();

				glColor3f(0.5f,0.5f,1.0f);
				glTranslatef(70,356,0);
				scaledglprintf(0.1f,0.1f,"%i WARBASES %i",statistics[1][0],statistics[0][0]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%i ELECTR'S %i",statistics[1][1],statistics[0][1]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%i NUCLEAR  %i",statistics[1][2],statistics[0][2]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%i PHASERS  %i",statistics[1][3],statistics[0][3]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%i MISSILES %i",statistics[1][4],statistics[0][4]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%i  CANNON  %i",statistics[1][5],statistics[0][5]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%i CHASSIS  %i",statistics[1][6],statistics[0][6]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"%.2i ROBOTS %.2i",statistics[1][7],statistics[0][7]);

				glColor3f(0.0f,0.8f,0.0f);
				glTranslatef(0,-65,0);
				scaledglprintf(0.1f,0.1f,"GENERAL %.2i",resources[0][0]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"ELECTR' %.2i",resources[0][1]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"NUCLEAR %.2i",resources[0][2]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"PHASERS %.2i",resources[0][3]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"MISSILE %.2i",resources[0][4]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"CANNON  %.2i",resources[0][5]);
				glTranslatef(0,-18,0);
				scaledglprintf(0.1f,0.1f,"CHASSIS %.2i",resources[0][6]);
			} /* if */ 
		}
		break;
	case ROBOT_MENU:
	case DIRECTCONTROL_MENU:
		{
			STATUSBUTTON *b;

			b=getbutton(ROBOT1_BUTTON);
			if (b!=0 && b->status==0) {

				glTranslatef(70,140,0);
				glColor3f(1.0f,1.0f,0.0);
				scaledglprintf(0.1f,0.1f,"-ORDERS-");
				glColor3f(0.5f,0.5f,1.0f);
				switch(controlled->program) {
				case PROGRAM_STOPDEFEND:
					glTranslatef(0,-20,0);
					scaledglprintf(0.1f,0.1f,"STOP");
					glTranslatef(0,-18,0);
					scaledglprintf(0.1f,0.1f,"AND");
					glTranslatef(0,-18,0);
					scaledglprintf(0.1f,0.1f,"DEFEND");
					break;
				case PROGRAM_ADVANCE:
					glTranslatef(0,-20,0);
					scaledglprintf(0.1f,0.1f,"ADVANCE");
					glTranslatef(0,-18,0);
					scaledglprintf(0.1f,0.1f,"%.2i",controlled->program_parameter/2);
					glTranslatef(0,-18,0);
					scaledglprintf(0.1f,0.1f,"MILES");
					break;
				case PROGRAM_RETREAT:
					glTranslatef(0,-20,0);
					scaledglprintf(0.1f,0.1f,"RETREAT");
					glTranslatef(0,-18,0);
					scaledglprintf(0.1f,0.1f,"%.2i",controlled->program_parameter/2);
					glTranslatef(0,-18,0);
					scaledglprintf(0.1f,0.1f,"MILES");
					break;
				case PROGRAM_DESTROY:
					glTranslatef(0,-20,0);
					scaledglprintf(0.1f,0.1f,"DESTROY");
					switch(controlled->program_parameter) {
					case P_PARAM_ROBOTS:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ENEMY");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ROBOTS");
						break;
					case P_PARAM_WARBASES:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ENEMY");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"WARBASES");
						break;
					case P_PARAM_NFACTORIES:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"NEUTRAL");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"FACTORIES");
						break;
					case P_PARAM_EFACTORIES:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ENEMY");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"FACTORIES");
						break;
					} /* switch */ 
					break;
				case PROGRAM_CAPTURE:
					glTranslatef(0,-20,0);
					scaledglprintf(0.1f,0.1f,"CAPTURE");
					switch(controlled->program_parameter) {
					case P_PARAM_ROBOTS:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ENEMY");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ROBOTS");
						break;
					case P_PARAM_WARBASES:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ENEMY");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"WARBASES");
						break;
					case P_PARAM_NFACTORIES:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"NEUTRAL");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"FACTORIES");
						break;
					case P_PARAM_EFACTORIES:
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"ENEMY");
						glTranslatef(0,-18,0);
						scaledglprintf(0.1f,0.1f,"FACTORIES");
						break;
					} /* switch */ 
					break;
				} /* switch */ 

				glTranslatef(0,-44,0);
				glColor3f(1.0f,1.0f,0.0);
				scaledglprintf(0.1f,0.1f,"STRENGTH");
				glTranslatef(0,-18,0);
				glColor3f(1.0f,1.0f,1.0f);
				scaledglprintf(0.1f,0.1f,"%.3i%c",controlled->strength,'%');
			} /* if */ 
		}
		break;

	case COMBATMODE_MENU:
	case DIRECTCONTROL2_MENU:

		glTranslatef(70,40,0);
		glColor3f(1.0f,1.0f,0.0);
		scaledglprintf(0.1f,0.1f,"STRENGTH");
		glTranslatef(0,-18,0);
		glColor3f(1.0f,1.0f,1.0f);
		scaledglprintf(0.1f,0.1f,"%.3i%c",controlled->strength,'%');
		break;

	case ORDERS_MENU:
		{
			STATUSBUTTON *b;

			b=getbutton(ORDERS1_BUTTON);
			if (b!=0 && b->status==0) {
				glTranslatef(70,400,0);
				glColor3f(1.0f,1.0f,1.0f);
				scaledglprintf(0.1f,0.1f,"SELECT");
				glTranslatef(0,-20,0);
				scaledglprintf(0.1f,0.1f,"ORDERS");

				glTranslatef(0,-340,0);
				glColor3f(1.0f,1.0f,0.0);
				scaledglprintf(0.1f,0.1f,"STRENGTH");
				glTranslatef(0,-18,0);
				glColor3f(1.0f,1.0f,1.0f);
				scaledglprintf(0.1f,0.1f,"%.3i%c",controlled->strength,'%');
			} /* if */ 
		}
		break;

	case SELECTDISTANCE_MENU:
		{
			STATUSBUTTON *b;

			b=getbutton(ORDERS_BUTTON);
			if (b!=0 && b->status==0) {
				glTranslatef(70,300,0);
				glColor3f(0.5f,0.5f,1.0f);
				scaledglprintf(0.1f,0.1f,"SELECT");
				glTranslatef(0,-20,0);
				scaledglprintf(0.1f,0.1f,"DISTANCE");

				glColor3f(1.0f,1.0f,0.0);
				glTranslatef(0,-40,0);
				scaledglprintf(0.1f,0.1f,"%.2i MILES",controlled->program_parameter/2);

				glTranslatef(0,-200,0);
				glColor3f(1.0f,1.0f,0.0);
				scaledglprintf(0.1f,0.1f,"STRENGTH");
				glTranslatef(0,-18,0);
				glColor3f(1.0f,1.0f,1.0f);
				scaledglprintf(0.1f,0.1f,"%.3i%c",controlled->strength,'%');
			} /* if */ 
		}
		break;

	case TARGETD_MENU:
	case TARGETC_MENU:
		{
			STATUSBUTTON *b;

			b=getbutton(ORDERS_BUTTON);
			if (b!=0 && b->status==0) {
				glTranslatef(70,350,0);
				glColor3f(0.5f,0.5f,1.0f);
				scaledglprintf(0.1f,0.1f,"SELECT");
				glTranslatef(0,-20,0);
				scaledglprintf(0.1f,0.1f,"TARGET");

				glTranslatef(0,-290,0);
				glColor3f(1.0f,1.0f,0.0);
				scaledglprintf(0.1f,0.1f,"STRENGTH");
				glTranslatef(0,-18,0);
				glColor3f(1.0f,1.0f,1.0f);
				scaledglprintf(0.1f,0.1f,"%.3i%c",controlled->strength,'%');
			} /* if */ 
		}
		break;

	} /* switch */ 
	glPopMatrix();

} /* NETHER::draw_status */ 