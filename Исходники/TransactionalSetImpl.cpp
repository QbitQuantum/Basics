            bool TransactionalSetImpl::remove(const serialization::pimpl::Data& e) {
                std::auto_ptr<protocol::ClientMessage> request =
                        protocol::codec::TransactionalSetRemoveCodec::RequestParameters::encode(
                                getName(), getTransactionId(), util::getThreadId(), e);

                return invokeAndGetResult<bool, protocol::codec::TransactionalSetRemoveCodec::ResponseParameters>(request);
            }