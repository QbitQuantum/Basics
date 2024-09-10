Constante& Rationnel::sinush()const
{
    Reel* res = new Reel(sinh((float)num/den));
    return *res;
}