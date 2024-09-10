int main(int argc, char *argv[])
{
    for (unsigned i = 0; i < 0x8000; ++i)
    {
        cache.clear();
        printf("\rguessing ver(4, 1, %5d) = ", i);
        fflush(stdout);
        unsigned guess = ver(4, 1, i);
        printf("%5d", guess);
        if (guess == 6)
        {
            printf("\nFound solution!\n");
            break;
        }
    }

    return 0;
}