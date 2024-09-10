void serialize(serializer &s, const std::string &key, const autocorr_result<T> &self)
{
    internal::check_valid(self);
    internal::serializer_sentry group(s, key);

    // Write size and nlevel as 64-bit integers for consistency
    serialize(s, "@size", static_cast<uint64_t>(self.size()));
    serialize(s, "@nlevel", static_cast<uint64_t>(self.nlevel()));

    s.enter("level");
    for (size_t i = 0; i != self.nlevel(); ++i)
        serialize(s, std::to_string(i), self.level_[i]);
    s.exit();

    s.enter("mean");
    serialize(s, "value", self.mean());
    serialize(s, "error", self.stderror());
    s.exit();
}