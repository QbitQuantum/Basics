rmw_node_t *
rmw_create_node(const char * name, size_t domain_id)
{
  if (!name) {
    RMW_SET_ERROR_MSG("name is null");
    return nullptr;
  }
  DDS::DomainParticipantFactory_var dp_factory = DDS::DomainParticipantFactory::get_instance();
  if (!dp_factory) {
    RMW_SET_ERROR_MSG("failed to get domain participant factory");
    return nullptr;
  }

  DDS::DomainId_t domain = static_cast<DDS::DomainId_t>(domain_id);
  DDS::DomainParticipant * participant = nullptr;

  // Make sure that the OSPL_URI is set, otherwise node creation will fail.
  char * ospl_uri = nullptr;
  const char * ospl_uri_env = "OSPL_URI";
#ifndef _WIN32
  ospl_uri = getenv(ospl_uri_env);
#else
  size_t ospl_uri_size;
  _dupenv_s(&ospl_uri, &ospl_uri_size, ospl_uri_env);
#endif
  if (!ospl_uri) {
    RMW_SET_ERROR_MSG("OSPL_URI not set");
    return nullptr;
  } else {
#ifdef _WIN32
    free(ospl_uri);
#endif
  }

  // Ensure the ROS_DOMAIN_ID env variable is set, otherwise parsing of the config may fail.
  // Also make sure the it is set to the domain_id passed in, otherwise it will fail.
  // But first backup the current ROS_DOMAIN_ID.
  char * ros_domain_id = nullptr;
  const char * env_var = "ROS_DOMAIN_ID";
#ifndef _WIN32
  ros_domain_id = getenv(env_var);
#else
  size_t ros_domain_id_size;
  _dupenv_s(&ros_domain_id, &ros_domain_id_size, env_var);
#endif

  // On Windows, setting the ROS_DOMAIN_ID does not fix the problem, so error early.
#ifdef _WIN32
  if (!ros_domain_id) {
    RMW_SET_ERROR_MSG("environment variable ROS_DOMAIN_ID is not set");
    fprintf(stderr, "[rmw_opensplice_cpp]: error: %s\n", rmw_get_error_string_safe());
    return nullptr;
  }
#endif

  // Set the ROS_DOMAIN_ID explicitly (if not Windows).
#ifndef _WIN32
  auto domain_id_as_string = std::to_string(domain_id);
  int ret = 0;
  ret = setenv(env_var, domain_id_as_string.c_str(), 1);
  if (0 != ret) {
    RMW_SET_ERROR_MSG("failed to set the ROS_DOMAIN_ID");
    return nullptr;
  }
#endif

  participant = dp_factory->create_participant(
    domain, PARTICIPANT_QOS_DEFAULT, NULL, DDS::STATUS_MASK_NONE);
  if (!participant) {
    RMW_SET_ERROR_MSG("failed to create domain participant");
    return NULL;
  }

  // Restore the ROS_DOMAIN_ID if necessary (and not Windows).
#ifndef _WIN32
  if (ros_domain_id) {
    ret = setenv(env_var, ros_domain_id, 1);
    if (0 != ret) {
      RMW_SET_ERROR_MSG("failed to reset the ROS_DOMAIN_ID");
      return nullptr;
    }
  } else {
    // Otherwise unset it again.
    ret = unsetenv(env_var);
    if (0 != ret) {
      RMW_SET_ERROR_MSG("failed to unset the ROS_DOMAIN_ID");
      return nullptr;
    }
  }
#endif

  rmw_node_t * node = nullptr;
  OpenSpliceStaticNodeInfo * node_info = nullptr;
  CustomPublisherListener * publisher_listener = nullptr;
  CustomSubscriberListener * subscriber_listener = nullptr;
  void * buf = nullptr;

  DDS::DataReader * data_reader = nullptr;
  DDS::PublicationBuiltinTopicDataDataReader * builtin_publication_datareader = nullptr;
  DDS::SubscriptionBuiltinTopicDataDataReader * builtin_subscription_datareader = nullptr;
  DDS::Subscriber * builtin_subscriber = participant->get_builtin_subscriber();
  if (!builtin_subscriber) {
    RMW_SET_ERROR_MSG("builtin subscriber handle is null");
    goto fail;
  }

  // setup publisher listener
  data_reader = builtin_subscriber->lookup_datareader("DCPSPublication");
  builtin_publication_datareader =
    DDS::PublicationBuiltinTopicDataDataReader::_narrow(data_reader);
  if (!builtin_publication_datareader) {
    RMW_SET_ERROR_MSG("builtin publication datareader handle is null");
    goto fail;
  }

  buf = rmw_allocate(sizeof(CustomPublisherListener));
  if (!buf) {
    RMW_SET_ERROR_MSG("failed to allocate memory");
    goto fail;
  }
  RMW_TRY_PLACEMENT_NEW(publisher_listener, buf, goto fail, CustomPublisherListener)
  buf = nullptr;
  builtin_publication_datareader->set_listener(publisher_listener, DDS::DATA_AVAILABLE_STATUS);

  data_reader = builtin_subscriber->lookup_datareader("DCPSSubscription");
  builtin_subscription_datareader =
    DDS::SubscriptionBuiltinTopicDataDataReader::_narrow(data_reader);
  if (!builtin_subscription_datareader) {
    RMW_SET_ERROR_MSG("builtin subscription datareader handle is null");
    goto fail;
  }

  // setup subscriber listener
  buf = rmw_allocate(sizeof(CustomSubscriberListener));
  if (!buf) {
    RMW_SET_ERROR_MSG("failed to allocate memory");
    goto fail;
  }
  RMW_TRY_PLACEMENT_NEW(subscriber_listener, buf, goto fail, CustomSubscriberListener)
  buf = nullptr;
  builtin_subscription_datareader->set_listener(subscriber_listener, DDS::DATA_AVAILABLE_STATUS);

  node = rmw_node_allocate();
  if (!node) {
    RMW_SET_ERROR_MSG("failed to allocate rmw_node_t");
    goto fail;
  }

  node->name = reinterpret_cast<const char *>(rmw_allocate(sizeof(char) * strlen(name) + 1));
  if (!node->name) {
    RMW_SET_ERROR_MSG("failed to allocate memory for node name");
    goto fail;
  }
  memcpy(const_cast<char *>(node->name), name, strlen(name) + 1);

  buf = rmw_allocate(sizeof(OpenSpliceStaticNodeInfo));
  if (!buf) {
    RMW_SET_ERROR_MSG("failed to allocate memory");
    goto fail;
  }
  RMW_TRY_PLACEMENT_NEW(node_info, buf, goto fail, OpenSpliceStaticNodeInfo)
  buf = nullptr;
  node_info->participant = participant;
  node_info->publisher_listener = publisher_listener;
  node_info->subscriber_listener = subscriber_listener;

  node->implementation_identifier = opensplice_cpp_identifier;
  node->data = node_info;

  return node;
fail:
  if (participant) {
    if (dp_factory->delete_participant(participant) != DDS::RETCODE_OK) {
      std::stringstream ss;
      ss << "leaking domain participant while handling failure at: " <<
        __FILE__ << ":" << __LINE__ << '\n';
      (std::cerr << ss.str()).flush();
    }
  }
  if (publisher_listener) {
    RMW_TRY_DESTRUCTOR_FROM_WITHIN_FAILURE(
      publisher_listener->~CustomPublisherListener(), CustomPublisherListener)
    rmw_free(publisher_listener);
  }
  if (subscriber_listener) {
    RMW_TRY_DESTRUCTOR_FROM_WITHIN_FAILURE(
      subscriber_listener->~CustomSubscriberListener(), CustomSubscriberListener)
    rmw_free(subscriber_listener);
  }
  if (node_info) {
    RMW_TRY_DESTRUCTOR_FROM_WITHIN_FAILURE(
      node_info->~OpenSpliceStaticNodeInfo(), OpenSpliceStaticNodeInfo)
    rmw_free(node_info);
  }
  if (buf) {
    rmw_free(buf);
  }
  if (node) {
    if (node->name) {
      rmw_free(const_cast<char *>(node->name));
    }
    rmw_node_free(node);
  }
  return nullptr;
}