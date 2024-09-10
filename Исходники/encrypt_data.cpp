int main()
{
	string str_src = "abcdefghijklmnopq";
	string str_key = "key";
	vector<char> key;
	for (auto it = str_key.begin(); it != str_key.end(); it++)
	{
		key.push_back(*it);
	}

	vector<char> input;
	vector<char> output;

	Blowfish *tool = new Blowfish(key);	//设置密钥
	for (auto it : str_src)
	{
		input.push_back(it);
	}
	output = tool->Encrypt(input);	//加密后字串
	
	//解密没有直接处理string的方法，只有vector<char>的方法
	
	input.clear();
	for (auto it = output.begin(); it != output.end(); it++)
	//等效于
	//for (auto it : output)
	{
		input.push_back(*it);
	}

	output.clear();
	output = tool->Decrypt(input);
	return 0;
}