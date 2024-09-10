int main(){
    std::string equation;
    std::getline(std::cin,equation,'\n');
    Parser parser(equation);
    Expr* e ;
    e = parser.expr();
    SExper sexper;

    e->accept(sexper);
    std::cout << std::endl;
}