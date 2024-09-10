    void XmlResultGenerator::generateAtom (StringBuffer& output, float value) const {
      if (value == 0.0) {
        output.appendText("0.0", 3);
        return;
      }

      int intType = _fpclass(value);

      switch (intType) {
        case _FPCLASS_PN:
        case _FPCLASS_NN:
        case _FPCLASS_NZ:
        case _FPCLASS_PZ: {
          output.appendDecimal(value);
          break;
        }
        case _FPCLASS_NINF: {
          generateAtom(output, "-INF");
          break;
        }
        case _FPCLASS_PINF: {
          generateAtom(output, "INF");
          break;
        }
        default: {
          generateAtom(output, "NAN");
          break;
        }
      }
    }