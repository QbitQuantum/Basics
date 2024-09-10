int main (int argc, char *argv[])
{
    if (argc > 1) {
        unexpected_handler save = set_unexpected (handler);

        return save == handler;
    }

    return 0;
}