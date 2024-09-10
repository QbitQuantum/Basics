EpsilonNFA EpsilonNFA::generate(const shared_ptr<IRegex>& regex, const StateInfo& matchName)
{
    NFAGenerator generator(matchName);
    regex->accept(generator);
    return EpsilonNFA(generator);
}