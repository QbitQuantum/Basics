typename GeneralQuestion::type ask(const Visitable& v)
{
    GeneralQuestion t;

    v.accept(t);

    return t.answer;

}