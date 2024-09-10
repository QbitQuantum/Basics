// <factor>          ::= <number_literal> | <identifier> | ( <bool_expression> )
void Factor(CPU *cpu, Files file){
    if(Peek('(', file)){
        Match('(', file);
        Boolean::Expression(cpu, file);
        Match(')', file);
    }
    else if(IsDigit(Peek())){
        cpu->LoadNumber(GetNumber(file));
    }
    else if(IsAlpha(Peek()))
        Identifier(cpu, file);
    else
        Abort("Internal Error. FIXME!", file);
}