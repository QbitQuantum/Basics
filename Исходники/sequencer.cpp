void
Sequencer::touch(){
  if (__time == 0) __time = clock();
  else{
	clock_t deltaT = clock() - __time;
	if (deltaT < __timestep) _sleep(__timestep-deltaT);
	__time = clock();
  }
}