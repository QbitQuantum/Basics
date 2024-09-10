bool StageSelect::init(){
	if ( !CCLayerColor::initWithColor( ccc4( 0xff, 0xff, 0xff, 0xff ) ) ){
		return false;
    }
	scheduleUpdate();

	//クリアステージの読み込み
	mUserDefault = CCUserDefault::sharedUserDefault();

	CCSprite* spriteBack = CCSprite::create( "image/stageBack.png" );
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	spriteBack->setPosition( ccp( winSize.width / 2, winSize.height / 2 ) );
	addChild( spriteBack );

	mNumStage = 21;

	mButtons = new CCMenu*[ mNumStage ];
	mNumLeftSprites = new CCSprite*[ mNumStage ];
	mNumRightSprites = new CCSprite*[ mNumStage ];
	mCheckSprite = new CCSprite*[ mNumStage ];
	CCTexture2D* numberTex = CCTextureCache::sharedTextureCache()->addImage( "image/number.png" );
	for ( int i = 0; i < mNumStage; i++ ){
		CCMenuItemImage* item = CCMenuItemImage::create( "image/stagebutton_0.png", "image/stagebutton_1.png", this, menu_selector( StageSelect::stageSelectCallback ) );
		item->setTag( i );

		mButtons[ i ] = CCMenu::create( item, NULL );

		float x = mButtonListLeft + i * mButtonIntervalX;
		float y = mButtonListUp + ( i % 2 ) * mButtonIntervalY;
		ScreenConverter::toLeftUp( &y );

		mButtons[ i ]->setPosition( ccp( x, y ) );

		addChild( mButtons[ i ] );

		//クリアチェック
		mCheckSprite[ i ] = CCSprite::create( "image/clear_check.png" );
		mCheckSprite[ i ]->setPosition( ccp(x,y) );
		addChild(mCheckSprite[ i ]);
		CCString* keyStr = CCString::createWithFormat( "stageCleared%d", i ) ;
		if(!mUserDefault->getBoolForKey(keyStr->getCString(),false)){
			mCheckSprite[ i ]->setVisible( false );	
		}

		int n = i + 1;
		CCRect rect;
		rect.setRect( ( n % 10 ) * 32, 0, 32, 32 );
		mNumRightSprites[ i ] = CCSprite::createWithTexture( numberTex, rect );

		rect.setRect( ( n / 10 ) * 32, 0, 32, 32 );
		mNumLeftSprites[ i ] = CCSprite::createWithTexture( numberTex, rect );

		mNumRightSprites[ i ]->setPosition( ccp( x + 16, y ) );
		mNumLeftSprites[ i ]->setPosition( ccp( x - 16, y ) );

		addChild( mNumRightSprites[ i ] );
		addChild( mNumLeftSprites[ i ] );

		
	}

	mPlayerA = CCSprite::create( "image/ship_stage.png" );
	mPlayerB = CCSprite::create( "image/ship_stage.png" );

	mPlayerA->setPosition( ccp( -100.0f, 90.0f ) );
	mPlayerA->setRotation( 90 );
	mPlayerB->setPosition( ccp( winSize.width + 100.0f, winSize.height - 90.0f ) );
	mPlayerB->setRotation( -90 );

	addChild( mPlayerA, 1 );
	addChild( mPlayerB, 1 );

	for ( int i = 0; i < 5; i++ ){
		mRipplesA[ i ] = new Ripple( -30 * i - 1, true );
		mRipplesA[ i ]->setParent( this, 0 );
		mRipplesB[ i ] = new Ripple( -30 * i - 1, true );
		mRipplesB[ i ]->setParent( this, 0 );
	}
	
	setTouchMode( kCCTouchesOneByOne );
	setTouchEnabled( true );
	mIsTouch = false;

	mOnSequence = false;
	mTimeCount = 0;

    return true;
}