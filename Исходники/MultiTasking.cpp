void MultiTasking::start() {
	Process proc = Process();
	processList.add(proc);
	initTimer(10);
}