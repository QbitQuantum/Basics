 void ShowDevices::operator()(const PlaceHolders &&, ServerRequest &request,
                              Poco::Net::HTTPServerResponse &response) {
     response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
     BOOST_LOG_TRIVIAL(info) << "ShowDevices";
     const auto &producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
     producer.produce(response.send(), ZDevicesPT(singletons.getZDevices()));
 }