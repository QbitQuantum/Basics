int main(int argc, char **argv) {

  Gtk::Main kit(argc, argv);

  InputParser parser(cin);
  _log("Parsing input...");
  Object json = parser.readBody();

  if (json.has<string>("lang")) {
    l10nLabels.setLanguage(json.get<string>("lang"));
  }

  string response;

  if (json.get<string>("protocol") != "https:") {
    ExtensionDialog dialog;
    response = dialog.error(ONLY_HTTPS_ALLOWED).json();
  } else {
    string type = json.get<string>("type");

    if (type == "SIGN") {
      string hashFromStdIn = json.get<String>("hash");
      string certId = json.get<String>("id");
      _log("signing hash: %s, with certId: %s", hashFromStdIn.c_str(), certId.c_str());
      Signer signer(hashFromStdIn, certId);
      response = signer.sign().json();
    } else if (type == "CERT") {
      CertificateSelection cert;
      response = cert.getCert().json();
    } else if (type == "VERSION") {
      VersionInfo version;
      response = version.getVersion().json();
    }
  }
  int responseLength = response.size();
  unsigned char *responseLengthAsBytes = intToBytesLittleEndian(responseLength);
  cout.write((char *) responseLengthAsBytes, 4);
  _log("Response(%i) %s ", responseLength, response.c_str());
  cout << response << endl;
  free(responseLengthAsBytes);
  return EXIT_SUCCESS;
}