void measureFPS ()
{
	// Measure FPS
	mint::Time tm_elaps;	
	if ( ++tm_cnt > 5 ) {		
		tm_elaps.SetSystemTime ( ACC_NSEC );			// get current sytem time - accurate to 1 ns
		tm_elaps = tm_elaps - tm_last;					// get elapsed time from 5 frames ago
		tm_fps = 5.0 * 1000.0 / tm_elaps.GetMSec ();	// compute fps
		tm_cnt = 0;										// reset frame counter
		tm_last.SetSystemTime ( ACC_NSEC );
	}
}