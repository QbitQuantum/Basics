/*
Open connection dialog with TreeItem data to CREATE a brand-new connection.
*/
void ConnectionsDock::_open_connection_dialog(TreeItem &item) {

	String signal = item.get_metadata(0).operator Dictionary()["name"];
	String signalname = signal;
	String midname = selectedNode->get_name();
	for (int i = 0; i < midname.length(); i++) { //TODO: Regex filter may be cleaner.
		CharType c = midname[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
			if (c == ' ') {
				//Replace spaces with underlines.
				c = '_';
			} else {
				//Remove any other characters.
				midname.remove(i);
				i--;
				continue;
			}
		}
		midname[i] = c;
	}

	Node *dst_node = selectedNode->get_owner() ? selectedNode->get_owner() : selectedNode;
	StringName dst_method = "_on_" + midname + "_" + signal;

	Connection c;
	c.source = selectedNode;
	c.signal = StringName(signalname);
	c.target = dst_node;
	c.method = dst_method;

	connect_dialog->init(c);
	connect_dialog->set_title(TTR("Connect Signal: ") + signalname);
	connect_dialog->popup_centered_ratio();
}