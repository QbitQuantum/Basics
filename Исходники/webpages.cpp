WebPageActivationData WebPages::page(int tabId, int parentId)
{
    if (!m_webPageComponent) {
        qWarning() << "TabModel not initialized!";
        return WebPageActivationData(0, false);
    }

    if (m_activePage && m_activePage->webPage && m_activePage->webPage->tabId() == tabId) {
        m_activePage->webPage->resumeView();
        m_activePage->webPage->setVisible(true);
        return WebPageActivationData(m_activePage->webPage, false);
    }

#ifdef DEBUG_LOGS
    qDebug() << "about to create a new tab or activate old:" << tabId;
#endif

    WebPageEntry *pageEntry = m_activePages.value(tabId, 0);
    bool resurrect = pageEntry && !pageEntry->webPage;
    if (!pageEntry || resurrect) {
        QQmlContext *creationContext = m_webPageComponent->creationContext();
        QQmlContext *context = new QQmlContext(creationContext ? creationContext : QQmlEngine::contextForObject(m_webContainer));
        QObject *object = m_webPageComponent->beginCreate(context);
        if (object) {
            context->setParent(object);
            object->setParent(m_webContainer);
            DeclarativeWebPage *webPage = qobject_cast<DeclarativeWebPage *>(object);
            if (webPage) {
                webPage->setParentItem(m_webContainer);
                webPage->setParentID(parentId);
                webPage->setTabId(tabId);
                webPage->setContainer(m_webContainer);
                if (!pageEntry) {
                    pageEntry = new WebPageEntry(webPage, 0);
                } else {
                    pageEntry->webPage = webPage;
                }

                m_webPageComponent->completeCreate();
#ifdef DEBUG_LOGS
                qDebug() << "New view id:" << webPage->uniqueID() << "parentId:" << webPage->parentId() << "tab id:" << webPage->tabId();
#endif
                m_activePages.insert(tabId, pageEntry);
                ++m_count;
            } else {
                qmlInfo(m_webContainer) << "webPage component must be a WebPage component";
            }
        } else {
            qmlInfo(m_webContainer) << "Creation of the web page failed. Error: " << m_webPageComponent->errorString();
            delete object;
            object = 0;
        }
    }

    updateActivePage(pageEntry, resurrect);
#ifdef DEBUG_LOGS
    dumpPages();
#endif

    return WebPageActivationData(pageEntry->webPage, true);
}