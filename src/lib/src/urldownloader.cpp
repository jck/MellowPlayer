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

#include <QtNetwork>
#include "mellowplayer/urldownloader.h"

//---------------------------------------------------------
UrlDownloader::UrlDownloader(QObject *parent):
    QObject(parent),
    m_nam(NULL)
{
}

//---------------------------------------------------------
void UrlDownloader::download(const QString &url, const QString &destination)
{
    m_fileUrl = destination;
    if(url.startsWith(":") || url.startsWith("qrc:"))
    {
        // load from resource
        QFile dst(m_fileUrl);
        QFile src(url);
        if(src.open(QIODevice::ReadOnly) && dst.open(QIODevice::WriteOnly))
        {
            dst.write(src.readAll());
            dst.close();
        }
        emit finished(m_fileUrl);
    }
    else
    {
        m_nam = new QNetworkAccessManager(this);
        connect(m_nam, SIGNAL(finished(QNetworkReply *)),
                this, SLOT(onDownloadFinished(QNetworkReply *)));
        m_nam->get(QNetworkRequest(QUrl(url)));
        qDebug() << "Downloading " << url << " to " << destination;
    }

}

//---------------------------------------------------------
void UrlDownloader::onDownloadFinished(QNetworkReply *reply)
{
    qDebug() << "Download finished: " << m_fileUrl;
    QFile file(m_fileUrl);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(reply->readAll());
        file.close();
    }
    emit finished(m_fileUrl);
}
