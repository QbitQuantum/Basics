 void freeNode(Node *node)
{
    size_t i;
    for (i = 0; node->children[i]; i++)
        freeNode(node->children[i]);
    if (node->tok)
        freeToken(node->tok);
    free(node);
}