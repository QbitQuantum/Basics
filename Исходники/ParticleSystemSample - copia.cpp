int Main(void)
{
  // Load resources
  texsmallball  = CORE_LoadBmp("data/tyrian_ball.32.bmp"      , false);
  texcursor  = CORE_LoadBmp("data/cursor.bmp", false);
  
  initCursor();

  initParticlePool(MAX_PARTICLES);

  //checking pool
  //while(particlePool.current)
  //{
	 // particlePool.current=particlePool.current->next;
  //}
  //particlePool.current = particlePool.head->next;

  initEmmiter();

  //for (int i = 0; i < NUM_PARTICLES; i++)
  //{
		//float radius;
		//radius = 8.f;
		//particle[i]=particlePool.current;
		//particlePool.current=particlePool.current->next;
		//particle[i]->radius = radius;
		//particle[i]->mass = 1.f;
		//particle[i]->index = texsmallball;
		//particle[i]->pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(radius, SCR_HEIGHT-radius));
		//particle[i]->vel = vmake(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
  //}


  // Set up rendering
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  DWORD start_tick= GetTickCount();

  while (!SYS_GottaQuit())
  {
    // Render
    glClear( GL_COLOR_BUFFER_BIT );
		
	CORE_RenderCenteredSprite(cursor->pos, 
				vmake(cursor->radius , cursor->radius ), cursor->index);

	//fixed substep
	float dt =1.0f/(substep*FPS);
	//adaptive substep
	//DWORD elapsed_ticks= GetTickCount()- start_tick;
	//float elapsed_dt= elapsed_ticks/TICKS_PER_SECOND;

	//float edt_dt = elapsed_dt/dt;
	//int ite = (int)edt_dt;
	//float lastdt= edt_dt - ite;

	tVector forces=vmake(0,-100.0f);

//	for( int i=0; i < ite; i++)
		updateEmitter( myEmmiter, forces, dt);

//	updateEmitter( myEmmiter, forces, lastdt);
	applyDeflectors(myEmmiter);

	renderParticles(myEmmiter);

	SYS_Show();

	start_tick= GetTickCount();
    // Keypress!
    if (SYS_KeyPressed('O'))
    {
		if(cursor)cursor->pos.x-=1.0f;;
	}
    if (SYS_KeyPressed('P'))
    {
		if(cursor)cursor->pos.x+=1.0f;;
	}
    if (SYS_KeyPressed('Q'))
    {
		if(cursor)cursor->pos.y+=1.0f;;
	}
    if (SYS_KeyPressed('A'))
    {
		if(cursor)cursor->pos.y-=1.0f;;
	}

    if (0)//SYS_KeyPressed('I'))
    {
		//start single ball at random
		float radius=16.f;
		GLuint texBall=texsmallball;
		float mass=1.0f;
		int index=(int)CORE_FRand(0, MAX_PARTICLES-1);

		//particle[index]->mass = mass;
		//particle[index]->index = texBall;
		//particle[index]->radius = radius;
	 //   particle[index]->pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(SCR_HEIGHT*.5f, SCR_HEIGHT-radius));
		//particle[index]->vel = vmake(0, 10);
	}
    if (0)//SYS_KeyPressed(' '))
    {
		//give an impulse to all balss

//      for (int i = 0; i < MAX_PARTICLES; i++)
//	  {
          //if (fabs(particle[i]->vel.x) < 0.1f)
          //  particle[i]->vel.x = CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED);
          //particle[i]->vel.y = CORE_FRand(0, JUMP_SPEED);
//	  }
    }
    if (0)//SYS_KeyPressed(VK_CONTROL))
    {
	  //reset all
		glClear( GL_COLOR_BUFFER_BIT );

  //    for (int i = 0; i < MAX_PARTICLES; i++)
	 // {
		//float radius=particle[i]->radius;
		//particle[i]->pos = vmake(CORE_FRand(radius, SCR_WIDTH-radius), CORE_FRand(radius, SCR_HEIGHT-radius));
		//particle[i]->vel = vmake(0, 10);
	 // }
	  SYS_Show();
	}
    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  CORE_UnloadBmp(texsmallball);
  CORE_UnloadBmp(texcursor);

  destroyEmmmiter(myEmmiter);
  destroyParticlePool();
  destroyCursor();

  return 0;
}