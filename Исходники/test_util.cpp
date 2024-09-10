std::string getCACertificateContent() {
  std::string content;
  readFile(fs::path(kTestDataPath) / "test_cert.pem", content);
  return content;
}