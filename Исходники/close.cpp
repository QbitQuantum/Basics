void worker(Chan<int> &jobs, Chan<int> &done)
{
	int j;
	while (jobs.recv(j) == esucc)
	{
		cout << "received job " << j << endl;
	}

	cout << "received all jobs" << endl;
	done.send(1);
}