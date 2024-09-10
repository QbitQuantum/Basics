void PetApi::pet_api_default_handler(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
    response.send(Net::Http::Code::Not_Found, "The requested method does not exist");
}