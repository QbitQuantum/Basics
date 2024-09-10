void RodSoundApp::draw() {
  while (running &&
//         app::getElapsedSeconds() - tAtLastDraw < 1.0/app::getFrameRate() &&
         fe.nextTimestep(c) > 1.0 / (real) SampleRate) {
    update();
  }
  tAtLastDraw = app::getElapsedSeconds();
  
  PROFILER_START("Draw");
  
	// Clear out the window with grey
	gl::clear(Color(0.45, 0.45, 0.5));
  
  // Enable alpha blending and depth testing
  gl::enableAlphaBlending();
	gl::enableDepthRead(true);
	gl::enableDepthWrite(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  // Draw framerate counter
  gl::setMatricesWindow(getWindowSize());
  std::stringstream ss;
  ss << getAverageFps();
  gl::drawStringRight(ss.str(),
                      Vec2c(getWindowWidth()-toPixels(10), getWindowHeight()-toPixels(20)),
                      Color(0.0, 0.0, 0.0),
                      Font("Arial", toPixels(12)));
  
  // Set projection/modelview matrices
  gl::setMatrices(cam);
  
  // Draw the rod and the normal of the bishop frame
  for(int i=0; i<r->numEdges(); i++) {
    Vec3c p0 = EtoC(r->cur().POS(i));
    Vec3c p1 = EtoC(r->cur().POS(i+1));
    gl::drawLine(p0, p1);
    gl::color(1.0, 1.0, 0.0);
    gl::lineWidth(1.0);
    Vec3c u = EtoC(r->cur().u[i]);
    gl::drawLine((p0+p1)/2.0, (p0+p1)/2.0+u*(p1-p0).length()*2.0);
  }
  
  m.apply();
  
  l->setDiffuse(Color::white());
  l->setAmbient(Color::white());
  l->setPosition(Vec3c(0.0, 50.0, 0.0));
  l->enable();
  
  diffuseProg.bind();
  for (int i=0; i<r->numCPs(); i++) {
    gl::pushModelView();
    gl::translate(EtoC(r->cur().POS(i)));
    spheredl->draw();
    gl::popModelView();
  }
  diffuseProg.unbind();
  
  rodProg.bind();

  floorTex.enableAndBind();
  gl::draw(floor);
  floorTex.disable();
  
  rodProg.unbind();
  
  // Draw rod edges
  rodProg.bind();
  rodTex.enableAndBind();
  for (int i=0; i<r->numEdges(); i++) {
    gl::pushModelView();
    Vec3c v = EtoC(r->cur().edge(i).normalized());
    
    gl::translate(EtoC(r->cur().POS(i)));
    Quaternion<real> q(Vec3c(0.0, 1.0, 0.0), v);
    real angle = acos(std::max((real)-1.0, std::min((real)1.0, (q*Vec3c(-1.0, 0.0, 0.0)).dot(EtoC(r->cur().u[i])))));
    if ((q*Vec3c(-1.0, 0.0, 0.0)).dot(EtoC(r->cur().v(i))) > 0.0) angle = -angle;
    gl::rotate(Quaternion<real>(v, angle));
    gl::rotate(q);
    gl::rotate(Vec3c(0.0, r->cur().rot(i)*180.0/constants::pi, 0.0));
    gl::scale(1.0, r->cur().edgeLength(i), 1.0);
    cylinderdl->draw();
    gl::popModelView();
  }
  rodTex.unbind();
  rodProg.unbind();

  for (RodEnergy* e : energies) {
    e->draw(c.timestep());
  }
  integrator->draw();
 
  fe.record(c);
  
  PROFILER_STOP("Draw");
}