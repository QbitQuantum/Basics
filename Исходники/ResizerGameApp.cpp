void ResizerGameApp::draw()
{
	// clear out the window with black
	gl::clear( Color( .1, .1, .1 ) );
  gl::enableAlphaBlending();
  
  float tSecs = getElapsedSeconds();
  int tFrames = getElapsedFrames();
  int tWinW = getWindowWidth();
  int tWinH = getWindowHeight();
  
  int tMaxEnemies = 30;
  float tClosest = 1000;
  float tEnemySpeed = constrain(float(tFrames) / 1000.0 + 1.0, 1.0, 8.0);
  float tEnemyCurve = abs(sin(tFrames * .001)) * 270;
  float tEnemyDistance = 70;
  tEnemyDistance -= constrain(tFrames * .01, 20.0, 70.0);
  
  float tEnemyCurve2 = abs(cos(tFrames * .001)) * 270;
  float tEnemyDistance2 = 90;
  tEnemyDistance2 -= constrain(tFrames * .01, 15.0, 90.0);
  
  int tPlayerY = constrain(tWinW - 300, 0, tWinH);
  int tPlayerX = 70;
  Vec2f player = Vec2f(tPlayerX, tPlayerY);
  float health = 10;
  
  //  draw the score
	Vec2f tSize = Vec2f( tWinW, 100 );
	Font tFont = Font( "Arial", 12 );
  string txt = "Score: " + std::to_string(tFrames);
	TextBox tbox = TextBox().alignment( TextBox::RIGHT ).font( tFont ).size( Vec2i( tSize.x, TextBox::GROW ) ).text( txt );
  gl::color( .8, .8, .8 );
  gl::Texture tTextTexture = gl::Texture( tbox.render() );
  if( tTextTexture ) gl::draw( tTextTexture );
  cout << "Score: " << tFrames << "\n";
  
  
  
  //  draw enemies
  gl::color(.8, .1, .1);
  
  for (int i = 0; i < tMaxEnemies; ++i){
    float tX = ( 600 - ( tFrames % 600 ) * tEnemySpeed ) - ( sin(i * .5) * tEnemyCurve ) + 300;
    float tY = sin( tSecs ) * 20 + i * tEnemyDistance;
    float tX2 = tX - 50;
    float tY2 = sin( tSecs + .5) * 20 + i * tEnemyDistance;
    
    gl::drawVector( Vec3f(tX, tY, 0), Vec3f(tX2, tY2, 0), 10, 5 );
    
    float tDist = min( player.distance( Vec2f(tX2, tY2)), player.distance( Vec2f(tX, tY) ) );
    if ( tDist < tClosest ) tClosest = tDist;
  }
  
  // wave2
  if (tFrames > 2000) {
    for (int i = 0; i < tMaxEnemies; ++i){
      float tX = ( 700 - ( tFrames % 700 ) * tEnemySpeed ) - ( sin(i * .5) * tEnemyCurve2 ) + 300;
      float tY = cos( tSecs ) * 20 + i * tEnemyDistance2;
      float tX2 = tX - 50;
      float tY2 = cos( tSecs + .5) * 20 + i * tEnemyDistance2;
      tX += 300;
      tX2 += 300;
      
      gl::drawVector( Vec3f(tX, tY, 0), Vec3f(tX2, tY2, 0), 10, 5 );
      
      float tDist = min( player.distance( Vec2f(tX2, tY2)), player.distance( Vec2f(tX, tY) ) );
      if ( tDist < tClosest ) tClosest = tDist;
    }
  }
  
  // player color
  gl::color( .1, .8, .1 );
  
  //  animate player
  if (tFrames > 100) {
    health += sin(tSecs) * 3;
  }
  
  //  flash yellow if almost hit
  if ( tClosest < health + 5 ) {
    gl::color( 1, 1, 0 );
  }
  
  //  quit if hit
  if ( tClosest <= health) {
    quit();
  }
  
  //  draw the player
  gl::drawSolidCircle(player, health);
  
  
}