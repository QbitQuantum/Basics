void gWindow::debug() {
	printf("---- window stack (id=%d): ----\n", getId());
	for (unsigned i=0; i<subWindows.size; i++)
		printf("[gWindow] %p (id=%d)\n", (void*)subWindows.at(i), subWindows.at(i)->getId());
	puts("----");
}