void StoreApiImpl::delete_order(const std::string &orderId, Net::Http::ResponseWriter &response) {
    response.send(Net::Http::Code::Ok, "Do some magic\n");
}