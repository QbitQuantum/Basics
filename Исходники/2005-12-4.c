inline void mov_int32(int32 *value, int32 *rvalue, char pop_symbol)
{
    /* integer transfer function */
    if(pop_symbol) {
        /* perform post-evaluation operations*/
        switch(pop_symbol) {
        case '*':
            *value *= *rvalue;
            break;
        case '/':
            *value /= *rvalue;
            break;
        case '+':
            *value += *rvalue;
            break;
        case '-':
            *value -= *rvalue;
            break;
        case '%':
            *value %= *rvalue;
            break;
        case '&':
            *value &= *rvalue;
            break;
        case '|':
            *value |= *rvalue;
            break;
        case '<':
            *value<<= *rvalue;
            break;
        case '>':
            *value>>= *rvalue;
            break;
        case '~':
            *value  = ~*rvalue;
            break;
        case '!':
            *value  = factorial(*rvalue);
            break;
        case '^':
            *value  = (int32)pow(*value,*rvalue);
            break;
        case '=':
            *value  = labs(*rvalue);
            break;
        case ':':
            concatenate(value,*rvalue);
            break;
        default:
            *value = *rvalue;
        }
    } else /* there is no post-evaluation operator */