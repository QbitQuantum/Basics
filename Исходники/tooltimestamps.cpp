int main(int, char **, char **) {
    Print printf(Platform::instance().output());
    CommonEra ce;
    ce.fromNow();
    ce.show();
    LocalTime lt;
    lt.fromCommonEra(ce);
    lt.show();
    TimeStamp ts;
    printf("UTC iso8601:       %s\n", ts.iso8601(ce));
    printf("UTC milspec:       %s\n", ts.milspec(ce));
    printf("UTC civilian:      %s\n", ts.civilian(ce));
    printf("UTC log:           %s\n", ts.log(ce));
    printf("UTC formal:        %s\n", ts.formal(ce));
    printf("UTC highprecision: %s\n", ts.highprecision(ce));
    printf("LCT iso8601:       %s\n", ts.iso8601(lt));
    printf("LCT milspec:       %s\n", ts.milspec(lt));
    printf("LCT civilian:      %s\n", ts.civilian(lt));
    printf("LCT log:           %s\n", ts.log(lt));
    printf("LCT formal:        %s\n", ts.formal(lt));
    printf("LCT highprecision: %s\n", ts.highprecision(lt));

    std::exit(0);
}