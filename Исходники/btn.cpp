static void btn_onpress(void)
{
    /* attempt copy from box_challenge context
     * we know the context is properly aligned so we try to obtain a carbon copy
     * of its memory location */
    pc.printf("attempting to read the secret...");
    memcpy(&g_challenge, g_box_context, sizeof(g_challenge));
    pc.printf(" done\n\r");
}