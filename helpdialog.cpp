#include "helpdialog.h"
#include "ui_helpdialog.h"
#include "mainwindow.h"

#include <QLibraryInfo>

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Help - " + APP_NAME);

    ui->contentAbout->setHtml(this->getAboutContent());
    ui->contentSyntax->setHtml(this->getSyntaxContent());
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

QString HelpDialog::getAboutContent()
{
    QString content = "<p><font size=\"5\">" + APP_NAME + "</font></p>";
    content.append("<p>v. " + APP_VERSION + " (use Qt " + QLibraryInfo::version().toString() + ")</p>");
    content.append("<p>Author: Paweł Balicki &lt;pawel@kilab.pl&gt;</p>");
    content.append("<p>Homepage: <a href=\"" + APP_HOMEPAGE_URL + "\">" + APP_HOMEPAGE_URL + "</a></p>");
    content.append("<hr />");

    content.append("<p>MIT License</p>");
    content.append("<p>Copyright (c) Paweł Balicki</p>");

    content.append(R"(<p>Permission is hereby granted, free of charge, to any person obtaining a copy
                           of this software and associated documentation files (the "Software"), to deal
                           in the Software without restriction, including without limitation the rights
                           to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                           copies of the Software, and to permit persons to whom the Software is
                           furnished to do so, subject to the following conditions:</p>)");

    content.append(R"(<p>The above copyright notice and this permission notice shall be included in all
                           copies or substantial portions of the Software.</p>)");

    content.append(R"(<p>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
                           IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
                           FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
                           AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
                           LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
                           OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
                           SOFTWARE.</p>)");

    return content;
}

QString HelpDialog::getSyntaxContent()
{
    QString content = "<style>pre { background: #fcfcfc; border: 2px solid #f6f6f6; padding: 8px; } </style>";

    content.append("<h3>Emphasis</h3>");
    content.append("<pre>");
    content.append("This text *<i>will be italic</i>*\n");
    content.append("This will _<i>also be italic</i>_\n");
    content.append("This text **<b>will be bold</b>**\n");
    content.append("This will __<b>also be bold</b>__\n");
    content.append("</pre>");

    content.append("<h3>Headers</h3>");
    content.append("<pre>");
    content.append("# This is an &lt;h1&gt; tag\n");
    content.append("## This is an &lt;h2&gt; tag\n");
    content.append("##### This is an &lt;h5&gt; tag\n");
    content.append("</pre>");

    content.append("More examples will be added in future..");

    return content;
}
