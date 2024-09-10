char TOpt::GetCharOr0() const {
    if (Chars_.empty())
        return 0;
    return GetChar();
}