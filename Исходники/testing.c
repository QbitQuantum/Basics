void perft(char dep) {
	int start_time, end_time;
	char num[65];
	float time;
	/*char p0[]="r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
	char p0[]="8/PPP4k/8/8/8/8/4Kppp/8 w - - ";*/
	/*8/2p5/3p4/KP5r/1R3p1k/6P1/4P3/8 b - - 0 1*/
	/*char p0[]="8/2p5/3p4/KP5r/1R3p1k/6P1/4P3/8 b - - 0 1";*/
	/*8/5kpp/2K5/p5q1/6P1/5P2/8/2q5 w - - 0 53*/
	/*char p0[]="8/5kpp/2K5/p5q1/6P1/5P2/8/2q5 w - - 0 53";

	char p0[]="8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -";
	

		
	char p0[]="8/2p5/K2p4/1P5r/1R3p1k/8/4P1P1/8 b - - 0 1";//15
	char p0[]="8/2p5/3p4/1P5r/KR3p1k/8/4P1P1/8 b - - 0 1";//15----30


	char p0[]="8/2p5/3p4/KP5r/R4p1k/8/4P1P1/8 b - - 0 1";//15
	char p0[]="8/2p5/3p4/KP5r/5p1k/1R6/4P1P1/8 b - - 0 1";//15
	char p0[]="8/2p5/3p4/KP5r/5p1k/8/1R2P1P1/8 b - - 0 1";//16
	char p0[]="8/2p5/3p4/KP5r/5p1k/8/4P1P1/1R6 b - - 0 1";//16
	char p0[]="8/2p5/3p4/KP5r/2R2p1k/8/4P1P1/8 b - - 0 1";//15
	char p0[]="8/2p5/3p4/KP5r/3R1p1k/8/4P1P1/8 b - - 0 1";//15
	char p0[]="8/2p5/3p4/KP5r/4Rp1k/8/4P1P1/8 b - - 0 1";//15
	char p0[]="8/2p5/3p4/KP5r/5R1k/8/4P1P1/8 b - - 0 1";//2-----109

	char p0[]="8/2p5/3p4/KP5r/1R3p1k/4P3/6P1/8 b - - 0 1";//15 
	char p0[]="8/2p5/3p4/KP5r/1R2Pp1k/8/6P1/8 b - e3 0 1";//17----32 ERROR???

	char p0[]="8/2p5/3p4/KP5r/1R3p1k/6P1/4P3/8 b - - 0 1";//4
	char p0[]="8/2p5/3p4/KP5r/1R3pPk/8/4P3/8 b - g3 0 1";//18-----22
	*/
	init_board();
	/*set_position(p0);*/

	init_data();
	print_board();

	print_bitboard();
	start_time = time_elapsed();
	perf_t(dep);
	end_time = time_elapsed();
	_ui64toa(Nodes,num,10);
	time = ((end_time - start_time) / (float)1000);
	printf("\nmoves %s in %.3f sec.\n", num, time);
	}