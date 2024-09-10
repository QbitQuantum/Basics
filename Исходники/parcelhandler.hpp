 /// The function \a get_parcel returns the next available parcel
 ///
 /// \param p        [out] The parcel instance to be filled with the
 ///                 received parcel. If the functioned returns \a true
 ///                 this will be the next received parcel.
 /// \param parcel_id  [in] The id of the parcel to fetch
 ///
 /// \returns        Returns \a true if the parcel with the given id
 ///                 has been retrieved successfully. The reference
 ///                 given by parameter \a p will be initialized with
 ///                 the received parcel data.
 ///                 Return \a false if no parcel is available in the
 ///                 parcelhandler, the reference \a p is not touched.
 ///
 /// The returned parcel will be no longer available from the
 /// parcelhandler as it is removed from the internal queue of received
 /// parcels.
 bool get_parcel(parcel& p, naming::gid_type const& parcel_id)
 {
     rethrow_exception();
     return parcels_->get_parcel(p, parcel_id);
 }