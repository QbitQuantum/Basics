int main(int argc, char *argv[]) {
    while (gettoken() != EOF) {
        out[0] = '\0';

        if ((argc > 1) && (strcmp(argv[1], "-u") == 0)) {
            flag = 1;
            undcl();
            printf("%s\n", out);
        }

        else {
            strcpy(datatype, token);
            dcl();

            if (tokentype != '\n')
                printf("syntax error\n");

            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    return 0;
}