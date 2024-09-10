int RlBabelDLL::callDLL(RLMachine& machine, int func, int arg1, int arg2,
                        int arg3, int arg4) {
  switch (func) {
    case dllInitialise:
      return initialize(arg1, arg2);
    case dllTextoutStart:
      if (arg1 == -1) {
        textoutClear();
        return 1;
      } else {
        textoutClear();
        return textoutAdd(*getSvar(arg1));
      }
    case dllTextoutAppend:
      return textoutAdd(*getSvar(arg1));
    case dllTextoutGetChar:
      return textoutGetChar(getSvar(arg1), getIvar(arg2));
    case dllTextoutNewScreen:
      return startNewScreen(*getSvar(arg1));
    case dllSetNameMod: {
      boost::shared_ptr<TextWindow> textWindow = getWindow(arg1);
      int original_mod = textWindow->nameMod();
      textWindow->setNameMod(arg2);
      return original_mod;
    }
    case dllGetNameMod:
      return getWindow(arg1)->nameMod();
    case dllGetTextWindow:
      return getWindow(-1)->windowNumber();
    case dllSetWindowName:
      return setCurrentWindowName(getSvar(arg1));
    case endSetWindowName:
    case endGetCharWinNam: {
      // Should never happen since we don't do the insane trick of overwriting
      // instruction memory to set the name of set the window name.
      return getcError;
    }
    case dllClearGlosses:
      return clearGlosses();
    case dllNewGloss:
      return newGloss();
    case dllAddGloss:
      return addGloss(*getSvar(arg1));
    case dllTestGlosses:
      return testGlosses(arg1, arg2, getSvar(arg3), arg4);
    case dllGetRCommandMod: {
      int window = getWindow(arg1)->windowNumber();
      return machine.system().gameexe()("WINDOW")(window)("R_COMMAND_MOD");
    }
    case dllMessageBox:
      //      return rlMsgBox(arg1, arg2);
    default:
      return -1;
  }
}