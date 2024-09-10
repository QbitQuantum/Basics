void Parser::optimise_call(ExprNode *node)
{
    DBL result = 0.0;
    bool have_result = true;;

    if(node->op != OP_CALL)
        return;
    if(node->child == NULL)
        return;
    if(node->child->op != OP_CONSTANT)
        return;

    switch(node->call.token)
    {
        case SIN_TOKEN:
            result = sin(node->child->number);
            break;
        case COS_TOKEN:
            result = cos(node->child->number);
            break;
        case TAN_TOKEN:
            result = tan(node->child->number);
            break;
        case ASIN_TOKEN:
            result = asin(node->child->number);
            break;
        case ACOS_TOKEN:
            result = acos(node->child->number);
            break;
        case ATAN_TOKEN:
            result = atan(node->child->number);
            break;
        case SINH_TOKEN:
            result = sinh(node->child->number);
            break;
        case COSH_TOKEN:
            result = cosh(node->child->number);
            break;
        case TANH_TOKEN:
            result = tanh(node->child->number);
            break;
        case ASINH_TOKEN:
            result = asinh(node->child->number);
            break;
        case ACOSH_TOKEN:
            result = acosh(node->child->number);
            break;
        case ATANH_TOKEN:
            result = atanh(node->child->number);
            break;
        case ABS_TOKEN:
            result = fabs(node->child->number);
            break;
        case RADIANS_TOKEN:
            result = node->child->number * M_PI / 180.0;
            break;
        case DEGREES_TOKEN:
            result = node->child->number * 180.0 / M_PI;
            break;
        case FLOOR_TOKEN:
            result = floor(node->child->number);
            break;
        case INT_TOKEN:
            result = (int)(node->child->number);
            break;
        case CEIL_TOKEN:
            result = ceil(node->child->number);
            break;
        case SQRT_TOKEN:
            result = sqrt(node->child->number);
            break;
        case EXP_TOKEN:
            result = exp(node->child->number);
            break;
        case LN_TOKEN:
            if(node->child->number > 0.0)
                result = log(node->child->number);
            else
                Error("Domain error in 'ln'.");
            break;
        case LOG_TOKEN:
            if(node->child->number > 0.0)
                result = log10(node->child->number);
            else
                Error("Domain error in 'log'.");
            break;
        case MIN_TOKEN:
            have_result = false;
            break;
        case MAX_TOKEN:
            have_result = false;
            break;
        case ATAN2_TOKEN:
            have_result = false;
            break;
        case POW_TOKEN:
            have_result = false;
            break;
        case MOD_TOKEN:
            have_result = false;
            break;
        case SELECT_TOKEN:
            have_result = false;
            break;
        case FUNCT_ID_TOKEN:
            have_result = false;
            break;
        case VECTFUNCT_ID_TOKEN:
            have_result = false;
            break;
        default:
            have_result = false;
            break;
    }

    if(have_result == true)
    {
        POV_FREE(node->call.name);
        node->number = result;
        node->op = OP_CONSTANT;
        POV_FREE(node->child);
        node->child = NULL;
    }
}