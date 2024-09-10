JS_BINDED_FUNC_IMPL(FakeAudio, removeEventListener) {
	JS::CallArgs args = CallArgsFromVp(argc, vp);
	if (args.length() >= 2) {
		// need to think this through
	}
	return JS_TRUE;
}