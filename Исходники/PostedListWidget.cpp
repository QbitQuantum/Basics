void PostedListWidget::applyRanking()
{
	/* uses current settings to sort posts, then add to layout */
	std::cerr << "PostedListWidget::applyRanking()";
	std::cerr << std::endl;

	shallowClearPosts();

	/* sort */
	switch(mSortMethod)
	{
		default:
		case RsPosted::HotRankType:
			std::cerr << "PostedListWidget::applyRanking() HOT";
			std::cerr << std::endl;
			qSort(mPostItems.begin(), mPostItems.end(), CmpPIHot);
			break;
		case RsPosted::NewRankType:
			std::cerr << "PostedListWidget::applyRanking() NEW";
			std::cerr << std::endl;
			qSort(mPostItems.begin(), mPostItems.end(), CmpPINew);
			break;
		case RsPosted::TopRankType:
			std::cerr << "PostedListWidget::applyRanking() TOP";
			std::cerr << std::endl;
			qSort(mPostItems.begin(), mPostItems.end(), CmpPITop);
			break;
	}
	mLastSortMethod = mSortMethod;

	std::cerr << "PostedListWidget::applyRanking() Sorted mPostList";
	std::cerr << std::endl;

	/* go through list (skipping out-of-date items) to get */
	QLayout *alayout = ui->scrollAreaWidgetContents->layout();
	int counter = 0;
	time_t min_ts = 0;
	foreach (PostedItem *item, mPostItems)
	{
		std::cerr << "PostedListWidget::applyRanking() Item: " << item;
		std::cerr << std::endl;
		
		if (item->getPost().mMeta.mPublishTs < min_ts)
		{
			std::cerr << "\t Skipping OLD";
			std::cerr << std::endl;
			item->hide();
			continue;
		}

		if (counter >= mPostIndex + mPostShow)
		{
			std::cerr << "\t END - Counter too high";
			std::cerr << std::endl;
			item->hide();
		}
		else if (counter >= mPostIndex)
		{
			std::cerr << "\t Adding to Layout";
			std::cerr << std::endl;
			/* add it in! */
			alayout->addWidget(item);
			item->show();
		}
		else
		{
			std::cerr << "\t Skipping to Low";
			std::cerr << std::endl;
			item->hide();
		}
		++counter;
	}