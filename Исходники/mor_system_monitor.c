int main(int argc, char *argv[]) {
    FILE *pipe;
    int args = 0;
    char buffer[256] = { 0 };
    char url_buffer[4096] = { 0 };
    char encoded_url_buffer[4096] = { 0 };
    conf_t conf = { { 0 }, { 0 }, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    CURL *curl;
    CURLcode res;

    // check if debug is ON
    if(argc > 1) {
        if(strcmp(argv[1], "--debug") == 0) {
            DEBUG = 1;
        }
    }

    // get database configuration
    if(read_config(&conf)) {
        return 1;
    }

    // format beginning of URL
    strcat(encoded_url_buffer, conf.url);
    strcat(encoded_url_buffer, "?");

    if(DEBUG) {
        printf("System Info:\n\n");
    }

    if(conf.cpu_cores) {
        pipe = popen("cat /proc/cpuinfo | grep processor | wc -l", "r");
        fgets(buffer, 256, pipe);
        buffer[strlen(buffer) - 1] = 0;
        strcat(url_buffer, "cpu_cores=");
        strcat(url_buffer, buffer);
        args = 1;
        if(DEBUG) printf("cpu_cores = %s\n", buffer);
        fclose(pipe);
    }

    if(conf.cpu_load) {
        // save top output to tmp file
        pipe = popen("top -n 2 > /tmp/mor_top_tmp.txt", "r");

        // wait for 2 iterations to complete
        sleep(5);

        // read tmp file
        pipe = popen("cat /tmp/mor_top_tmp.txt | grep 'Cpu(s)' | tail -n+2 | sed 's/.*, *\\([0-9.]*\\)%\\id.*/\\1/' | awk '{print  100 - $5}'", "r");
        fgets(buffer, 256, pipe);
        buffer[strlen(buffer) - 1] = 0;
        if(args) strcat(url_buffer, "&");
        strcat(url_buffer, "cpu_load=");
        strcat(url_buffer, buffer);
        args = 1;
        if(DEBUG) printf("cpu_load = %s\n", buffer);
        fclose(pipe);

        // remove tpm file
        pipe = popen("rm -fr /tmp/mor_top_tmp.txt", "r");
        fclose(pipe);
    }

    if(conf.ram_total || conf.ram_free || conf.ram_used || conf.ram_buffers) {
        char var1[256];
        char var2[256];
        char var3[256];
        char var4[256];
        pipe = popen("free -k | grep -Po '\\d+' | head -n 5", "r");
        fscanf(pipe, "%s %s %s %s %s", var1, var2, var3, var4, var4);
        if(conf.ram_total) {
            if(args) strcat(url_buffer, "&");
            strcat(url_buffer, "ram_total=");
            strcat(url_buffer, var1);
            args = 1;
            if(DEBUG) printf("ram_total = %s\n", var1);
        }
        if(conf.ram_used) {
            if(args) strcat(url_buffer, "&");
            strcat(url_buffer, "ram_used=");
            strcat(url_buffer, var2);
            args = 1;
            if(DEBUG) printf("ram_used = %s\n", var2);
        }
        if(conf.ram_free) {
            if(args) strcat(url_buffer, "&");
            strcat(url_buffer, "ram_free=");
            strcat(url_buffer, var3);
            args = 1;
            if(DEBUG) printf("ram_free = %s\n", var3);
        }
        if(conf.ram_buffers) {
            if(args) strcat(url_buffer, "&");
            strcat(url_buffer, "ram_buffers=");
            strcat(url_buffer, var4);
            args = 1;
            if(DEBUG) printf("ram_buffers = %s\n", var4);
        }
        fclose(pipe);
    }

    if(conf.mysql) {
        pipe = popen("service mysqld status | grep -o 'running'", "r");;
        fgets(buffer, 256, pipe);
        buffer[strlen(buffer) - 1] = 0;
        if(args) strcat(url_buffer, "&");
        strcat(url_buffer, "mysql=");
        if(strcmp(buffer, "running") == 0) {
            strcat(url_buffer, "1");
            if(DEBUG) printf("mysql = 1\n");
        } else {
            strcat(url_buffer, "0");
            if(DEBUG) printf("mysql = 0\n");
        }
        args = 1;
        fclose(pipe);
    }

    if(conf.httpd) {
        pipe = popen("service httpd status | grep -o 'running'", "r");;
        fgets(buffer, 256, pipe);
        buffer[strlen(buffer) - 1] = 0;
        if(args) strcat(url_buffer, "&");
        strcat(url_buffer, "httpd=");
        if(strcmp(buffer, "running") == 0) {
            strcat(url_buffer, "1");
            if(DEBUG) printf("httpd = 1\n");
        } else {
            strcat(url_buffer, "0");
            if(DEBUG) printf("httpd = 0\n");
        }
        args = 1;
        fclose(pipe);
    }

    if(conf.asterisk) {
        pipe = popen("service asterisk status | grep -o 'running'", "r");;
        fgets(buffer, 256, pipe);
        buffer[strlen(buffer) - 1] = 0;
        if(args) strcat(url_buffer, "&");
        strcat(url_buffer, "asterisk=");
        if(strcmp(buffer, "running") == 0) {
            strcat(url_buffer, "1");
            if(DEBUG) printf("asterisk = 1\n");
        } else {
            strcat(url_buffer, "0");
            if(DEBUG) printf("asterisk = 0\n");
        }
        args = 1;
        fclose(pipe);
    }

    if(conf.hdd) {
        char pipe_buffer[256] = { 0 };

        sprintf(pipe_buffer, "df -h %s | grep -Po '[0-9]+%%' | sed 's|%%||'", conf.file_system);

        pipe = popen(pipe_buffer, "r");

        fgets(buffer, 256, pipe);
        buffer[strlen(buffer) - 1] = 0;
        if(args) strcat(url_buffer, "&");
        strcat(url_buffer, "hdd=");
        strcat(url_buffer, buffer);
        if(DEBUG) printf("hdd = %s\n", buffer);
        args = 1;
        fclose(pipe);
    }

    if(args) {
        encode_url(url_buffer, encoded_url_buffer);

        if(DEBUG) {
            printf("\nHTTP Request:\n\n");
            printf("%s\n\n", encoded_url_buffer);
        } else {
            FILE *curl_resp = tmpfile();

            curl_global_init(CURL_GLOBAL_ALL);
            curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, curl_resp);

            if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL, encoded_url_buffer);
                res = curl_easy_perform(curl);
                if(res != CURLE_OK) {
                    fprintf(stderr, "cURL error %d\n", res);
                }
            } else {
                fprintf(stderr, "Cannot initiate cURL\n");
                return 1;
            }

            curl_easy_cleanup(curl);
            curl_global_cleanup();

            fclose(curl_resp);
        }
    }

    return 0;
}