void DateTime::add(const Duration &duration) {
    if (isValid()) {
        DateTime x = addMSecs(duration.milliseconds());
        setDate( x.date() );
        setTime( x.time() );
        //kDebug(planDbg())<<toString();
    }
}