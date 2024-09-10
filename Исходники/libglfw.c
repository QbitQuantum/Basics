static int
lMakeContextCurrent(lua_State *L) {
	GLFWwindow * window = getwindow(L);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		return luaL_error(L, "Can't load GL");
	}

	return 0;
}