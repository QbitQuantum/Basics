AbstractState::TransitionResult PS0::Transition(AbstractStateMachine &machine, const Symbol & symbol)
{
    AbstractState::TransitionResult ret = AbstractState::UNEXPECTED;
    switch (symbol.code) {
    case S_CONST:///< mot-clé 'const'
        machine.Reduce(SYM_LD, RULE_3);
        ret = AbstractState::REDUCED;
        break;
    case S_VAR:///< mot-clé 'var'
        machine.Reduce(SYM_LD, RULE_3);
        ret = AbstractState::REDUCED;
        break;
    case S_READ:///< 'lire'
        machine.Reduce(SYM_LD, RULE_3);
        ret = AbstractState::REDUCED;
        break;
    case S_WRITE:///< 'ecrire'
        machine.Reduce(SYM_LD, RULE_3);
        ret = AbstractState::REDUCED;
        break;
    case S_ID:///< identifiant '\w[\w\d]*'
        machine.Reduce(SYM_LD, RULE_3);
        ret = AbstractState::REDUCED;
        break;
    case S_LD:///< liste de déclarations
        machine.PileUp(symbol, new PS1());
        ret = AbstractState::PILED_UP;
        break;
    case S_EOF:///< Fin du fichier
        ret = AbstractState::ACCEPT;
        break;
    default:
        machine.Unexpected(AbstractStateMachine::ERROR, "Program must begin with one of the following keywords 'const', 'var' or 'ecrire'");
        break;
    }
    return ret;

}