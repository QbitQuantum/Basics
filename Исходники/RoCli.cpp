RoOptionalUtf8 RoCli::ReadString(std::string message, bool isPassword, optional<RoButtonSoundPtr> buttonSound)
{
    return ReadRaw(message, isPassword, TEXT_SPECIAL_CHARS, buttonSound);
}