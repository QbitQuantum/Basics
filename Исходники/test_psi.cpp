uint32_t set_up_parameters(role_type role, uint32_t myneles, uint32_t* mybytelen,
	uint8_t** elements, uint8_t** pelements, CSocket& sock, crypto* crypt) {

	uint32_t pneles, nintersections, offset;

	//Exchange meta-information and equalize byte-length
	sock.Send(&myneles, sizeof(uint32_t));
	sock.Receive(&pneles, sizeof(uint32_t));

	if(role == SERVER) {
		sock.Send(mybytelen, sizeof(uint32_t));
	} else {
		sock.Receive(mybytelen, sizeof(uint32_t));
	}
	*elements = (uint8_t*) malloc(myneles * *mybytelen);
	*pelements = (uint8_t*) malloc(pneles * *mybytelen);

	crypt->gen_rnd(*elements, myneles * *mybytelen);

	//Exchange elements for later check
	if(role == SERVER) {
		sock.Send(*elements, myneles * *mybytelen);
		sock.Receive(*pelements, pneles * *mybytelen);
	} else { //have the client use some of the servers values s.t. the intersection is not disjoint
		sock.Receive(*pelements, pneles * *mybytelen);
		nintersections = rand() % min(myneles, pneles);
		offset = myneles / nintersections;

		for(uint32_t i = 0; i < nintersections; i++) {
			memcpy(*elements + i * offset * *mybytelen, *pelements + i * *mybytelen, *mybytelen);
		}
		sock.Send(*elements, myneles * *mybytelen);
	}

	return pneles;
}