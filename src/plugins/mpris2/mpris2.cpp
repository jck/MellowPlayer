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

#include <QWidget>
#include <mellowplayer.h>
#include "mpris2.h"
#include "mpris2root.h"
#include "mpris2player.h"

#define SERVICE_NAME    "org.mpris.MediaPlayer2.mellowplayer"
#define OBJECT_NAME     "/org/mpris/MediaPlayer2"

//---------------------------------------------------------
Mpris2Plugin::Mpris2Plugin(QObject *parent):
    QObject(parent),
    m_root(NULL),
    m_player(NULL)
{
}

//---------------------------------------------------------
void Mpris2Plugin::setup()
{
    if(!QDBusConnection::sessionBus().registerService(SERVICE_NAME))
    {
        qWarning() << "Failed to register service on the session bus: "
                   << SERVICE_NAME;
        return;
    }
    m_root = new Mpris2Root(this);
    m_player = new Mpris2Player(this);
    if(!QDBusConnection::sessionBus().registerObject(OBJECT_NAME, this))
    {
        qWarning() << "Failed to register object on the session bus: "
                   << OBJECT_NAME;
        return;
    }
    qDebug() << "MPRIS2 service started!";
}

//---------------------------------------------------------
void Mpris2Plugin::teardown()
{
    QDBusConnection::sessionBus().unregisterObject(OBJECT_NAME);
    QDBusConnection::sessionBus().unregisterObject(SERVICE_NAME);
}

//---------------------------------------------------------
const PluginMetaData &Mpris2Plugin::metaData() const
{
    static PluginMetaData meta;
    meta.name = "MPRIS2";
    meta.author = "Colin Duquesnoy";
    meta.author_website = "https://github.com/ColinDuquesnoy";
    meta.version = "1.1";
    meta.description =tr("Exposes an MPRIS2 interface to DBUS.");
    return meta;
}
