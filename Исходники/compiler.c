static struct parseNode *getParseTreeVar(struct parserState *ps)
{
    struct parseNode *result=NULL,*next,*ptr;
    int y;
    char *name;
    if(ps->token[0]=='}' || ps->token[0]==0)
        return NULL;
    name=copystr(ps->token);
    result=newNode(9);
    result->lineno=ps->lineno;

    next=newNode(0);
    next->lineno=ps->lineno;
    next->dat.s=name;
    result->dat.n=next;
    ptr=next;
    y=getToken(ps);
    if(y!=NameToken && ps->token[0]!='(')
    {
        state=y;
        error("Error! Method or variable name expected at %d, found %s\n"
              ,ps->lineno,ps->token);
        return result;
    }
    if(y==NameToken)
    {
        result->type=7;
        name=copystr(ps->token);
        next=newNode(0);
        next->lineno=ps->lineno;
        next->dat.s=name;
        ptr->next=next;
        ptr=next;
        y=getToken(ps);
    }
    if(ps->token[0]=='(')
    {
        ptr->next=getParseTreeMethod(ps);
    }
    else
    {
        result->type=5;
        while(ps->token[0]==',')
        {
            y=getToken(ps);
            if(y!=NameToken)
            {
                error("Error! Variable name expected at %d, found %s\n"
                      ,ps->lineno,ps->token);
                return result;
            }
            name=copystr(ps->token);
            next=newNode(0);
            next->lineno=ps->lineno;
            next->dat.s=name;
            ptr->next=next;
            ptr=next;
            y=getToken(ps);
        }
        if(ps->token[0]!=';')
        {
            error("Error! Semicolon ; expected at %d\n",ps->lineno);
            return result;
        }
        y=getToken(ps);
        state=y;
    }
    return result;
}