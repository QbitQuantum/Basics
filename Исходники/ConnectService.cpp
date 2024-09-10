bool ConnectService::process(message_ptr const & message, connection_ptr const & connection)
{
	static Engine& engine = Engine::get_instance();
	if (message->type != MessageType::PING) return false;

	uint32_t id;
	_dec_declare2_(req, message->get_content_data(), message->get_content_size());
	_dec_get_var32_(req, id);
	if (!_dec_valid_(req))
	{
		DLOG(ERROR) << "Bad Ping format";
		return true;
	}

	NodeConf* config = (NodeConf*) engine.get_component(COMP_SERVERCONF).get();
	servernode_map::iterator it = config->nodes.find(id);
	if (it != config->nodes.end())
	{
		servernode_ptr node = it->second;
		connection->asyn = true;
		connection->authenticated = true;
		connection->data = node.get();
		connection->type = CT_S2S;
		node->connection = connection;
		node->state = READY;

		_enc_declare_(rep, 64);
		_enc_put_msg_header_(rep, MessageType::REPLY, message->id, 0);
		_enc_put_var32_(rep, ErrorCode::OK);
		_enc_update_msg_size_(rep);
		connection->send(_enc_data_(rep), _enc_size_(rep));
	}
	else
	{
		_enc_declare_(rep, 64);
		_enc_put_msg_header_(rep, MessageType::REPLY, message->id, 0);
		_enc_put_var32_(rep, ErrorCode::IS_NOT_FOUND);
		_enc_update_msg_size_(rep);
		connection->send(_enc_data_(rep), _enc_size_(rep));
	}
	return true;
}