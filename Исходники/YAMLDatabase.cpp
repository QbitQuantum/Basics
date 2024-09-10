		bool set_fields_if_equals(doid_t do_id, const map_t &equals, map_t &values)
		{
			m_log->trace() << "Setting fields if equals on obj-" << do_id << endl;

			YAML::Node document;
			if(!load(do_id, document))
			{
				values.clear();
				return false;
			}

			// Get current field values from the file
			const Class* dcc = g_dcf->get_class_by_name(document["class"].as<string>());
			ObjectData dbo(dcc->get_id());
			YAML::Node existing = document["fields"];
			for(auto it = existing.begin(); it != existing.end(); ++it)
			{
				const Field* field = dcc->get_field_by_name(it->first.as<string>());
				if(!field)
				{
					m_log->warning() << "Field '" << it->first.as<string>()
					                 << "', loaded from '" << filename(do_id)
					                 << "', does not exist." << endl;
					continue;
				}
				vector<uint8_t> value = read_yaml_field(field, it->second, do_id);
				if(value.size() > 0)
				{
					dbo.fields[field] = value;
				}
			}

			// Check if equals matches current values
			bool fail = false;
			for(auto it = equals.begin(); it != equals.end(); ++it)
			{
				auto found = dbo.fields.find(it->first);
				if(found == dbo.fields.end())
				{
					values.erase(it->first);
					fail = true;
				}
				else if(it->second != found->second)
				{
					values.erase(it->first);
					fail = true;
				}
			}

			// Return current values on failure
			if(fail)
			{
				for(auto it = values.begin(); it != values.end(); ++it)
				{
					it->second = dbo.fields[it->first];
				}
				return false;
			}

			// Update existing values on success
			for(auto it = values.begin(); it != values.end(); ++it)
			{
				dbo.fields[it->first] = it->second;
			}
			write_yaml_object(do_id, dcc, dbo);
			return true;
		}