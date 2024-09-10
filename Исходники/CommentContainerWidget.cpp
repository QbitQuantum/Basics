void CommentContainerWidget::onTokenReady(uint32_t token, bool ok)
{
    if(ok)
    {
        clear();
        std::vector<RsGxsComment> comments;
        //_CommentService->getRelatedComments(token, comments);
        _CommentService->getCommentData(token, comments);
        for(std::vector<RsGxsComment>::iterator vit = comments.begin(); vit != comments.end(); vit++)
        {
            RsGxsComment& comment = *vit;
            Wt::WContainerWidget* outerContainer = new Wt::WContainerWidget(this);
            Wt::WBorderLayout *layout = new Wt::WBorderLayout();
            outerContainer->setLayout(layout);
            AvatarWidgetWt* avatar = new AvatarWidgetWt(true);
            avatar->setIdentity(comment.mMeta.mAuthorId);
            layout->addWidget(avatar, Wt::WBorderLayout::West);
            Wt::WLabel* text = new Wt::WLabel(Wt::WString::fromUTF8(comment.mComment));
            layout->addWidget(text, Wt::WBorderLayout::Center);
        }
        // note: the widgets the pointers where pointing to where deleted by clear()
        _TextArea = new Wt::WTextArea(this);
        _TextArea->setEmptyText("your comment");
        //_IdChooser = new GxsIdChooserWt(this);
        _SubmitButton = new Wt::WPushButton("submit", this);
        _SubmitButton->clicked().connect(this, &CommentContainerWidget::onSubmitComment);
    }
    else
    {
        clear();
        new Wt::WLabel("FAIL", this);
    }
}