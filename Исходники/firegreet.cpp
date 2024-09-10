void send_pub_key(
        n::connection_manager& con, 
        sc::session_library& sec, 
        const n::endpoint& ep,  
        const ms::greet_key_request& req, 
        user_info_map& users, 
        const sc::private_key& pkey)
{
    ms::greet_key_response rep{pkey.public_key()};
    m::message m = rep;

    auto address = n::make_address_str(ep); 
    m.meta.to = {address, req.response_service_address()};

    LOG << "sending pub key to " << address << std::endl;

    //send plaintext
    auto data = u::encode(m);
    data = sec.encrypt(address, data);
    con.send(address, data);
}