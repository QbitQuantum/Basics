int main(){
	createWindow();
	printf("This is SDL primitives\r\n");
	//pthread_t t1, t2, th;

	while( !quit ) {
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				quit = true;
			}
		}
		char str[56];
		uint len = snprintf(str, sizeof(str),"%0.2f", elapsed);
		updateWindow(str, len);
		for(uint i=0; i<5; i++)keyBoard[i*2].pressed ^= true; 
		SDL_Delay(500);
		elapsed += 0.5;
	}		
	closeWindow();
	return 0;
}