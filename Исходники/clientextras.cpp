void renderscore(dynent *d)
{
    sprintf_sd(lag)("%d", d->plag);
    sprintf_sd(name) ("(%s)", d->name); 
    sprintf_s(scorelines.add().s)("%d\t%s\t%d\t%s\t%s", d->frags, d->state==CS_LAGGED ? "LAG" : lag, d->ping, d->team, d->state==CS_DEAD ? name : d->name);
    menumanual(0, scorelines.length()-1, scorelines.last().s); 
};