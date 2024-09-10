/*
 * Process a CA message
 *
 * Arguments:
 *	dcsp	pointer to a DCS control block for the neighbor
 *	cap	pointer to the CA part of the received message
 *
 * Returns:
 *	none
 *
 */
void
scsp_process_ca(Scsp_dcs* dcsp, Scsp_ca *cap)
{
	Scsp_csa	*csap, *next_csap;
	Scsp_cse	*csep;
	Scsp_server	*ssp = dcsp->sd_server;

	/*
	 * Process CSAS records from the CA message
	 */
	for (csap = cap->ca_csa_rec; csap; csap = next_csap) {
		next_csap = csap->next;
		SCSP_LOOKUP(ssp, &csap->key, csep);
		if (!csep || (scsp_cmp_id(&csap->oid,
					&csep->sc_oid) == 0 &&
				csap->seq > csep->sc_seq)) {
			/*
			 * CSAS entry not in cache or more
			 * up to date than cache, add it to CRL
			 */
			UNLINK(csap, Scsp_csa, cap->ca_csa_rec, next);
			LINK2TAIL(csap, Scsp_csa, dcsp->sd_crl, next);
		}
	}
}