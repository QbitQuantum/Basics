void tx(RCSwitch mySwitch, char* sCodeWord) {
	mySwitch.send(sCodeWord);
    cout << "Send code " << sCodeWord << endl;
}