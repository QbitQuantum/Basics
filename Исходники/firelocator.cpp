void send_pub_key(
        n::connection_manager& con, 
        sc::encrypted_channels& sec, 
        const n::endpoint& ep,  
        const ms::greet_key_request& req, 
        user_info_map& users, 
        const sc::private_key& pkey)
{
    ms::greet_key_response rep{pkey.public_key()};
    m::message m = rep;

    auto address = n::make_address_str(ep); 
    m.meta.to = {address, req.response_service_address()};

    //send plaintext
    auto data = u::encode(m);
    data = u::compress(data);
    data = sec.encrypt(address, data);
    con.send(address, data);
}