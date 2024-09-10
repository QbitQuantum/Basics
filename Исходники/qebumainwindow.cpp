void QEbuMainWindow::actionWizard()
{
    QWizard *wizard = new QWizard(this);
    wizard->setWindowTitle(QObject::tr("Getting started"));
    wizard->setWizardStyle(QWizard::ModernStyle);
    wizard->adjustSize();

    // INTRO
    QWizardPage *intro = new QWizardPage;
    {
        intro->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));
        intro->setTitle(QObject::tr("Introduction"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *label = new QLabel(QObject::tr("This brief tutorial will give an overview "
                              "of the main components of the editor and their "
                              "meaning. A couple of aspects of the GUI are pointed out "
                              "in every page and small insight is given about the most "
                              "relevant elements."));
        label->setWordWrap(true);
        layout->addWidget(label);
        intro->setLayout(layout);
    }


    // FIRST PAGE - Basic Layout Description I
    // Breadcrumb
    // Grouping attributes/elements

    QWizardPage *page1 = new QWizardPage;
    {
        page1->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page1->setTitle(QObject::tr("Basic Layout I"));
        page1->setSubTitle(QObject::tr("Breadcrumb and grouping"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page0.png"));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("(1) A simple to read breadcrumb at the top of each page will help you remember at which level of the tree you are");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("(2) All the fields within a form are grouped together, or at least sorted in a meaningful way. For any given types all the attributes are stacked at the top of the page, whereas inner elements occupy lower positions.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page1->setLayout(layout);
    }


    // SECOND PAGE - Basic Layout Description II
    // [0..1]
    // TAB

    QWizardPage *page2 = new QWizardPage;
    {
        page2->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page2->setTitle(QObject::tr("Basic Layout II"));
        page2->setSubTitle(QObject::tr("Simple elements and Tabs"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page1.png"));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("(1) Inner elements with cardinality of [0..1] are hadlled with a couple of buttons to add the element, or edit the existing one, and to remove it. An immutable edit box gives a direct feedback of the status of said element.");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("(2) To have a nicer and tidier appearence, in case of very rich panels, the content is divided among several tabs, with the aim to keep together correlated elements.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page2->setLayout(layout);
    }

    // THIRD PAGE - Basic Layout Description III
    // The Amazing ListView
    // Mention to New Form vs Simple Dialog

    QWizardPage *page3 = new QWizardPage;
    {
        page3->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page3->setTitle(QObject::tr("Basic Layout III"));
        page3->setSubTitle(QObject::tr("Listview"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page2.png"));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("In case of inner elements with [0..*] cardinality a custom list manager is provided, to manage the contents.");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("In presence of both single and multiple cardinality elements within the same form, to keep a coherent appearence all the items are managed with the proposed list view, that automatically forbids the insertion of more than one element, if needed.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page3->setLayout(layout);
    }

    // FOURTH PAGE - Dates & Numbers
    // Optional fields
    // Checkboxes
    // Compliance Check

    QWizardPage *page4 = new QWizardPage;
    {
        page4->setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png").scaled(560, 49, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        page4->setTitle(QObject::tr("About data"));
        page4->setSubTitle(QObject::tr("Dates, numbers and validation"));
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *image = new QLabel;
        image->setPixmap(QPixmap(":/images/page3.png").scaledToWidth(500, Qt::SmoothTransformation));
        image->setAlignment(Qt::AlignHCenter);
        QLabel *firstParagraph = new QLabel("(1) Unlike simple text fields, data and numeric related fields come with a checkbox to enable/disable its content from being saved to the XML files in creation. Upon a change of the represented value the checkboxes are automatically ticked off, whilst if unchecked their value is ignored or cleared if previusly modified.");
        firstParagraph->setWordWrap(true);
        QLabel *secondParagraph = new QLabel("(2) Upon clicking Apply a compliance check is run on the form contents, and an error message, preventing the user from continuing, appears in case of mistakes or shortcomings.");
        secondParagraph->setWordWrap(true);
        layout->addWidget(image);
        layout->addWidget(firstParagraph);
        layout->addWidget(secondParagraph);
        page4->setLayout(layout);
    }

    // END OF TUTORIAL

    wizard->addPage(intro);
    wizard->addPage(page1);
    page1->setFixedHeight(420);
    wizard->addPage(page2);
    wizard->addPage(page3);
    wizard->addPage(page4);
    wizard->exec();
}