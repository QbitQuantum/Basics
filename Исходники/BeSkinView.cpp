/**
 *	@brief	Reads items array in menu design resource.
 *	@return	trigger character
 */
char BeSkinView::parseMenuItemTrigger(
	const char* sourceLabel,	///< source label string
	BString& outLabel			///< OUTPUT. label string without '&' prefix character.
)
{
	char trigger = 0;
	outLabel = sourceLabel;
	int32 find = 0;
	
	while (true)
	{
		find = outLabel.FindFirst('~', find);
		if (B_ERROR == find)
		{
			break;
		}
		outLabel.Remove(find, 1);
		if (outLabel[find] != '~')
		{
			if (0 == trigger)
			{
				trigger = tolower(outLabel[find]);
			}
		}
		else
		{
			find++;
		}
	}
	
	return trigger;
}