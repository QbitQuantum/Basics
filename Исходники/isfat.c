//
// Tests if a file name (WITHOUT PATH) is FAT compliant
// 1 - FAT compliant
// 0 - non FAT compliant
//
// ... could be better but seems to work !
//
int isfat(pchar component) {
    int len = strlen(component);
    int i, j, pos;


    if (strcmp(component, ".") == 0) {          // "."
        return 1;
    }

    if (strcmp(component, "..") == 0) {         // ".."
        return 1;
    }

    if ((len > 12) || (len == 0)) {
        return 0;                   // lenght > 8.3 or null
    }

    for (i = 0;i < nb_forbiden_names  ; i++) {
       if (strcmp(component, forbidden_names[i]) == 0) {
           return 0;
       } /* endif */
    } /* endfor */

    if (strpbrk(component, forbidden_chars) > 0) {
        return 0;                   // Forbidden characters present
    }

    j = 0;
    pos = 0;
    for (i = 0; i < len; i++) {
        if (component[i] == '.') {
            j++;
        } else{
           if (j == 0) {
               pos++;
           } /* endif */
        }
    }

    if (j > 1) {                    // More than one '.'
        return 0;
    }

    if (j == 0) {                   // No '.'
        if (len > 8) {
            return 0;
        } else {
            return 1;
        }
    }

    if (j == 1) {
        if ((len - pos > 4) || (pos == 0)) {            // '.' in front or extension > 3
            return 0;
        } else {
            if (pos > 8) {
                return 0;                               // name > 8
            } else {
               return 1;
            } /* endif */
        }
    }

    return 0;
}