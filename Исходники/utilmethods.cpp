QTime UtilMethods::addHMToCurrentTime(int hr,int min) {
    int val = (hr*60*60)+(min*60);
    KDateTime now = KDateTime::currentLocalDateTime().addSecs(val);    
    return now.time();
}