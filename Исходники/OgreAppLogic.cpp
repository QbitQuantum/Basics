void OgreAppLogic::updateClock1Canvas()
{
	Chrono chrono(true);
	Ogre::Canvas::Context* ctx = mCanvasTextureClock1->getContext();

	ctx->save();		
	ctx->clearRect(0, 0, 150, 150);
	ctx->strokeStyle(Ogre::ColourValue::Black);
	ctx->fillStyle(Ogre::ColourValue::White);
	ctx->fillRect(0, 0, 150, 150);
	ctx->translate(75, 75);
	ctx->scale(0.4f, 0.4f);
	ctx->rotate(-Ogre::Math::PI/2.0f);
	ctx->lineWidth(8);
	ctx->lineCap(Ogre::Canvas::LineCap_Round);

	// Hour marks
	ctx->save();
	for (float i=0; i<12; i++)
	{
		ctx->beginPath();
		ctx->rotate(Ogre::Math::PI/6.0f);
		ctx->moveTo(100, 0);
		ctx->lineTo(120, 0);
		ctx->stroke();
	}
	ctx->restore();

	// Minute marks
	ctx->save();
	ctx->lineWidth(5);
	for (int i=0; i<60; i++)
	{
		if (i%5!=0) 
		{
			ctx->beginPath();
			ctx->moveTo(117, 0);
			ctx->lineTo(120, 0);
			ctx->stroke();
		}
		ctx->rotate(Ogre::Math::PI/30);
	}
	ctx->restore();

	time_t now = time(NULL);
	struct tm * timeinfo;
	timeinfo = localtime(&now);
	int sec = timeinfo->tm_sec;
	int min = timeinfo->tm_min;
	int hr = timeinfo->tm_hour;
	hr = hr>=12 ? hr-12 : hr;

	ctx->fillStyle(Ogre::ColourValue::Black);

	// write Hours
	ctx->save();
	ctx->rotate( hr*(Ogre::Math::PI/6) + (Ogre::Math::PI/360)*min + (Ogre::Math::PI/21600)*sec );
	ctx->lineWidth(14);
	ctx->beginPath();
	ctx->moveTo(-20, 0);
	ctx->lineTo(80, 0);
	ctx->stroke();
	ctx->restore();

	// write Minutes
	ctx->save();
	ctx->rotate( (Ogre::Math::PI/30)*min + (Ogre::Math::PI/1800)*sec );
	ctx->lineWidth(10);
	ctx->beginPath();
	ctx->moveTo(-28, 0);
	ctx->lineTo(112, 0);
	ctx->stroke();
	ctx->restore();

	// Write seconds
	ctx->save();
	ctx->rotate(sec * Ogre::Math::PI/30);
	ctx->strokeStyle(Ogre::Canvas::ColourConverter::fromHexa("#D40000")); //red
	ctx->fillStyle(Ogre::Canvas::ColourConverter::fromHexa("#D40000")); //red
	ctx->lineWidth(6);
	ctx->beginPath();
	ctx->moveTo(-30, 0);
	ctx->lineTo(83, 0);
	ctx->stroke();
	ctx->beginPath();
	ctx->arc(0, 0, 10, 0, Ogre::Math::PI*2, true);
	ctx->fill();
	ctx->beginPath();
	ctx->arc(95, 0, 10, 0, Ogre::Math::PI*2, true);
	ctx->stroke();
	ctx->fillStyle(Ogre::Canvas::ColourConverter::fromHexa("#555")); //grey dark
	ctx->arc(0, 0, 3, 0, Ogre::Math::PI*2, true);
	ctx->fill();
	ctx->restore();

	ctx->beginPath();
	ctx->lineWidth(14);
	ctx->strokeStyle(Ogre::Canvas::ColourConverter::fromHexa("#325FA2")); //blue dark
	ctx->arc(0, 0, 142, 0, Ogre::Math::PI*2, true);
	ctx->stroke();

	ctx->restore();
	double renderTime = chrono.getTimeElapsed();
	mCanvasTextureClock1->uploadTexture();
	double uploadTime = chrono.getTimeElapsed()-renderTime;
	std::cout << "clock1 render: " << renderTime << "ms, upload: " << uploadTime << "ms" <<std::endl;
}