int main(int argc, char **argv) {

	Buffer*  buffer;

	if (argv[1] != NULL) {
		buffer = new Buffer(argv[1]);
	} else {
		buffer = new Buffer("../input/in.txt");
	}

	char c = '1';
	int i = 0;

	while (c != '\0') {
		i++;
		c = buffer->getChar();
		cout << c;
	}
}