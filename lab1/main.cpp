#include <iostream>

#include "Playlist.h"

using namespace std;

void PrintMenu(string plName, Playlist *playlist);
void OutputFullPl(string plName, Playlist *playlist);
void AddSong(Playlist *playlist);
void RemoveSong(Playlist *playlist, string id, int tracker);
void TotalTime(Playlist *playlist);
void ChangePos(Playlist *playlist);
void OutputByArtist(Playlist *playlist);

int main(int argc, char *argv[]) {
    Playlist *playlist = new Playlist();
    //beginning of the prompt
    string playlistName;

    cout<<"Enter playlist's title:"<<endl;
    cout<<endl;
    getline(cin, playlistName);

    PrintMenu(playlistName, playlist);

    return 0;
}

void PrintMenu(string plName, Playlist *playlist) {
    char option = ' ';
    
    while(option!='q') {
        //generate prompt below
        cout<<plName<<" PLAYLIST MENU"<<endl;
        cout<<"a - Add song"<<endl;
        cout<<"d - Remove song"<<endl;
        cout<<"c - Change position of song"<<endl;
        cout<<"s - Output songs by specific artist"<<endl;
        cout<<"t - Output total time of playlist (in seconds)"<<endl;
        cout<<"o - Output full playlist"<<endl;
        cout<<"q - Quit"<<endl;
        cout<<endl;
        cout<<"Choose an option:"<<endl;
        cin>>option;

        if(option=='q') { //quit
            break;
        }
        else if(option=='a') { //add song
            AddSong(playlist);
        }
        else if(option=='d') { //remove song
            //prompt
            string id;
            cout<<"REMOVE SONG"<<endl;
            cout<<"Enter song's unique ID:"<<endl;
            cin>>id;

            RemoveSong(playlist, id, 0);
        }
        else if(option=='c') { //change pos of song 
            ChangePos(playlist);
        }
        else if(option=='s') { //output songs by artist
            OutputByArtist(playlist);
        }
        else if(option=='t') { //output total time
            TotalTime(playlist);
        }
        else if(option=='o') { //output full playlist
            OutputFullPl(plName, playlist);
        }
        else { //invalid input 
            //cout<<"Please try again, invalid input."<<endl;
        }
    }
}

void OutputFullPl(string plName, Playlist *playlist) {
    int songCount = 1;
    PlaylistNode *currNode = playlist->head;

    if(playlist->head == nullptr) { //first check if empty
        cout<<plName<<" - OUTPUT FULL PLAYLIST"<<endl;
        cout<<"Playlist is empty"<<endl;
        cout<<endl;
    }
    else if(playlist->tail == playlist->head) { //only one song in list
        cout<<plName<<" - OUTPUT FULL PLAYLIST"<<endl;
        cout<<songCount<<"."<<endl;
        currNode->PrintPlaylistNode();

        songCount++;

        delete currNode;
        currNode = nullptr;
    }
    else { //at least two songs 
        cout<<plName<<" - OUTPUT FULL PLAYLIST"<<endl;
        for(auto i=currNode;i!=nullptr;i=i->GetNext()) {
            cout<<songCount<<"."<<endl;
            i->PrintPlaylistNode(); 

            songCount++;
        }
    }
}

void AddSong(Playlist *playlist) {
    string id, songName, artistName;
    int length;

    //start of prompt
    cout<<"ADD SONG"<<endl;
    cout<<"Enter song's unique ID:"<<endl;
    cin.ignore();
    getline(cin, id);
    cout<<"Enter song's name:"<<endl;
    getline(cin, songName);
    cout<<"Enter artist's name:"<<endl;
    getline(cin, artistName);
    cout<<"Enter song's length (in seconds):"<<endl;
    cin>>length;
    cout<<endl;

    //add song to playlist
    PlaylistNode *node = new PlaylistNode(id, songName, artistName, length);
    if(playlist->head == nullptr) { //if playlist is empty
        playlist->head = node;
        playlist->tail = node;
        playlist->songCount++;
    }
    else{ //for other situations
        playlist->tail->InsertAfter(node);
        playlist->tail = node;
        playlist->songCount++;
    }
    playlist->totalTime += length;
}

