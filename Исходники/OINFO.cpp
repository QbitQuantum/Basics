//------- Begin of function Info::init_random_seed ------//
//
// [unsigned] randomSeed - if given, it will be the random seed of the game.
//									random seed. otherwise a random seed will be
//								   picked.
//								   (default:0)
//
void Info::init_random_seed(int randomSeed)
{
	if( randomSeed )
		random_seed = randomSeed;
	else
	{
		randomSeed = time(NULL);
		randomSeed = (int) _rotr( randomSeed, 4 );
		if( randomSeed < 0 )
			randomSeed = ~randomSeed;
		if( randomSeed == 0 )
			randomSeed = 1;
		random_seed = randomSeed;
	}

	misc.set_random_seed(random_seed);

	//------ write random seed --------//

	if( sys.testing_session )
	{
		File fileMapSeed;

		fileMapSeed.file_create( "MAP.RS" );

		String str(misc.format(random_seed,1));

		fileMapSeed.file_write(str, str.len());
	}
}