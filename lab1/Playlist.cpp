#include <iostream>

#include "Playlist.h"

using namespace std;

Playlist::Playlist() {
    head = nullptr;
    tail = nullptr;
    totalTime = 0;
    songCount = 0;
}

PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string id, string song, string artist, int length) {
    uniqueID = id;
    songName = song;
    artistName = artist;
    songLength = length;
}

void PlaylistNode::InsertAfter(PlaylistNode *node) {
    PlaylistNode *tempNext = nullptr;
    tempNext = this->nextNodePtr; //the bn's next node now stored
    
    //node is now the nti
    node->SetNext(tempNext);//new node's next node is now the bn's original next
    SetNext(node);//store the new node into bn's next node
}

void PlaylistNode::SetNext(PlaylistNode *node) {
    this->nextNodePtr = node;
}

string PlaylistNode::GetID() const{
    return uniqueID;
}

string PlaylistNode::GetSongName() const {
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const{
    return this->nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    cout<<"Unique ID: "<<uniqueID<<endl;
    cout<<"Song Name: "<<songName<<endl;
    cout<<"Artist Name: "<<artistName<<endl;
    cout<<"Song Length (in seconds): "<<songLength<<endl;
    cout<<endl;
}


