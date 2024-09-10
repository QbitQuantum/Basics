int main()
{
    Element* pElement = new ConcreteElementA();
    Visitor* pVisitor = new ConcreteVisitorA();
    pElement->accept(pVisitor);

    return 0;
}