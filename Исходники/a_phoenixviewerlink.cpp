BOOL PhoenixViewerLink::allowed_login()
{
	PhoenixViewerLink* self = getInstance();
	return (self->blocked_versions.find(versionid) == self->blocked_versions.end());
}