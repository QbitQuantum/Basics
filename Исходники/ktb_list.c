static int
listKeyContext (ListGenerationData *lgd, const KeyContext *ctx, const wchar_t *keysPrefix) {
  {
    const HotkeyEntry *hotkey = ctx->hotkeyTable;
    unsigned int count = ctx->hotkeyCount;

    while (count) {
      if (!(hotkey->flags & HKF_HIDDEN)) {
        if (!listHotkeyEvent(lgd, &hotkey->keyValue, "press", hotkey->pressCommand)) return 0;
        if (!listHotkeyEvent(lgd, &hotkey->keyValue, "release", hotkey->releaseCommand)) return 0;
      }

      hotkey += 1, count -= 1;
    }
  }

  {
    const KeyBinding *binding = ctx->keyBindingTable;
    unsigned int count = ctx->keyBindingCount;

    while (count) {
      if (!(binding->flags & KBF_HIDDEN)) {
        size_t keysOffset;

        if (!putCommandDescription(lgd, binding->command, !binding->combination.anyKeyCount)) return 0;
        if (!putCharacterString(lgd, WS_C(": "))) return 0;
        keysOffset = lgd->lineLength;

        if (keysPrefix) {
          if (!putCharacterString(lgd, keysPrefix)) return 0;
          if (!putCharacterString(lgd, WS_C(", "))) return 0;
        }

        if (!putKeyCombination(lgd, &binding->combination)) return 0;

        if ((binding->command & BRL_MSK_BLK) == BRL_BLK_CONTEXT) {
          const KeyContext *c = getKeyContext(lgd->keyTable, (KTB_CTX_DEFAULT + (binding->command & BRL_MSK_ARG)));
          if (!c) return 0;

          {
            size_t length = lgd->lineLength - keysOffset;
            wchar_t keys[length + 1];

            wmemcpy(keys, &lgd->lineCharacters[keysOffset], length);
            keys[length] = 0;
            lgd->lineLength = 0;

            if (isTemporaryKeyContext(lgd->keyTable, c)) {
              if (!listKeyContext(lgd, c, keys)) return 0;
            } else {
              if (!putCharacterString(lgd, WS_C("switch to "))) return 0;
              if (!putCharacterString(lgd, c->title)) return 0;
              if (!putCharacterString(lgd, WS_C(": "))) return 0;
              if (!putCharacterString(lgd, keys)) return 0;
              if (!endLine(lgd)) return 0;
            }
          }
        } else {
          if (!endLine(lgd)) return 0;
        }
      }

      binding += 1, count -= 1;
    }
  }

  if (!listKeyboardFunctions(lgd, ctx)) return 0;
  return 1;
}