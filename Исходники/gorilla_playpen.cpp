  App() : mTimer(0), mTimer2(0), mNextUpdate(0)
  {
   
   _makeOgre();
   _makeOIS();

  // Create Silverback and load in dejavu
  mSilverback = new Gorilla::Silverback();
  mSilverback->loadAtlas("dejavu");
  mScreen = mSilverback->createScreen(mViewport, "dejavu");
  mScreen->setOrientation(Ogre::OR_DEGREE_270);
  Ogre::Real vpW = mScreen->getWidth(), vpH = mScreen->getHeight();

  // Create our drawing layer
  mLayer = mScreen->createLayer(0);
  rect = mLayer->createRectangle(0,0, vpW, vpH);
  rect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(98,0,63), Gorilla::rgb(255,180,174));
  
  markup = mLayer->createMarkupText(9,5,5, "%@24%A Haiku\n%@14%Written by Betajaen%@9%\nSo many to choose from\nPretty typefaces on Ogre screen\nTime to update Git");
  
  caption = mLayer->createCaption(9, vpW - 55, 5, "9");
  caption->width(50);
  caption->align(Gorilla::TextAlign_Right);

  caption = mLayer->createCaption(14, vpW - 55, 18, "14");
  caption->width(50);
  caption->align(Gorilla::TextAlign_Right);

  caption = mLayer->createCaption(24, vpW - 55, 33, "24");
  caption->width(50);
  caption->align(Gorilla::TextAlign_Right);
  }