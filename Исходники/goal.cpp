void* GoalObject::operator new (size_t ourSize) {

	void *result = missionHeap->Malloc(ourSize);
	return(result);
}