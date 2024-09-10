/*
==================
FullscreenFXManager::Initialize
==================
*/
void FullscreenFXManager::Initialize( idPlayerView *pv ) {
	// set the playerview
	playerView = pv;
	blendBackMaterial = declManager->FindMaterial( "textures/smf/blendBack" );

	// allocate the fx
	CreateFX( "helltime", "helltime", 1000 );
	CreateFX( "warp", "warp", 0 );
	CreateFX( "envirosuit", "envirosuit", 500 );
	CreateFX( "doublevision", "doublevision", 0 );
	CreateFX( "multiplayer", "multiplayer", 1000 );
	CreateFX( "influencevision", "influencevision", 1000 );
	CreateFX( "bloom", "bloom", 0 );

	// pre-cache the texture grab so we dont hitch
	renderSystem->CropRenderSize( 512, 512, true );
	renderSystem->CaptureRenderToImage( "_accum" );
	renderSystem->UnCrop();

    renderSystem->CropRenderSize( 512, 256, true );
	renderSystem->CaptureRenderToImage( "_scratch" );
	renderSystem->UnCrop();

	renderSystem->CaptureRenderToImage( "_currentRender" );
}