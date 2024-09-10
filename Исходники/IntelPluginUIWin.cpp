//Show just a message box
void errorMessage(std::string msg, std::string title)
{
	MessageBox(GetActiveWindow(), msg.c_str(), title.c_str(), MB_OK);
}