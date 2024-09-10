std::string Partida::getXMLNivel() {
	XMLDocument doc;
	bool cargoArchivo = doc.LoadFile(idNiveles[contadorNiveles]);
	if (cargoArchivo == false) {
		std::cout << "\tError al abrir el archivo XML." << std::endl;
		return std::string();
	}
	TiXmlPrinter printer;
	printer.SetIndent("");
	printer.SetLineBreak("");
	doc.Accept(&printer);
	return printer.CStr();
}