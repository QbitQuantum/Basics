void AsyncRunner::performAsyncOperation() {
  // We don't support throttled QPS right now.  The right way to do
  // this requires an AsyncIntervalTimer

  uint32_t opType = config_->pickOpType();
  scoreboard_->opStarted(opType);

  OpData *d = &(outstandingOps_[writePos_]);
  writePos_ = (writePos_ + 1) % (q_size_);

  d->opType_ = opType;
  n_outstanding_++;
  ctr_--;
  curOpData_ = d;

  switch (static_cast<ClientLoadConfig::OperationEnum>(opType)) {
    case ClientLoadConfig::OP_NOOP:
      return client_->noop(recvCob);
    case ClientLoadConfig::OP_ONEWAY_NOOP:
      return client_->onewayNoop(recvCob);
    case ClientLoadConfig::OP_ASYNC_NOOP:
      return client_->asyncNoop(recvCob);
    case ClientLoadConfig::OP_SLEEP:
      return client_->sleep(recvCob, config_->pickSleepUsec());
    case ClientLoadConfig::OP_ONEWAY_SLEEP:
      return client_->onewaySleep(recvCob, config_->pickSleepUsec());
    case ClientLoadConfig::OP_BURN:
      return client_->burn(recvCob, config_->pickBurnUsec());
    case ClientLoadConfig::OP_ONEWAY_BURN:
      return client_->onewayBurn(recvCob, config_->pickBurnUsec());
    case ClientLoadConfig::OP_BAD_SLEEP:
      return client_->badSleep(recvCob, config_->pickSleepUsec());
    case ClientLoadConfig::OP_BAD_BURN:
      return client_->badBurn(recvCob, config_->pickBurnUsec());
    case ClientLoadConfig::OP_THROW_ERROR:
      d->code = loadgen::RNG::getU32();
      return client_->throwError(recvCob, d->code);
    case ClientLoadConfig::OP_THROW_UNEXPECTED:
      return client_->throwUnexpected(recvCob, loadgen::RNG::getU32());
    case ClientLoadConfig::OP_ONEWAY_THROW:
      return client_->onewayThrow(recvCob, loadgen::RNG::getU32());
    case ClientLoadConfig::OP_SEND:
    {
      std::string str(config_->pickSendSize(), 'a');
      return client_->send(recvCob, str);
    }
    case ClientLoadConfig::OP_ONEWAY_SEND:
    {
      std::string str(config_->pickSendSize(), 'a');
      return client_->onewaySend(recvCob, str);
    }
    case ClientLoadConfig::OP_RECV:
      return client_->recv(recvCob, config_->pickRecvSize());
    case ClientLoadConfig::OP_SENDRECV:
    {
      std::string str(config_->pickSendSize(), 'a');
      return client_->sendrecv(recvCob, str, config_->pickRecvSize());
    }
    case ClientLoadConfig::OP_ECHO:
    {
      std::string str(config_->pickSendSize(), 'a');
      return client_->echo(recvCob, str);
    }
    case ClientLoadConfig::OP_ADD:
    {
      boost::uniform_int<int64_t> distribution;
      curOpData_->a = distribution(loadgen::RNG::getRNG());
      curOpData_->b = distribution(loadgen::RNG::getRNG());

      return client_->add(recvCob, curOpData_->a, curOpData_->b);
    }
    case ClientLoadConfig::NUM_OPS:
      // fall through
      break;
      // no default case, so gcc will warn us if a new op is added
      // and this switch statement is not updated
  }

  T_ERROR("AsyncClientWorker::performOperation() got unknown operation %"
          PRIu32, opType);
  assert(false);
}