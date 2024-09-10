void DrawGame::CircleSprite::draw()
{
  // 显示圆形	
  ofPushMatrix();	 
  ofTranslate(ofPoint(X,Y)); 
  ofRotate(Rot,0,0,1); 
  ofScale(Size,Size,1.0f);   
  drawFill();  
  drawEdge();  
  ofPopMatrix();

  // 显示表情
  ofPushMatrix();
  ofTranslate(ofPoint(X,Y));
  ofRotate(Rot,0,0,1);	 
  ofScale(Size,Size,1.0f);  
  drawFace();
  ofPopMatrix();
}