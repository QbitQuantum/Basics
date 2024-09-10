AwtDesktopProperties::AwtDesktopProperties(jobject self) {
    this->self = GetEnv()->NewGlobalRef(self);
    GetEnv()->SetLongField( self, AwtDesktopProperties::pDataID,
                            ptr_to_jlong(this) );
}