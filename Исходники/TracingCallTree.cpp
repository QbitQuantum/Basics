void TracingCallTree::UpdateCycleTime(TracingCallTreeElem * prevActiveElem, TracingCallTreeElem* nextActiveElem){
	BOOL suc = QueryThreadCycleTime(_osThreadHandle,&nextActiveElem->LastCycleTime);
	CheckError2(suc);
	prevActiveElem->CycleTime += nextActiveElem->LastCycleTime - prevActiveElem->LastCycleTime;
}