void end_time(CS207::Clock t){
	cout << "Time: " << chrono::duration_cast<chrono::nanoseconds>(t.elapsed()).count() << '\n';
}