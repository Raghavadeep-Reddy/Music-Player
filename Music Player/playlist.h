//
//  playlist.h
//  Music Player
//
//  Created by Navroop Singh Bajwa on 02/05/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef playlist_h
#define playlist_h

#include"songs.h"

class songs_playlist {
    public :
    struct song_in_playlist {
        struct songs *song_data;
        int unique_song_id; //to be used for hashing and for shuffle fucntion
        struct playlist *next,*prev;
    };
private:
    string name;
    int count=-1;
    int playlist_id;
public:
    songs_playlist(string name,int playlist_id){
        this->name=name;
        this->playlist_id=playlist_id;
    }
    string get_name(){
        return name;
    }
    void change_playlist_id(int newid){
        playlist_id=newid;
    }
    void change_name(string newname){
        name=newname;
    }
};

#endif /* playlist_h */
