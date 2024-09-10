void setTimeValue( char *searchDir )
{
	void setFileTime( char *, time_t * ) ;
	
	time_t *newOldTime, *newOlderTime, *newOldestTime, *newExactTime ;
		
	char olderTime[]  = "01:00:00 2002/01/01" ;
	char oldestTime[] = "01:00:00 2001/01/01" ;
	char exactTime[] = "01:00:01 2002/01/01" ;
	char testFile[BUFFER_SIZE] = { '\0' } ;  
  	  	
	newOldTime = ( time_t * ) malloc( sizeof( time_t ) ) ;	
	newOlderTime = ( time_t * ) malloc( sizeof( time_t ) ) ; 
	newOldestTime = ( time_t * ) malloc( sizeof( time_t ) ) ;
	newExactTime = ( time_t * ) malloc( sizeof( time_t ) ) ;
	
  	*newOldTime = time( NULL ) ;
	*newOlderTime = parsedate( olderTime, NULL ) ;
	*newOldestTime = parsedate( oldestTime, NULL ) ;
	*newExactTime = parsedate( exactTime, NULL ) ;

	_debug( __FILE__, __LINE__, 5, "newOldTime is %s", ctime( newOldTime ) ) ;
	_debug( __FILE__, __LINE__, 5, "newOlderTime is %s", ctime( newOlderTime ) ) ;
	_debug( __FILE__, __LINE__, 5, "newOldestTime is %s", ctime( newOldestTime ) ) ;
	_debug( __FILE__, __LINE__, 5, "newExactTime is %s", ctime( newExactTime ) ) ;

	sprintf( testFile, "%s/%s", searchDir, "testTIME.txt" ) ;
	setFileTime( testFile, newExactTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testID1.c" ) ;
	setFileTime( testFile, newOldestTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testDATE1.c" ) ;
	setFileTime( testFile, newOldestTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testNAME1.c" ) ;
	setFileTime( testFile, newOldestTime ) ;	
	
	sprintf( testFile, "%s/%s", searchDir, "testID2.c" ) ;
	setFileTime( testFile, newOlderTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testDATE2.c" ) ;
	setFileTime( testFile, newOlderTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testNAME2.c" ) ;
	setFileTime( testFile, newOlderTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testID3.c" ) ;
	setFileTime( testFile, newOldTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testDATE3.c" ) ;
	setFileTime( testFile, newOldTime ) ;
	
	sprintf( testFile, "%s/%s", searchDir, "testNAME3.c" ) ;
	setFileTime( testFile, newOldTime ) ;
}