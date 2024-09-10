void DirectXHook::drawChatInterface()
{
	auto& console = GameConsole::Instance();
	if ((console.getMsSinceLastConsoleOpen() > 10000 && !console.showChat && !console.showConsole) || (GetAsyncKeyState(VK_TAB) & 0x8000 && !console.showChat && !console.showConsole))
	{
		return;
	}

	int x = (int)(0.05 * *horizontalRes);
	int y = (int)(0.65 * *verticalRes);
	int inputTextBoxWidth = (int)(0.5 * *horizontalRes);
	int inputTextBoxHeight = normalSizeFontHeight + (int)(0.769 * normalSizeFontHeight);
	int horizontalSpacing = (int)(0.012 * inputTextBoxWidth);
	int verticalSpacingBetweenEachLine = (int)(0.154 * normalSizeFontHeight);
	int verticalSpacingBetweenLinesAndInputBox = (int)(1.8 * normalSizeFontHeight);
	int verticalSpacingBetweenTopOfInputBoxAndFont = (inputTextBoxHeight - normalSizeFontHeight) / 2;
	size_t maxCharsPerLine = 105;

	if (console.showChat)
	{
		int tempX = x;

		std::string helpText = "Press ` or F1 to open console.";
		drawText(tempX + horizontalSpacing, y + verticalSpacingBetweenTopOfInputBoxAndFont, COLOR_WHITE, helpText.c_str(), normalSizeFont);
	}

	y -= verticalSpacingBetweenLinesAndInputBox;

	if (console.showChat || console.showConsole)
	{
		// Display current input
		drawBox(x, y, inputTextBoxWidth, inputTextBoxHeight, COLOR_WHITE, COLOR_BLACK);
		drawText(x + horizontalSpacing, y + verticalSpacingBetweenTopOfInputBoxAndFont, COLOR_WHITE, console.currentInput.currentInput.c_str(), normalSizeFont);

		// START: Line showing where the user currently is in the input field.
		if (console.getMsSinceLastConsoleBlink() > 300)
		{
			console.consoleBlinking = !console.consoleBlinking;
			console.lastTimeConsoleBlink = GetTickCount();
		}
		if (!console.consoleBlinking)
		{
			std::string currentInput = console.currentInput.currentInput;
			char currentChar;
			int width = 0;
			if (currentInput.length() > 0) {
				currentChar = currentInput[console.currentInput.currentPointerIndex];
				width = getTextWidth(currentInput.substr(0, console.currentInput.currentPointerIndex).c_str(), normalSizeFont) - 3;
			}
			else
			{
				width = -3;
			}
			drawText(x + horizontalSpacing + width, y + verticalSpacingBetweenTopOfInputBoxAndFont, COLOR_WHITE, "|", normalSizeFont);
		}
		// END: Line showing where the user currently is in the input field.
	}

	y -= verticalSpacingBetweenLinesAndInputBox;

	// Draw text from chat or console
	for (int i = console.selectedQueue->startIndexForScrolling; i < console.selectedQueue->numOfLinesToShow + console.selectedQueue->startIndexForScrolling; i++)
	{
		std::string line = console.selectedQueue->queue.at(i);

		if (line.size() > maxCharsPerLine)
		{
			std::vector<std::string> linesWrapped = std::vector < std::string > {};

			for (size_t i = 0; i < line.size(); i += maxCharsPerLine)
			{
				linesWrapped.push_back(line.substr(i, maxCharsPerLine));
			}

			for (int i = linesWrapped.size() - 1; i >= 0; i--)
			{
				drawText(x, y, COLOR_WHITE, linesWrapped.at(i).c_str(), normalSizeFont);
				y -= normalSizeFontHeight + verticalSpacingBetweenEachLine;
			}
		}
		else
		{
			drawText(x, y, COLOR_WHITE, line.c_str(), normalSizeFont);
			y -= normalSizeFontHeight + verticalSpacingBetweenEachLine;
		}
	}
}