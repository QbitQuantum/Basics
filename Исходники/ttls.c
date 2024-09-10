/*
 *	Convert diameter attributes to our VALUE_PAIR's
 */
static VALUE_PAIR *diameter2vp(REQUEST *request, SSL *ssl,
			       const uint8_t *data, size_t data_len)
{
	uint32_t	attr;
	uint32_t	vendor;
	uint32_t	length;
	size_t		offset;
	size_t		size;
	size_t		data_left = data_len;
	VALUE_PAIR	*first = NULL;
	VALUE_PAIR	**last = &first;
	VALUE_PAIR	*vp;

	while (data_left > 0) {
		rad_assert(data_left <= data_len);
		memcpy(&attr, data, sizeof(attr));
		data += 4;
		attr = ntohl(attr);
		vendor = 0;

		memcpy(&length, data, sizeof(length));
		data += 4;
		length = ntohl(length);

		/*
		 *	A "vendor" flag, with a vendor ID of zero,
		 *	is equivalent to no vendor.  This is stupid.
		 */
		offset = 8;
		if ((length & (1 << 31)) != 0) {
			memcpy(&vendor, data, sizeof(vendor));
			vendor = ntohl(vendor);

			data += 4; /* skip the vendor field, it's zero */
			offset += 4; /* offset to value field */

			if (attr > 65535) goto next_attr;
			if (vendor > FR_MAX_VENDOR) goto next_attr;
		}

		/*
		 *	FIXME: Handle the M bit.  For now, we assume that
		 *	some other module takes care of any attribute
		 *	with the M bit set.
		 */
		
		/*
		 *	Get the length.
		 */
		length &= 0x00ffffff;

		/*
		 *	Get the size of the value portion of the
		 *	attribute.
		 */
		size = length - offset;

		/*
		 *	Vendor attributes can be larger than 255.
		 *	Normal attributes cannot be.
		 */
		if ((attr > 255) && (vendor == 0)) {
			RDEBUG2W("Skipping Diameter attribute %u",
				attr);
			goto next_attr;
		}

		/*
		 * EAP-Message AVPs can be larger than 253 octets.
		 */
		if ((size > 253) && !((vendor == 0) && (attr == PW_EAP_MESSAGE))) {
			RDEBUG2W("diameter2vp skipping long attribute %u", attr);
			goto next_attr;
		}

		/*
		 *	RADIUS VSAs are handled as Diameter attributes
		 *	with Vendor-Id == 0, and the VSA data packed
		 *	into the "String" field as per normal.
		 *
		 *	EXCEPT for the MS-CHAP attributes.
		 */
		if ((vendor == 0) && (attr == PW_VENDOR_SPECIFIC)) {
			ssize_t decoded;
			uint8_t buffer[256];

			buffer[0] = PW_VENDOR_SPECIFIC;
			buffer[1] = size + 2;
			memcpy(buffer + 2, data, size);

			vp = NULL;
			decoded = rad_attr2vp(NULL, NULL, NULL,
					      buffer, size + 2, &vp);
			if (decoded < 0) {
				RDEBUG2E("diameter2vp failed decoding attr: %s",
					fr_strerror());
				goto do_octets;
			}

			if ((size_t) decoded != size + 2) {
				RDEBUG2E("diameter2vp failed to entirely decode VSA");
				pairfree(&vp);
				goto do_octets;
			}

			*last = vp;
			do {
				last = &(vp->next);
				vp = vp->next;
			} while (vp != NULL);

			goto next_attr;
		}

		/*
		 *	Create it.  If this fails, it's because we're OOM.
		 */
	do_octets:
		vp = paircreate(attr, vendor);
		if (!vp) {
			RDEBUG2("Failure in creating VP");
			pairfree(&first);
			return NULL;
		}

		/*
		 *	If it's a type from our dictionary, then
		 *	we need to put the data in a relevant place.
		 */
		switch (vp->da->type) {
		case PW_TYPE_INTEGER:
		case PW_TYPE_DATE:
			if (size != vp->length) {
				const DICT_ATTR *da;

				/*
				 *	Bad format.  Create a "raw"
				 *	attribute.
				 */
		raw:
				if (vp) pairfree(&vp);
				da = dict_attrunknown(attr, vendor, TRUE);
				if (!da) return NULL;
				vp = pairalloc(NULL, da);
				if (size >= 253) size = 253;
				vp->length = size;
				memcpy(vp->vp_octets, data, vp->length);
				break;
			}
			memcpy(&vp->vp_integer, data, vp->length);

			/*
			 *	Stored in host byte order: change it.
			 */
			vp->vp_integer = ntohl(vp->vp_integer);
			break;

		case PW_TYPE_INTEGER64:
			if (size != vp->length) goto raw;
			memcpy(&vp->vp_integer64, data, vp->length);

			/*
			 *	Stored in host byte order: change it.
			 */
			vp->vp_integer64 = ntohll(vp->vp_integer64);
			break;

		case PW_TYPE_IPADDR:
			if (size != vp->length) {
				RDEBUG2("Invalid length attribute %d",
				       attr);
				pairfree(&first);
				pairfree(&vp);
				return NULL;
			}
		  memcpy(&vp->vp_ipaddr, data, vp->length);

		  /*
		   *	Stored in network byte order: don't change it.
		   */
		  break;

		case PW_TYPE_BYTE:
			if (size != vp->length) goto raw;
			vp->vp_integer = data[0];
			break;

		case PW_TYPE_SHORT:
			if (size != vp->length) goto raw;
			vp->vp_integer = (data[0] * 256) + data[1];
			break;

		case PW_TYPE_SIGNED:
			if (size != vp->length) goto raw;
			memcpy(&vp->vp_signed, data, vp->length);
			vp->vp_signed = ntohl(vp->vp_signed);
			break;

		case PW_TYPE_IPV6ADDR:
			if (size != vp->length) goto raw;
			memcpy(&vp->vp_ipv6addr, data, vp->length);
			break;

		case PW_TYPE_IPV6PREFIX:
			if (size != vp->length) goto raw;
			memcpy(&vp->vp_ipv6prefix, data, vp->length);
			break;

			/*
			 *	String, octet, etc.  Copy the data from the
			 *	value field over verbatim.
			 */
		case PW_TYPE_OCTETS:
			if (attr == PW_EAP_MESSAGE) {
				const uint8_t *eap_message = data;

				/*
				 *	vp exists the first time around.
				 */
				while (1) {
					vp->length = size;
					if (vp->length > 253) vp->length = 253;
					memcpy(vp->vp_octets, eap_message,
					       vp->length);

					size -= vp->length;
					eap_message += vp->length;

					*last = vp;
					last = &(vp->next);

					if (size == 0) break;

					vp = paircreate(attr, vendor);
					if (!vp) {
						RDEBUG2("Failure in creating VP");
						pairfree(&first);
						return NULL;
					}
				}

				goto next_attr;
			} /* else it's another kind of attribute */
			/* FALL-THROUGH */

		default:
			if (size >= 253) size = 253;
			vp->length = size;
			memcpy(vp->vp_strvalue, data, vp->length);
			break;
		}

		/*
		 *	User-Password is NUL padded to a multiple
		 *	of 16 bytes.  Let's chop it to something
		 *	more reasonable.
		 *
		 *	NOTE: This means that the User-Password
		 *	attribute CANNOT EVER have embedded zeros in it!
		 */
		if ((vp->da->vendor == 0) && (vp->da->attr == PW_USER_PASSWORD)) {
			/*
			 *	If the password is exactly 16 octets,
			 *	it won't be zero-terminated.
			 */
			vp->vp_strvalue[vp->length] = '\0';
			vp->length = strlen(vp->vp_strvalue);
		}

		/*
		 *	Ensure that the client is using the
		 *	correct challenge.  This weirdness is
		 *	to protect against against replay
		 *	attacks, where anyone observing the
		 *	CHAP exchange could pose as that user,
		 *	by simply choosing to use the same
		 *	challenge.
		 *
		 *	By using a challenge based on
		 *	information from the current session,
		 *	we can guarantee that the client is
		 *	not *choosing* a challenge.
		 *
		 *	We're a little forgiving in that we
		 *	have loose checks on the length, and
		 *	we do NOT check the Id (first octet of
		 *	the response to the challenge)
		 *
		 *	But if the client gets the challenge correct,
		 *	we're not too worried about the Id.
		 */
		if (((vp->da->vendor == 0) && (vp->da->attr == PW_CHAP_CHALLENGE)) ||
		    ((vp->da->vendor == VENDORPEC_MICROSOFT) && (vp->da->attr == PW_MSCHAP_CHALLENGE))) {
			uint8_t	challenge[16];

			if ((vp->length < 8) ||
			    (vp->length > 16)) {
				RDEBUG("Tunneled challenge has invalid length");
				pairfree(&first);
				pairfree(&vp);
				return NULL;
			}

			eapttls_gen_challenge(ssl, challenge,
					      sizeof(challenge));
			
			if (memcmp(challenge, vp->vp_octets,
				   vp->length) != 0) {
				RDEBUG("Tunneled challenge is incorrect");
				pairfree(&first);
				pairfree(&vp);
				return NULL;
			}
		}

		/*
		 *	Update the list.
		 */
		*last = vp;
		last = &(vp->next);

	next_attr:
		/*
		 *	Catch non-aligned attributes.
		 */
		if (data_left == length) break;

		/*
		 *	The length does NOT include the padding, so
		 *	we've got to account for it here by rounding up
		 *	to the nearest 4-byte boundary.
		 */
		length += 0x03;
		length &= ~0x03;

		rad_assert(data_left >= length);
		data_left -= length;
		data += length - offset; /* already updated */
	}

	/*
	 *	We got this far.  It looks OK.
	 */
	return first;
}