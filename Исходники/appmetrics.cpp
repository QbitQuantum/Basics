static std::string toStdString(Local<String> s) {
	char *buf = new char[s->Length() + 1];
	s->WriteUtf8(buf);
	std::string result(buf);
	delete[] buf;
	return result;
}