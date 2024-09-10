static char *
parseIvalAst (ast *node, int *inCodeSpace) {
#define LEN 4096
    char *buffer = NULL;
    char *left, *right;

    if (IS_AST_VALUE(node)) {
        value *val = AST_VALUE(node);
        symbol *sym = IS_AST_SYM_VALUE(node) ? AST_SYMBOL(node) : NULL;
        if (inCodeSpace && val->type
                && (IS_FUNC(val->type) || IS_CODE(getSpec(val->type))))
        {
            *inCodeSpace = 1;
        }
        if (inCodeSpace && sym
                && (IS_FUNC(sym->type)
                    || IS_CODE(getSpec(sym->type))))
        {
            *inCodeSpace = 1;
        }

        DEBUGprintf ("%s: AST_VALUE\n", __FUNCTION__);
        if (IS_AST_LIT_VALUE(node)) {
            buffer = Safe_alloc(LEN);
            SNPRINTF(buffer, LEN, "0x%lx", AST_ULONG_VALUE (node));
        } else if (IS_AST_SYM_VALUE(node)) {
            assert ( AST_SYMBOL(node) );
            /*
            printf ("sym %s: ", AST_SYMBOL(node)->rname);
            printTypeChain(AST_SYMBOL(node)->type, stdout);
            printTypeChain(AST_SYMBOL(node)->etype, stdout);
            printf ("\n---sym %s: done\n", AST_SYMBOL(node)->rname);
            */
            buffer = Safe_strdup(AST_SYMBOL(node)->rname);
        } else {
            assert ( !"Invalid values type for initializers in AST." );
        }
    } else if (IS_AST_OP(node)) {
        DEBUGprintf ("%s: AST_OP\n", __FUNCTION__);
        switch (node->opval.op) {
        case CAST:
            assert (node->right);
            buffer = parseIvalAst(node->right, inCodeSpace);
            DEBUGprintf ("%s: %s\n", __FUNCTION__, buffer);
            break;
        case '&':
            assert ( node->left && !node->right );
            buffer = parseIvalAst(node->left, inCodeSpace);
            DEBUGprintf ("%s: %s\n", __FUNCTION__, buffer);
            break;
        case '+':
            assert (node->left && node->right );
            left = parseIvalAst(node->left, inCodeSpace);
            right = parseIvalAst(node->right, inCodeSpace);
            buffer = Safe_alloc(LEN);
            SNPRINTF(buffer, LEN, "(%s + %s)", left, right);
            DEBUGprintf ("%s: %s\n", __FUNCTION__, buffer);
            Safe_free(left);
            Safe_free(right);
            break;
        case '[':
            assert ( node->left && node->right );
            assert ( IS_AST_VALUE(node->left) && AST_VALUE(node->left)->sym );
            right = parseIvalAst(node->right, inCodeSpace);
            buffer = Safe_alloc(LEN);
            SNPRINTF(buffer, LEN, "(%s + %u * %s)",
                    AST_VALUE(node->left)->sym->rname, getSize(AST_VALUE(node->left)->type), right);
            Safe_free(right);
            DEBUGprintf ("%s: %s\n", __FUNCTION__, &buffer[0]);
            break;
        default:
            assert ( !"Unhandled operation in initializer." );
            break;
        }
    } else {
        assert ( !"Invalid construct in initializer." );
    }

    return (buffer);
}