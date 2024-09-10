void msaFluidParticlesApp::keyDown( KeyEvent event )
{ 
    switch( event.getChar() ) {
		case 'a':
			drawFluid = !drawFluid;
		break;
		case 'd':
			drawFluidTex = !drawFluidTex;
		break;
		case 'f':
			setFullScreen( ! isFullScreen() );
		break;
		case ' ':
			fluidSolver.randomizeColor();
		break;
		case 'p':
			drawParticles = ! drawParticles;
		break;
		case 'b': {
			Timer timer;
			timer.start();
			const int ITERS = 1000;
			for( int i = 0; i < ITERS; ++i )
				fluidSolver.update();
			timer.stop();
			console() << ITERS << " iterations took " << timer.getSeconds() << " seconds." << std::endl;
		}
		break;
		case 's':
			writeImage( getHomeDirectory() / "cinder" / "saveImage_" / ( toString( getElapsedFrames() ) + ".png" ), copyWindowSurface() );
			break;
    }
}