void RemoveSong(Playlist *playlist, string id, int tracker) {
    string songName;
    PlaylistNode *prevNode = nullptr;

    //code
    if(playlist->head == nullptr) {
        cout<<"List is empty."<<endl;
    }
    else if(playlist->tail == playlist->head) { //only one song
        songName = playlist->head->GetSongName();
        delete playlist->head;
        playlist->head = nullptr;
        playlist->tail = nullptr;
        playlist->totalTime = 0;
        playlist->songCount--;
    }
    else if(playlist->head->GetID() == id) { //remove head
        songName = playlist->head->GetSongName();
        int time = playlist->head->GetSongLength();
        PlaylistNode *temp = playlist->head;

        playlist->head = playlist->head->GetNext();
        delete temp;
        temp = nullptr;

        playlist->totalTime -= time;
        playlist->songCount--;
    }
    else {
        for(auto i=playlist->head;i!=nullptr;i=i->GetNext()) {
            if(id == i->GetID()) {
                songName = i->GetSongName();
                if(i==playlist->tail) { //remove tail
                    //cout<<"Removing tail"<<endl;
                    int time = playlist->tail->GetSongLength();
                    PlaylistNode *temp = playlist->tail;

                    prevNode->SetNext(nullptr);
                    delete temp;
                    temp = nullptr;
                    playlist->tail = prevNode;

                    playlist->totalTime -= time;
                    playlist->songCount--;
                }
                else if(i->GetNext() == nullptr) { //remove second to last node
                    PlaylistNode *temp = i;
                    int time = i->GetSongLength();

                    prevNode->SetNext(nullptr);
                    delete temp;
                    temp = nullptr;

                    playlist->totalTime -= time;
                    playlist->songCount--;
                }
                else {
                    PlaylistNode *temp = i;
                    int time = i->GetSongLength();

                    prevNode->SetNext(i->GetNext());
                    delete temp;
                    temp = nullptr;

                    playlist->totalTime -= time;
                    playlist->songCount--;
                }
            }
            else {
                prevNode = i;
            }
        }
    }
    if(tracker==0) { //determines if the function is called by menu or by changepos
        cout<<"\""<<songName<<"\" removed."<<endl;
        cout<<endl;
    }
}

void TotalTime(Playlist *playlist) {
    cout<<"OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)"<<endl;
    cout<<"Total time: "<<playlist->totalTime<<" seconds"<<endl;
    cout<<endl;
}

void ChangePos(Playlist *playlist) {
    int currPos = 0;
    int newPos = 0;

    //prompt
    cout<<"CHANGE POSITION OF SONG"<<endl;
    cout<<"Enter song's current position:"<<endl;
    cin>>currPos;
    cout<<"Enter new position for song:"<<endl;
    cin>>newPos;
    
    int begIndex=1 ;
    PlaylistNode* prevNode = nullptr ;
    PlaylistNode* currNode = playlist->head ;

    if(currPos<1){
        cout << "Invalid current position." << endl ;
        return ;
    }
    while(begIndex<currPos){
        if (currNode != nullptr){
            prevNode = currNode ;
            currNode = currNode->GetNext() ;
            begIndex++ ;
        }
    }
    if(prevNode!=nullptr){
        prevNode->SetNext(currNode->GetNext()) ;
    }
    else{
        playlist->head=currNode->GetNext() ;
    } 
    if(currNode==playlist->tail){
        playlist->tail = prevNode ;
    }
    if(newPos<=1) {
        if (playlist->head==nullptr){
            playlist->tail=currNode ;
        }

        currNode->SetNext(playlist->head) ;
        playlist->head = currNode ;
        cout << '"' << currNode->GetSongName() << '"' << " moved to position 1" << endl ;
        cout<<endl;
    }
    else {
        if(playlist->head == nullptr) {
            playlist->tail->InsertAfter(currNode);
            playlist->tail = currNode;
            playlist->songCount++;
            cout << '"' << currNode->GetSongName() << '"' << " moved to position 1" << endl ;
            cout<<endl;
        }
        else{
            int newIndex = 2;
            PlaylistNode* previousNode = playlist->head;
            PlaylistNode* afterNode = playlist->head->GetNext() ;
            while (newIndex<newPos && afterNode!=nullptr){
                previousNode = afterNode ;
                afterNode = afterNode->GetNext() ;
                newIndex++ ;
            }

            previousNode->InsertAfter(currNode) ;

            if (afterNode==nullptr) {
                playlist->tail = currNode ;
            }
            cout << '"' << currNode->GetSongName() << '"' << " moved to position " << newIndex << endl ;
            cout<<endl;
        }
    }
}

void OutputByArtist(Playlist *playlist) {
    int songItr = 1;
    string name = " ";
    //prompt
    cout<<"OUTPUT SONGS BY SPECIFIC ARTIST"<<endl;
    cout<<"Enter artist's name:"<<endl;
    cout<<endl;
    cin.ignore();
    getline(cin, name);
    for(auto i=playlist->head;i!=nullptr;i=i->GetNext()) {
        if(i->GetArtistName()==name) {
            cout<<songItr<<"."<<endl;
            i->PrintPlaylistNode();
        }
        songItr++;
    }
}