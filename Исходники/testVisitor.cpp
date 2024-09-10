int main(int argc, char *argv[])
{
    Visitor *vis = new ConcreteVisitorB();
    Element *elm = new ConcreteElementB();
    elm->Accept(vis);

    system("pause");
    return 0;
}