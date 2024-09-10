void PetApiImpl::delete_pet(const int64_t &petId, const Pistache::Optional<Pistache::Http::Header::Raw> &apiKey, Pistache::Http::ResponseWriter &response) {
    response.send(Pistache::Http::Code::Ok, "Do some magic\n");
}