//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#include "webview.h"

//---------------------------------------------------------
WebView::WebView(QWidget *parent):
  QWebView(parent)
{

}

//---------------------------------------------------------
QWebView *WebView::createWindow(QWebPage::WebWindowType type)
{
    Q_UNUSED(type);

    QWebView *webView = new WebView();
    QWebPage *newWeb = new QWebPage(webView);
    connect(newWeb, SIGNAL(windowCloseRequested()),
            webView, SLOT(close()));
    webView->setAttribute(Qt::WA_DeleteOnClose, true);
    webView->setPage(newWeb);
    webView->show();

    return webView;
}
