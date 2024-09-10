/**
  * Konstruktor podminky, ktery nastavy typ a promenne.
  *
  * @param var1 prvni promenna podminky
  * @param op operator podminky
  * @param var2 druha promenna podminky
  */
Constraint::Constraint(QString var1, int op, QString var2)
{
    first = var1;
    second_var = var2; //ulozim jako promennou
    if (op < 0 || op > 5) { //operator je cislo (dle enum) 0-5
        qCritical() << "Error: bad operator in condition in XML";
        return;
    }
    this->op = Operators(op); //prevedu na enum
    type = TYPEVAR; //druhe cislo je "promenna"
}