int main()
{
	Chan<string> chan = make_chan<string>();

	cout << "starting ping" << endl;
	std::thread ping_thread(ping, std::ref(chan));
	ping_thread.detach();

	string res;
	while (chan.recv(res) != epipe)
		cout << "received: " << res << endl;

	return 0;
}