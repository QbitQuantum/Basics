void in6_is_addr_mc_sitelocal(void) {
    int counter = 0;
    int swap_flag = 1;
    int tmp = 0;

    while(swap_flag == 1) {
        counter = 0;
        swap_flag = 0;

        while(counter < total_ip_addr - 1) {
            if((IN6_IS_ADDR_MC_SITELOCAL(&s6[print_to_ip[counter]]) == 1) &&
               (IN6_IS_ADDR_MC_SITELOCAL(&s6[print_to_ip[counter + 1]]) == 0)) {
                tmp = print_to_ip[counter];
                print_to_ip[counter] = print_to_ip[counter + 1];
                print_to_ip[counter + 1] = tmp;

                swap_flag = 1;
            }
            counter++;
        }
    }

    counter = 0;
    while(counter < total_ip_addr) {
        ip_to_print[print_to_ip[counter]] = counter;
        counter++;
    }

    return;
}