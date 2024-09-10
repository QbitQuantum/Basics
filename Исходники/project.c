void display(void)
{

  // Clear the screen____________________________________


if((cam.x < goalx + 2 && cam.x > goalx - 2) && (cam.z < goalz + 2 && cam.z > goalz - 2))
{
	
	third_person = true;

}
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



  // Variables
    
  mat4 total, modelView, camMatrix;
  GLfloat t =(GLfloat)glutGet(GLUT_ELAPSED_TIME)/1000; //Scale with constant to make animation slower.
 


  //Read input_____________________________________________
  if (third_person)
    {

	goal_found = true;

      if (glutKeyIsDown('t'))
	{ 
	  third_person = false;  
	}
  
  vec3 pos =  {200, 200, 150};// SetVector(keyx,keyy,keyz);
      //Mouse control_____________________________________________
      //fmin and fmax doesn't really make sense but looks good. 
      GLfloat mousexlocal = 0;
      GLfloat mouseylocal = 0;

      if (mousex < 350 ||  mousex > 250)
	{
	  mousexlocal = 300-mousex;
	}
      else
	{
	  mousexlocal = 0;
	}

      deltaphi = deltaphi + deltaphi*-mousexlocal;
      deltaphi = fmin(0.0001,deltaphi);
      deltaphi = fmax(deltaphi,2 * PI - 0.0001);
      forward = MultVec3(Ry(deltaphi*-mousexlocal), forward);

      vec3 crossvec = CrossProduct(forward,up);

      if (mousey < 350 || mousey > 250)
	{
	  mouseylocal = 300-mousey;
	}  
      else
	{
	  mouseylocal = 0;
	}

      deltatheta = deltatheta + deltatheta* -mouseylocal;
      deltatheta = fmin(0.0001,deltatheta);
      deltatheta = fmax(deltatheta,2*PI - 0.0001);
      forward = MultVec3( ArbRotate(crossvec,deltatheta*-mouseylocal), forward);

      //Create camera matrix_____________________________________________
      camMatrix = lookAtv(pos,VectorAdd(forward,pos),up);
    }




// FIRST PERSON VIEW --------------------------------------------------------
  else
    {
      
      vec3 moveVec;
      
      if (glutKeyIsDown('w')) // forwards, obviously
	{
	  vec3 oldcam = cam; //Save old position to check if its legal.
	  moveVec = ScalarMult(VectorSub(cam, SetVector(lookAtPoint.x, cam.y, lookAtPoint.z)), 0.1); // VectorSub makes a vector in the direction we're looking.
	  cam = VectorSub(cam, moveVec); // The new camera position is the old camera position + the move vector
	  cam.y = getHeight(&ttex,cam.x, cam.z)+2; // Get the correct height from the new position  
	  GLfloat maze_height = getHeight(&ttexm, cam.x, cam.z); // Get the height of the maze at the new (possible) camera position
	  GLfloat ground_height = getHeight(&ttex, cam.x, cam.z); // Get the height of the ground at the new (possible) camera position


	  //Check if the new position is legal
	    if ((ground_height - maze_height) < ground_height) // If 0, shouldn't move ever: OK!
						   // When does it start to move??
	      {
		printf("woot");
		cam = oldcam;
	      }
	}
       else if (glutKeyIsDown('t'))
	 {
	   third_person = true;
	 }

       GLfloat mousexlocal = 0;
      GLfloat mouseylocal = 0;

      if (mousex < 350 ||  mousex > 250)
	{
	  mousexlocal = 300-mousex;
	}
      else
	{
	  mousexlocal = 0;
	}

      deltaphi = deltaphi + deltaphi*-mousexlocal;
      deltaphi = fmin(0.0001,deltaphi);
      deltaphi = fmax(deltaphi,2 * PI - 0.0001);
      forward = MultVec3(Ry(deltaphi*-mousexlocal), forward);

      vec3 crossvec = CrossProduct(forward,up);

      if (mousey < 350 || mousey > 250)
	{
	  mouseylocal = 300-mousey;
	}  
      else
	{
	  mouseylocal = 0;
	}

      deltatheta = deltatheta + deltatheta* -mouseylocal;
      deltatheta = fmin(0.0001,deltatheta);
      deltatheta = fmax(deltatheta,2*PI - 0.0001);
      forward = MultVec3( ArbRotate(crossvec,deltatheta*-mouseylocal), forward);
      lookAtPoint = VectorAdd(forward,cam);
      //Create camera matrix_____________________________________________
      camMatrix = lookAtv(cam,lookAtPoint,up);

    }

  
  // --------------------------------------------------------//
  // SKYBOX
  // --------------------------------------------------------//

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glUseProgram(programSky);
	glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, tex2);
	trans = T(0.0, 0.0, 0.0);

       	rot = Rx(0);
	total = Mult(trans, rot);
       	glUniformMatrix4fv(glGetUniformLocation(programSky, "mdlMatrix"), 1, GL_TRUE, total.m);

	lookSky = camMatrix;

	lookSky.m[3] = 0;
	lookSky.m[7] = 0;
	lookSky.m[11] = 0;

	glUniformMatrix4fv(glGetUniformLocation(programSky, "lookMatrix"), 1, GL_TRUE, lookSky.m);
	glUniformMatrix4fv(glGetUniformLocation(programSky, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);

	glUniform1i(glGetUniformLocation(programSky, "texUnit2"), 2); // Texture unit 2
	DrawModel(skybox, programSky, "in_Position", NULL, "inTexCoord");


	glUseProgram(program);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//------------------------------------------------------//
	//------------------------------------------------------//



 
  modelView = IdentityMatrix();
  total = Mult(camMatrix, modelView);

  glActiveTexture(GL_TEXTURE1);
  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
  glBindTexture(GL_TEXTURE_2D, tex2);		// Bind Our Texture tex1
  DrawModel(tm, program,"inPosition", "inNormal", "inTexCoord");

  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 0, GL_TRUE, total.m);
  glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
  DrawModel(mm, program,"inPosition", "inNormal", "inTexCoord");

  GLfloat y = getHeight(&ttexm, 200, 147);
  mat4 trans = T(goalx, 2, goalz);
  mat4 scale = S(1, 1, 1);
 total = Mult(total, trans);
 total = Mult(total, scale);

 
 if (goal_found)
{
	char* string = "GOOD JOB!! You won :D";
	sfDrawString(100, 100, string);
	//while(true){};
}



  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
  glBindTexture(GL_TEXTURE_2D, tex3);		// Bind Our Texture tex1


  DrawModel(goal, program,"inPosition", "inNormal", "inTexCoord");


  



  printError("display 2");
	
  glutSwapBuffers();
  printf("x %f\n", cam.x);
  printf("y %f\n", cam.y);
  printf("z %f\n", cam.z);
  
  /* if ( (cam.x < 95) && (cam.x > 85) && */
  /*      (cam.z < 85) && (cam.z > 75)) */

  
}