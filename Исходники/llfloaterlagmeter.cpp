void LLFloaterLagMeter::updateControls(bool shrink)
{
//	LLFloaterLagMeter * self = (LLFloaterLagMeter*)data;

	LLButton * button = getChild<LLButton>("minimize");
	S32 delta_width = mMaxWidth -mMinWidth;
	LLRect r = getRect();

	if(!shrink)
	{
		setTitle(getString("max_title_msg", mStringArgs) );
		// make left edge appear to expand
		r.translate(-delta_width, 0);
		setRect(r);
		reshape(mMaxWidth, getRect().getHeight());
		
		childSetText("client", getString("client_text_msg", mStringArgs) + ":");
		childSetText("network", getString("network_text_msg",mStringArgs) + ":");
		childSetText("server", getString("server_text_msg", mStringArgs) + ":");

		// usually "<<"
		button->setLabel( getString("smaller_label", mStringArgs) );
	}
	else
	{
		setTitle( getString("min_title_msg", mStringArgs) );
		// make left edge appear to collapse
		r.translate(delta_width, 0);
		setRect(r);
		reshape(mMinWidth, getRect().getHeight());
		
		childSetText("client", getString("client_text_msg", mStringArgs) );
		childSetText("network",getString("network_text_msg",mStringArgs) );
		childSetText("server", getString("server_text_msg", mStringArgs) );

		// usually ">>"
		button->setLabel( getString("bigger_label", mStringArgs) );
	}
	// Don't put keyboard focus on the button
	button->setFocus(FALSE);

//	self->mClientText->setVisible(self->mShrunk);
//	self->mClientCause->setVisible(self->mShrunk);
//	self->childSetVisible("client_help", self->mShrunk);

//	self->mNetworkText->setVisible(self->mShrunk);
//	self->mNetworkCause->setVisible(self->mShrunk);
//	self->childSetVisible("network_help", self->mShrunk);

//	self->mServerText->setVisible(self->mShrunk);
//	self->mServerCause->setVisible(self->mShrunk);
//	self->childSetVisible("server_help", self->mShrunk);

//	self->mShrunk = !self->mShrunk;
}