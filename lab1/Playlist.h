using namespace std;

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

class PlaylistNode {
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode *nextNodePtr;

    public:
        PlaylistNode();
        PlaylistNode(string id, string song, string artist, int length); 
        void InsertAfter(PlaylistNode *node);
        void SetNext(PlaylistNode *node);
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode *GetNext() const;
        void PrintPlaylistNode() const;

};

class Playlist {
    public: 
        int totalTime; 
        int songCount;
        PlaylistNode *head;
        PlaylistNode *tail;
        Playlist();
};

#endif