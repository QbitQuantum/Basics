int JS_setcursor(duk_context *ctx) {
	int cx = duk_get_int(ctx, 0);
	int cy = duk_get_int(ctx, 1);

	JS_window.setCursor(cx, cy);

	return 0;
}