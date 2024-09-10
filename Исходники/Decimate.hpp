    /** Returns a gnnsSatTypeValue object, adding the new data
     *  generated when calling this object.
     *
     * @param gData    Data object holding the data.
     */
 virtual gnssSatTypeValue& Process(gnssSatTypeValue& gData)
    throw(DecimateEpoch)
 { Process(gData.header.epoch, gData.body); return gData; };