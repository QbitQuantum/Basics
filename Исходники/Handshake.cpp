// send client key exchange
void sendClientKeyExchange(SSL& ssl, BufferOutput buffer)
{
    ssl.verifyState(serverHelloDoneComplete);
    if (ssl.GetError()) return;

    ClientKeyExchange ck(ssl);
    ck.build(ssl);
    ssl.makeMasterSecret();

    RecordLayerHeader rlHeader;
    HandShakeHeader   hsHeader;
    mySTL::auto_ptr<output_buffer> out(NEW_YS output_buffer);
    buildHeaders(ssl, hsHeader, rlHeader, ck);
    buildOutput(*out.get(), rlHeader, hsHeader, ck);
    hashHandShake(ssl, *out.get());

    if (buffer == buffered)
        ssl.addBuffer(out.release());
    else
        ssl.Send(out->get_buffer(), out->get_size());
}