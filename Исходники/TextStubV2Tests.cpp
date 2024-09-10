TEST(TBDv2, ReadFile2) {
  static const char tbd_v2_file2[] =
      "--- !tapi-tbd-v2\n"
      "archs: [ armv7, armv7s, armv7k, arm64 ]\n"
      "platform: ios\n"
      "flags: [ flat_namespace, not_app_extension_safe ]\n"
      "install-name: Test.dylib\n"
      "swift-version: 1.1\n"
      "exports:\n"
      "  - archs: [ armv7, armv7s, armv7k, arm64 ]\n"
      "    symbols: [ _sym1, _sym2, _sym3, _sym4, $ld$hide$os9.0$_sym1 ]\n"
      "    objc-classes: [ _class1, _class2 ]\n"
      "    objc-ivars: [ _class1._ivar1, _class1._ivar2 ]\n"
      "    weak-def-symbols: [ _weak1, _weak2 ]\n"
      "    thread-local-symbols: [ _tlv1, _tlv2 ]\n"
      "  - archs: [ armv7, armv7s, armv7k ]\n"
      "    symbols: [ _sym5 ]\n"
      "    objc-classes: [ _class3 ]\n"
      "    objc-ivars: [ _class1._ivar3 ]\n"
      "    weak-def-symbols: [ _weak3 ]\n"
      "    thread-local-symbols: [ _tlv3 ]\n"
      "undefineds:\n"
      "  - archs: [ armv7, armv7s, armv7k, arm64 ]\n"
      "    symbols: [ _undefSym1, _undefSym2, _undefSym3 ]\n"
      "    objc-classes: [ _undefClass1, _undefClass2 ]\n"
      "    objc-ivars: [ _undefClass1._ivar1, _undefClass1._ivar2 ]\n"
      "    weak-ref-symbols: [ _undefWeak1, _undefWeak2 ]\n"
      "...\n";

  auto Buffer = MemoryBuffer::getMemBuffer(tbd_v2_file2, "Test.tbd");
  auto Result = TextAPIReader::get(std::move(Buffer));
  EXPECT_TRUE(!!Result);
  auto File = std::move(Result.get());
  EXPECT_EQ(FileType::TBD_V2, File->getFileType());
  auto Archs = AK_armv7 | AK_armv7s | AK_armv7k | AK_arm64;
  EXPECT_EQ(Archs, File->getArchitectures());
  EXPECT_EQ(PlatformKind::iOS, File->getPlatform());
  EXPECT_EQ(std::string("Test.dylib"), File->getInstallName());
  EXPECT_EQ(PackedVersion(1, 0, 0), File->getCurrentVersion());
  EXPECT_EQ(PackedVersion(1, 0, 0), File->getCompatibilityVersion());
  EXPECT_EQ(2U, File->getSwiftABIVersion());
  EXPECT_EQ(ObjCConstraintType::Retain_Release, File->getObjCConstraint());
  EXPECT_FALSE(File->isTwoLevelNamespace());
  EXPECT_FALSE(File->isApplicationExtensionSafe());
  EXPECT_FALSE(File->isInstallAPI());
  EXPECT_EQ(0U, File->allowableClients().size());
  EXPECT_EQ(0U, File->reexportedLibraries().size());
}