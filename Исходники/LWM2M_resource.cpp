/*
examine one query option to see if the tag matches one of the observe attributes
if so, set the corresponding attribute pmin, pmax, lt, gt, step and flag pending update
*/
void set_notification_attribute(char* option)
{
    char* attribute = strtok(option, "="); // first token
    char* value = strtok(NULL, "="); // next token
    
    pc.printf("Setting: %s = %s\r\n", attribute, value);

    if (strcmp(attribute, "pmin") == 0){
        sscanf(value, "%f", &LWM2M_pmin);
        attribute_update = true;
        return;
    }
    else if(strcmp(attribute, "pmax") == 0){
        sscanf(value, "%f", &LWM2M_pmax);
        attribute_update = true;
        return;
    }
    else if(strcmp(attribute, "gt") == 0){
        sscanf(value, "%f", &LWM2M_gt);
        attribute_update = true;
        return;
    }
    else if(strcmp(attribute, "lt") == 0){
        sscanf(value, "%f", &LWM2M_lt);
        attribute_update = true;
        return;
    }    
    else if(strcmp(attribute, "st") == 0){
        sscanf(value, "%f", &LWM2M_step);
        attribute_update = true;
        return;
    }
    else if(strcmp(attribute, "cancel") == 0){
        LWM2M_stop_notification();
        attribute_update = true;
        return;
    }
}