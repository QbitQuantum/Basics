void loadGlobalMemoryFrom(std::istream& iss, RLMachine& machine) {
  using namespace boost::iostreams;
  filtering_stream<input> filtered_input;
  filtered_input.push(zlib_decompressor());
  filtered_input.push(iss);

  text_iarchive ia(filtered_input);
  System& sys = machine.system();
  int version;
  ia >> version;

  // Load global memory.
  ia >> machine.memory().global();

  // When Karmic Koala came out, support for all boost earlier than 1.36 was
  // dropped. For years, I had used boost 1.35 on Ubuntu. It turns out that
  // boost 1.35 had a serious bug in it, where it wouldn't save vectors of
  // primitive data types correctly. These global data files no longer load
  // correctly.
  //
  // After flirting with moving to Google protobuf (can't; doesn't handle
  // complex object graphs like GraphicsObject and its copy-on-write stuff),
  // and then trying to fix the problem in a forked copy of the serialization
  // headers which was unsuccessful, I'm just saying to hell with the user's
  // settings. Most people don't change these values and save games and global
  // memory still work (per above.)
  if (version == CURRENT_GLOBAL_VERSION) {
    ia >> sys.globals()
       >> sys.graphics().globals()
       >> sys.event().globals()
       >> sys.text().globals()
       >> sys.sound().globals();

    // Restore options which may have System specific implementations. (This
    // will probably expand as more of RealLive is implemented).
    sys.sound().restoreFromGlobals();
  }