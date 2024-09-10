void displayAndEmptyQueue(Queue<T> q)
{
	while(q.size() > 0)
	{
		cout << q.get() << " ";
		q.remove();
	}
	cout << "\n";
}