            int TransactionalMultiMapImpl::valueCount(const serialization::pimpl::Data &key) {
                std::auto_ptr<protocol::ClientMessage> request =
                        protocol::codec::TransactionalMultiMapValueCountCodec::RequestParameters::encode(
                                getName(), getTransactionId(), util::getThreadId(), key);

                return invokeAndGetResult<int, protocol::codec::TransactionalMultiMapValueCountCodec::ResponseParameters>(
                        request);
            }