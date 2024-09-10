void hash_test(shared_ptr<redis::client>& c) {
	c->flushall();
	c->select(14);

	//hset
	c->hset("hash1", "key1", "val1");
	c->hset("hash1", "key2", "val2");
	c->hset("hash1", "key3", "val3");
	assert(c->exists("hash1") == true);
	assert(c->type("hash1") == redis::client::datatype_hash);
	assert(c->hlen("hash1") == 3L);

	//hget
	assert(c->hget("hash1", "key1") == "val1");

	//hsetnx
	assert(c->hsetnx("hash1", "key1", "val1_invalid") == false);
	assert(c->hget("hash1", "key1") == "val1");
	assert(c->hsetnx("hash1", "key4", "val4") == true);
	assert(c->hget("hash1", "key4") == "val4");

	redis::client::string_pair_vector content;
	//hmset
	content.push_back(make_pair("key1", "val1"));
	content.push_back(make_pair("key2", "val2"));
	content.push_back(make_pair("key3", "val3"));
	c->hmset("hash2", content);

	//hmget
	redis::client::string_vector fields;
	fields.push_back("key1");
	fields.push_back("key2");
	fields.push_back("key3");
	fields.push_back("key4");

	redis::client::string_vector values;
	c->hmget("hash2", fields, values);

	for (size_t i = 0; i < fields.size(); i++) {
		if (content.size() > i) {
			assert(values[i] == content[i].second);
		} else {
			assert(values[i] == redis::client::missing_value());
		}
	}

	//hincrby
	c->hset("hash3", "key1", "1");
	long l;
	l = c->hincrby("hash3", "key1", 1);
	assert(l == 2L);
	l = c->hincrby("hash3", "key2", 1);
	assert(l == 1L);
	l = c->hincrby("hash3", "key3", -3);
	assert(l == -3L);

	string s;
	s = c->hget("hash3", "key1");
	assert(s == "2");
	s = c->hget("hash3", "key2");
	assert(s == "1");

	//hexists
	assert(c->hexists("hash3", "key1"));
	assert(!c->hexists("hash3", "key4"));

	//hdel
	assert(c->hdel("hash3", "key1"));
	assert(!c->hexists("hash3", "key1"));
	assert(!c->hdel("hash3", "key4"));
	assert(!c->hexists("hash3", "key4"));

	c->hset("hash3", "key1", "val1");

	//hlen
	assert(c->hlen("hash3") == 3);
	assert(c->hlen("hash4") == 0);

	//hkeys
	fields.clear();
	c->hkeys("hash3", fields);
	assert(fields.size() == 3);
	std::sort(fields.begin(), fields.end());
	assert(fields[0] == "key1");
	assert(fields[1] == "key2");
	assert(fields[2] == "key3");

	values.clear();
	c->hvals("hash1", values);
	assert(values.size() == 4);
	std::sort(values.begin(), values.end());
	for (size_t i = 0; i < values.size(); i++) {
		assert(values[i] == "val" + lexical_cast<string>(i + 1));
	}

	//hgetall
	redis::client::string_pair_vector entries;
	c->hgetall("hash1", entries);
	std::sort(entries.begin(), entries.end());
	for (size_t i = 0; i < entries.size(); i++) {
		assert(entries[i].first == "key" + lexical_cast<string>(i + 1));
		assert(entries[i].second == "val" + lexical_cast<string>(i + 1));
	}
}