void SelectionHandler::selectAtPoint(WebCore::IntPoint& location)
{
    // selectAtPoint API currently only supports WordGranularity but may be extended in the future.
    selectObject(location, WordGranularity);
}