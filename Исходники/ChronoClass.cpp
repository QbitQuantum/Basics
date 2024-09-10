void ChronoClass::increaseSystem(){
	if(systemTime != GetTickCount()){
		systemTime = GetTickCount();
		increase();
	}
}