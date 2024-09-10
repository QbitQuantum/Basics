    /** Returns a reference to a gnnsRinex object after converting
     *  from a geocentric reference system to a topocentric reference
     *  system.
     *
     * @param gData    Data object holding the data.
     */
 virtual gnssRinex& Process(gnssRinex& gData)
    throw(ProcessingException)
 { Process(gData.body); return gData; };