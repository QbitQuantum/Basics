static void
proto_session_hdr_unmarshall_sver(Proto_Session *s, Proto_StateVersion *v)
{
    v->raw = ntohll(s->rhdr.sver.raw);
}