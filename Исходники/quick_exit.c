// Test procedure for quick_exit()
int main()
{
    // Attempt to exit using quick_exit
    quick_exit(EXIT_SUCCESS);

    // Return failure
    return EXIT_FAILURE;
}