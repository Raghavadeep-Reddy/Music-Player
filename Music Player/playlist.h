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
        struct song *song_data;
        int unique_song_id; //to be used for hashing and for shuffle fucntion
        struct playlist *next,*prev;
        song_in_playlist(struct song *head,int unid){
            this->song_data=head;
            this->unique_song_id=unid;
        }
    };
private:
    struct song_in_playlist *head,*tail;
    string name;
    int count=-1;
    int playlist_id;
public:
    songs_playlist(string name,int playlist_id){
        this->name=name;
        this->playlist_id=playlist_id;
        this->head=NULL;
        this->tail=NULL;
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
    void add_this_song(struct song *song_data){
        struct song_in_playlist *temp=new song_in_playlist(song_data,++count);
        if(head==NULL){
            head=temp;
            tail=head;
        }else{
           // tail->next=temp;
            tail=temp;
        }
    }
};

#endif /* playlist_h */
