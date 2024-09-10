std::string errno_str()
{
    char buffer[1024];
    errno_t e = strerror_s(buffer, sizeof(buffer), errno);
    if (e == 0) {
	return buffer;
    }
    return "errno:" + std::to_string(errno);
}