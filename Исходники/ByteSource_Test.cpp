  static void Test_Scan() {
    s32 val;

    tester.Reset("123");
    assert(tester.Scan(val, Format::DEC));
    assert(val == 123);

    tester.Reset();
    assert(tester.Scan(val, Format::OCT));
    assert(val == 0123);

    tester.Reset();
    assert(tester.Scan(val, Format::HEX));
    assert(val == 0x123);

    tester.Reset();
    assert(tester.Scan(val, (Format::Type) 5));  // Base 5
    assert(val == 1*(5*5) + 2*(5) + 3);

    tester.Reset();
    assert(tester.Scan(val, (Format::Type) 36));  // Base 36 0..9a..z
    assert(val == 1*(36*36) + 2*(36) + 3);

    tester.Reset();
    assert(tester.Scan(val, Format::BIN));
    assert(val == 1);

    assert(!tester.Scan(val, Format::BIN));  // Looking at the 2
    assert(tester.Scan(val, Format::DEC));
    assert(val == 23);

    u32 uval;

    tester.Reset("deaDBEefs");
    assert(tester.Scan(uval, Format::HEX));
    assert(uval == 0xdeadbeef);
    assert(tester.Scan(uval, Format::BYTE));
    assert(uval == 's');
    assert(!tester.Scan(uval, Format::BYTE));
  }