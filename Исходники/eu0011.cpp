void eu0011 :: solucion(){
	// ---------------------------------------------------- //
	tstart = (double)clock()/CLOCKS_PER_SEC;
	// ---------------------------------------------------- //
	
	output = 0;
	tem_2d_1 = new unsigned long long *[20];
	for ( unsigned int i=0; i<20; i++ ){
		tem_2d_1[i] = new unsigned long long [20];
	}
	
	// ---------------------------------------------------- //
	
	char uu[3];
	myfile_read_1.open("eu0011_data.txt");
// 	myfile_read_1.setf( ios::fixed );
	
	for( unsigned int i=0; i<20; i++ ){
		for( unsigned int j=0; j<20; j++ ){			
			myfile_read_1.get(uu, 3);
			tem_2d_1[i][j] = strtold(uu,0);
			myfile_read_1.ignore(1,' ');
		}
	}
	// Arriba a Abajo
	for( unsigned int j=0; j<20; j++ ){
		for( unsigned int k=0; k<17; k++ ){
			temp_1 = 1;
			for( unsigned int i=k; i<k+4; i++ ){
				temp_1 = temp_1*tem_2d_1[i][j];
			}
			if( output < temp_1 ){
				output = temp_1;
			}
		}
	}
	// Lateral
	for( unsigned int i=0; i<20; i++ ){
		for( unsigned int k=0; k<17; k++ ){
			temp_1 = 1;
			for( unsigned int j=k; j<k+4; j++ ){
				temp_1 = temp_1*tem_2d_1[i][j];
			}
			if( output < temp_1 ){
				output = temp_1;
			}
		}
	}
	// Diagonal
	for( unsigned int i=0; i<17; i++ ){
		for( unsigned int j=0; j<17; j++ ){
			temp_1 = 1;
			for( unsigned int k=0; k<4; k++ ){
				temp_1 = temp_1*tem_2d_1[i+k][j+k];
			}
			if( output < temp_1 ){
				output = temp_1;
			}
		}
	}
	// Diagonal 2
	for( unsigned int i=3; i<20; i++ ){
		for( unsigned int j=0; j<17; j++ ){
			temp_1 = 1;
			for( unsigned int k=0; k<4; k++ ){
				temp_1 = temp_1*tem_2d_1[i-k][j+k];
			}
			if( output < temp_1 ){
				output = temp_1;
			}
		}
	}
	
	// ---------------------------------------------------- //
	tstop = (double)clock()/CLOCKS_PER_SEC;
	ttime= tstop-tstart;
	// ---------------------------------------------------- //
}