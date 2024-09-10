void ScummEngine_v2::o2_clearState08() {
	int obj = getActiveObject();
	putState(obj, getState(obj) & ~kObjectState_08);
	markObjectRectAsDirty(obj);
	clearDrawObjectQueue();
}