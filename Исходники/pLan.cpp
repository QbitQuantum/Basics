std::shared_ptr<core::Processor> ExecutionPlan::addProcessor(const std::shared_ptr<core::Processor> &processor, const std::string &name, core::Relationship relationship, bool linkToPrevious) {
  if (finalized) {
    return nullptr;
  }

  utils::Identifier uuid;
  id_generator_->generate(uuid);

  processor->setStreamFactory(stream_factory);
  // initialize the processor
  processor->initialize();

  processor_mapping_[processor->getUUIDStr()] = processor;

  if (!linkToPrevious) {
    termination_ = relationship;
  } else {
    std::shared_ptr<core::Processor> last = processor_queue_.back();

    if (last == nullptr) {
      last = processor;
      termination_ = relationship;
    }

    relationships_.push_back(connectProcessors(last, processor, relationship, true));
  }

  std::shared_ptr<core::ProcessorNode> node = std::make_shared<core::ProcessorNode>(processor);

  processor_nodes_.push_back(node);

  std::shared_ptr<core::ProcessContext> context = std::make_shared<core::ProcessContext>(node, controller_services_provider_, prov_repo_, flow_repo_, content_repo_);
  processor_contexts_.push_back(context);

  processor_queue_.push_back(processor);

  return processor;
}