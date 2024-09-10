void daemon_main() {
	chdir("/home/pi/Pokecan/display");
	execlp("/usr/bin/python", "python", "display.py");
}