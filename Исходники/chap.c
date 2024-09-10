/*
 * ChapSendChallenge - Send an Authenticate challenge.
 */
static void
ChapSendChallenge(
    chap_state *cstate)
{
    u_char *outp;
    int chal_len, name_len;
    int outlen;

    chal_len = cstate->chal_len;
    name_len = strlen(cstate->chal_name);
    outlen = CHAP_HEADERLEN + sizeof (u_char) + chal_len + name_len;
    outp = outpacket_buf;

    MAKEHEADER(outp, PPP_CHAP);		/* paste in a CHAP header */

    PUTCHAR(CHAP_CHALLENGE, outp);
    PUTCHAR(cstate->chal_id, outp);
    PUTSHORT(outlen, outp);

    PUTCHAR(chal_len, outp);		/* put length of challenge */
    BCOPY(cstate->challenge, outp, chal_len);
    INCPTR(chal_len, outp);

    BCOPY(cstate->chal_name, outp, name_len);	/* append hostname */

    output(cstate->unit, outpacket_buf, outlen + PPP_HDRLEN);

    TIMEOUT(ChapChallengeTimeout, cstate, cstate->timeouttime);
    ++cstate->chal_transmits;
}