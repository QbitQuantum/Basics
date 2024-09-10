/*
 * Send bloom filter vector to POX 
 * I tried , BUT cannot match 
 * so here I just fake it by write to a local file
 * trigger the POX to update the bloom filter by read this fp file
 */
void sync_bloom_to_pox(){
	char *s = "bloom filter";
	// latest fp file close
	fflush(fpfile_latest);
	fclose(fpfile_latest);

	Sendto(sockfdbloom, s,strlen(s), 0,  (SA *) &fakeaddr, sizeof(fakeaddr));
}