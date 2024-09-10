void cDSRoomLevel1::RunPhysics()
{
	//Objects
	 //Buttons
	  //Back
	if(mpButtonBack)
	{
		mpButtonBack->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	}
	  //Scramble
	//if the button exists
	if(mpButtonScramble)
	{
		mpButtonScramble->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
		if(mpButtonScramble->GetButtonState() == kClick)
		{
			//scramble the board n times, where n is proportional to the size of the board
			mpBoard->ScramblePieces(mpBoard->mkTilesX * mpBoard->mkTilesY * 10);
		}
	}

	 //Board
	  //Pieces
	//Scramble pieces logic
	//if the puzzle has not been scrambled yet, do NOT allow the player to move pieces
	if(mpBoard->GetPiecesPosScrambled())
	{
		if(!mpBoard->mSolved)
		{
			for(int i = 0; i < mpBoard->mkTilesTotal; ++i)
			{
				mpBoard->mpTiles[i]->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
				if(mpBoard->mpTiles[i]->GetButtonState() == kClick)
				{
					//if the scramble button hasn't already been destroyed
					if(mpButtonScramble)
					{
						//if a successful move is made, destroy the scramble button
						if(mpBoard->MovePiece(i))
						{
							delete mpButtonScramble;
							mpButtonScramble = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
						}
					}
					else
					{
						mpBoard->MovePiece(i);
					}
				}
			}
		}
	}
	//Check if all of the pieces are in order (puzzle solved)
	if(mpBoard->mPiecesPosScrambled)
	{
		if(!mpBoard->mSolved)
		{
			if(mpBoard->IsSolved())
			{
				mpBoard->mSolved = true;
				//Change the background
				mBgTexture.Unload();
				mBgTexture.Load("./Resources/Textures/Backgrounds/bgScoreScreen.jpg");
				mBgSprite.ClearTextures();
				mBgSprite.AddTexture(&mBgTexture);

				//Update fonts
				sprintf_s(mStatsBuff, "It took you %d moves to solve a %d by %d puzzle!", mpBoard->mMoveCounter, mpBoard->mkTilesX, mpBoard->mkTilesY);
			}
		}
	}

	#ifdef DSDEBUGMODE
		//Score
		///pApp->mDefaultFont.SetColor(225, 155, 44);
		///sprintf_s(scoreTextBuff, "Score: %d", pApp->mScore);
	#endif //DSDEBUGMODE
}