// ////////////////////////////////////////////////////////////////////////////
bool InsContext::CheckContext(std::vector<std::string> &error_list) const
{
	typedef std::map<unsigned int, unsigned int>  DVMap;
	typedef DVMap::iterator                       DVMapIter;
	typedef DVMap::const_iterator                 DVMapIterC;
	typedef std::pair<unsigned int, unsigned int> DVMapPair;

	unsigned int ins_item_count   =
		static_cast<unsigned int>(ins_item_list_.size());
	unsigned int dict_value_count =
		static_cast<unsigned int>(dict_value_list_.size());

	unsigned int             count_1;
	DVMap                    dv_map;
	std::vector<std::string> tmp_error_list;

	for (count_1 = 0; count_1 < ins_item_count; ++count_1) {
		const InsItem     &this_item(ins_item_list_[count_1]);
		std::stringstream  item_text;
		item_text << "Error in instruction item index " << count_1 << ", fid " <<
			this_item.auxiliary_id_ << " ('" <<
			this_item.field_name_ << "') with parent index " <<
			this_item.parent_index_ << ": ";
		try {
			if (this_item.parent_index_ >= ins_item_count) {
				std::ostringstream o_str;
				o_str << "The parent index (" << this_item.parent_index_ <<
					") is not less than the number of instruction items (" <<
					ins_item_count << ").";
				tmp_error_list.push_back(item_text.str() + o_str.str());
			}
			if ((count_1 + this_item.element_count_) > ins_item_count) {
				std::ostringstream o_str;
				o_str << "The item index plus the element count (" << count_1 <<
					" + " << this_item.element_count_ << " = " <<
					(count_1 + this_item.element_count_) << ") is greater "
					"than number of instruction items (" << ins_item_count << ").";
				tmp_error_list.push_back(item_text.str() + o_str.str());
			}
			if (this_item.field_operator_ == FieldOperator_None) {
				if ((this_item.dict_value_index_) &&
					(this_item.data_type_ != DataType_Template)) {
					std::ostringstream o_str;
					o_str << "The field has an operator of 'None', but the "
						"dictionary value index is " <<
						this_item.dict_value_index_ << " (should be 0).";
					tmp_error_list.push_back(item_text.str() + o_str.str());
				}
				if ((this_item.dict_value_count_) &&
					(this_item.data_type_ != DataType_Template)) {
					std::ostringstream o_str;
					o_str << "The field has an operator of 'None', but the "
						"dictionary value count is " <<
						this_item.dict_value_count_ << " (should be 0).";
					tmp_error_list.push_back(item_text.str() + o_str.str());
				}
			}
			else {
				if (!this_item.dict_value_count_) {
					std::ostringstream o_str;
					o_str << "The field has an operator of '" <<
						this_item.field_operator_ << "', but the dictionary value "
						"count is 0.";
					tmp_error_list.push_back(item_text.str() + o_str.str());
				}
				else if ((this_item.dict_value_index_ +
					this_item.dict_value_count_) > dict_value_count) {
					std::ostringstream o_str;
					o_str << "The dictionary value index plus the dictionary value "
						"count (" << this_item.dict_value_index_ << " + " <<
						this_item.dict_value_count_ << " = " <<
						(this_item.dict_value_index_ + this_item.dict_value_count_) <<
						") is greater than number of dictionary values (" <<
						dict_value_count << ").";
					tmp_error_list.push_back(item_text.str() + o_str.str());
				}
			}
		}
		catch (const std::exception &except) {
			tmp_error_list.push_back(item_text.str() + except.what());
		}
	}

	error_list.swap(tmp_error_list);

	return(error_list.empty());
}