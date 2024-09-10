/*
 * General command function which sends the given characters to port
 * @param input an array of characters where each byte represents a byte
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::command(std::vector<char> &input) {

	return writePort(input);
}