/** Converts the reply into server version and a return code
 *
 * This function takes the reply BER Value and decodes the NMAS server version and return code and if a non
 * null retData buffer was supplied, tries to decode the the return data and length.
 *
 @verbatim
	ResponseBer contents:
		server_version		INTEGER
		error       		INTEGER
		data			OCTET STRING
 @endverbatim
 *
 * @param[in] reply_bv reply data from extended request.
 * @param[out] server_version that responded.
 * @param[out] out data.
 * @param[out] outlen Length of data written to out.
 * @return 0 on success, and < 0 on error.
 */
static int ber_decode_login_data(struct berval *reply_bv, int *server_version, void *out, size_t *outlen)
{
	int rc = 0;
	int err = 0;
	BerElement *reply_ber = NULL;

	rad_assert(out != NULL);
	rad_assert(outlen != NULL);

	if ((reply_ber = ber_init(reply_bv)) == NULL) {
		err = NMAS_E_SYSTEM_RESOURCES;
		goto finish;
	}

	rc = ber_scanf(reply_ber, "{iis}", server_version, &err, out, outlen);
	if (rc == -1) {
		err = NMAS_E_FRAG_FAILURE;
		goto finish;
	}

finish:

	if(reply_ber) ber_free(reply_ber, 1);

	return err;
}