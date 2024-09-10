int main(int argc, char *argv[])
{
    char **args = alloca(sizeof(char*) * (argc+12));
    int i, j;

    char execpath[PATH_MAX+1];
    char sdkpath[PATH_MAX+1];
    char codesign_allocate[64];
    char osvermin[64];

    char *compiler;
    char *target;

    char *sdk;
    char *cpu;
    char *osmin;

    target_info(argv, &target, &compiler);
    if (!get_executable_path(execpath, sizeof(execpath))) abort();
    snprintf(sdkpath, sizeof(sdkpath), "%s/../SDK", execpath);
 
    snprintf(codesign_allocate, sizeof(codesign_allocate),
             "%s-codesign_allocate", target);

    setenv("CODESIGN_ALLOCATE", codesign_allocate, 1);
    setenv("IOS_FAKE_CODE_SIGN", "1", 1);

    env(&sdk, "IOS_SDK_SYSROOT", sdkpath);
    env(&cpu, "IOS_TARGET_CPU", TARGET_CPU);

    env(&osmin, "IPHONEOS_DEPLOYMENT_TARGET", OS_VER_MIN);
    unsetenv("IPHONEOS_DEPLOYMENT_TARGET");

    snprintf(osvermin, sizeof(osvermin), "-miphoneos-version-min=%s", osmin);

    for (i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-arch"))
        {
            cpu = NULL;
            break;
        }
    }

    i = 0;

    args[i++] = compiler;
    args[i++] = "-target";
    args[i++] = target;
    args[i++] = "-isysroot";
    args[i++] = sdk;

    if (cpu)
    {
        args[i++] = "-arch";
        args[i++] = cpu;
    }

    args[i++] = osvermin;
    args[i++] = "-mlinker-version=241.9";

    for (j = 1; j < argc; ++i, ++j)
        args[i] = argv[j];

    args[i] = NULL;

    setenv("COMPILER_PATH", execpath, 1);
    execvp(compiler, args);

    fprintf(stderr, "cannot invoke compiler!\n");
    return 1;
}