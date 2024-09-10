//
// Free all memory in a CertGroup
//
void CertGroup::destroy(Allocator &allocator)
{
	switch (type()) {
	case CSSM_CERTGROUP_DATA:
		// array of CSSM_DATA elements
		for (uint32 n = 0; n < count(); n++)
			allocator.free(blobCerts()[n].data());
		allocator.free (blobCerts ());
		break;
	case CSSM_CERTGROUP_ENCODED_CERT:
		for (uint32 n = 0; n < count(); n++)
			allocator.free(encodedCerts()[n].data());
		allocator.free (blobCerts ());
		break;
	case CSSM_CERTGROUP_PARSED_CERT:
		// CSSM_PARSED_CERTS array -- unimplemented
	case CSSM_CERTGROUP_CERT_PAIR:
		// CSSM_CERT_PAIR array -- unimplemented
		break;
	}
}