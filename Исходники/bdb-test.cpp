void recv_inv(const std::error_code &ec, const message::inventory& packet,
    channel_ptr node)
{
    if (ec)
        log_error() << ec.message();
    message::get_data getdata;
    for (const message::inventory_vector& ivv: packet.inventories)
    {
        if (ivv.type != message::inventory_type::block)
            continue;
        getdata.inventories.push_back(ivv);
    }
    node->send(getdata, handle_send_packet);
    node->subscribe_inventory(std::bind(&recv_inv, _1, _2, node));
}