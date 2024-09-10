int fpu_post_test_math2 (void)
{
    if (rintf (-1.5) != -2.0) {
        post_log ("Error in FPU math2 test\n");
        return -1;
    }
    return 0;
}