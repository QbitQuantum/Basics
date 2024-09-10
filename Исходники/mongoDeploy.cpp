/** Try to connect every 2 secs until successful. Give up after maxSecs (60 secs by default) */
mongoDeploy::Connection mongoDeploy::waitConnect (string hostPort, unsigned maxSecs) {
	unsigned secs = 0;
	while (true)
		try {
			Connection c (new mongo::DBClientConnection);
			c->connect (hostPort);
			return c;
		} catch (exception &e) {
			if (secs >= maxSecs) except::raise (e);
			thread::sleep (2);
			secs += 2;
		}
}