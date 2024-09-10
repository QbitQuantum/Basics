bool EasyUtil::Base64Decode(const std::string &sInput, string &sOutput)
{
	std::string temp;
	temp.resize(modp_b64_decode_len(sInput.size()));

	// does not null terminate result since result is binary data!
	int input_size = static_cast<int>(sInput.size());
	int output_size = modp_b64_decode(&(temp[0]), sInput.data(), input_size);
	if (output_size < 0)
		return false;

	temp.resize(output_size);
	sOutput.swap(temp);

	return true;
}