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

#include <QtCore>
#include <mellowplayer.h>

class DeezerPlugin:
        public QObject,
        public IStreamingService
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IStreamingService_iid FILE "deezer.json")
    Q_INTERFACES(IStreamingService)

public:
    DeezerPlugin();

    //! Gets the plugin's meta data
    virtual const PluginMetaData& metaData() const;
    //! Flash is required.
    virtual bool flashRequired();
    //! Returns the DeezerPlugin URL
    virtual QUrl url() const;
    //! Plays the current song
    void play();
    //! Pauses the current song
    void pause();
    //! Skips to the next song
    void next();
    //! Skips to the previous song
    void previous();
    //! Seeks to the indicated position
    void seekToPosition(int position);
    //! Gets the current song info
    SongInfo currentSongInfo();
    //! Gets the deezer player's playback status
    PlaybackStatus playbackStatus();
    //! Gets the player volume
    float volume();
    //! Sets the player volume
    void setVolume(float volume);
    //! Whether the client can control the playback position using
    //! seekToPosition.
    bool canSeek();
    //! Whether the client can call the next method on this interface and
    //! expect the current track to change.
    bool canGoNext();
    //! Whether the client can call the previsou method on this interface and
    //! expect the current track to change.
    bool canGoPrevious();
    //! Checks whether the service support adding a song to the user's favorite
    bool canFavorite();
    //! Checks whether the current song is one of the user's favorite.
    bool isFavorite();
    //! Adds the current song to the user's favorites
    void addToFavorite(bool add);
};
