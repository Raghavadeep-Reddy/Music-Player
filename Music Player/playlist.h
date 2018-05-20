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
#include"hashing.h"
#include <iostream>
// priority is to add song to playlist and update song pointer that it contains the playlist associated with it

using namespace std;
struct song_in_playlist { // this is just a list with id's in incrementing order
    struct song *song_data;
    int unique_song_id; //to be used for hashing and for shuffle fucntion in playlist function
    struct song_in_playlist *next,*prev;
    song_in_playlist(struct song *head,int unid){
        this->song_data=head;
        this->next=this->prev=NULL;
        this->unique_song_id=unid;
    }
};
class songs_playlist {
private:
    struct song_in_playlist *head,*tail;
    string name;
    int count=-1;
public :
    int playlist_id;
    make_search_easy search_song,search_artist;
    songs_playlist(string name,int playlist_id){ //playlist id and name
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
        this->name=newname;
    }
    int get_size(){
        return count;
    }
    void insert_playlist_id_into_song(struct song *head,int plid){ // this will add playlist no to song
        struct ids *t=new ids(plid);
        if(head==NULL){
            head->head_for_playlist= t;
        }else{
            t->next=head->head_for_playlist; // insertion at front
            head->head_for_playlist=t;
        }
    }
    void display_whole_playlist(){
        struct song_in_playlist *temp=head;
        while(temp!=NULL){
            cout<<temp->song_data->name<<" "<<temp->song_data->songid<<endl;
            temp=temp->next;
        }
        cout<<endl;
    }
    void add_this_song(struct song *song_data){ // main function to add song to playlist
        struct song_in_playlist *t=new song_in_playlist(song_data,++count);
        if(head==NULL){
            head=t;
            tail=t;
        }else{ //doubly linked list used in playlist
            //insertion at the end
            tail->next=t;
            t->prev=tail;
            tail=t;
        }
        search_song.insert(song_data->name, count);//update trie associated with it and here uniid will represent its no associated with playlist
        search_artist.insert(song_data->artistname,count);
        //now tell that song it had been added into this->id playlist so to exclude when song is deleted from lib
        if(song_data->head_for_playlist==NULL){
            insert_playlist_id_into_song(song_data,playlist_id);
        }
        // add this song to tries for that current playlist
    }
    void delete_this_song_from_playlist(int song_id){
        //delete from trie and also delete from playlist itself
    }
};
struct playlist{
    struct songs_playlist *head;//here songs will be inserted
    struct playlist *next,*prev;
    int uni_id;
    playlist(struct songs_playlist *head,int uni_id){
        this->head=head;
        this->uni_id=uni_id;
        this->next=NULL;
        this->prev=NULL;
    }
};
class playlist_handler {
private:
    // here object for each playlist will be stored in double linked list and assigned unique key
    // hashing will be implemented on the same later on
    // any change in playlist will take place from here
    int count=-1;
    struct playlist *head=NULL,*tail=NULL;
public:
    // delete playlist
    // delete song from playlist
    make_search_easy search_playlist_name;
    bool create_new_playlist(string name){
        // name to be checked with tries of playlist such that ids not coincide with each other
        // if u want to create new playlist with zero song initialized
        songs_playlist *obj=new songs_playlist(name,++count);//string name,int playlist_id
        struct playlist *t=new playlist(obj,count); // here object will be address will be saved
        if(head==NULL){
            head=t;
            tail=t;
        }else{
            tail->next=t;
            t->prev=tail;
            tail=t; //insertion at back
        }
        search_playlist_name.insert(name, count);
        // here trie insertion will also take place
        return true;
    }
    struct songs_playlist *get_object_for_required_playlist(int playlist_id){//this will provide address using hashing later on
        struct playlist *temp=head;
        while(temp!=NULL){
            if(temp->uni_id==playlist_id){
                return temp->head;
            }
            temp=temp->next;
        }
        return NULL; // if playlist not availabe
    }
    void change_name_for_playlist(string newnname,int playlist_id){
        songs_playlist *temp=get_object_for_required_playlist(playlist_id); //this will fetch obj from linked list
        if(temp!=NULL){
            songs_playlist obj=*temp;
            string oldname=obj.get_name();
            obj.change_name(newnname);
            search_playlist_name.deletion_process(oldname, obj.playlist_id);
            search_playlist_name.insert(newnname, obj.playlist_id);
        }
    }
    void delete_this_playlise(int playid){
        // this will be very complex
        // this will traverse every song tell that song it is not included in that particular playlist no more
    }
    void insert_this_song_into_this_playlist(struct song *pointer_for_song,int playlist_id){
        // get address from playlist and then add to that playlist
        struct songs_playlist *temp;
        temp=get_object_for_required_playlist(playlist_id);
        if(temp!=NULL){
            songs_playlist obj=*temp;
            obj.add_this_song(pointer_for_song);
            cout<<"Inserted successfully into playlist\n";
        }
    }
    void display_this_playlist(int n){
        songs_playlist *temp=get_object_for_required_playlist(n);
        if(temp!=NULL){
            songs_playlist obj=*temp;
            cout<<"Displaying playlist no : "<<n<<" Playlist name : "<<obj.get_name()<<" Playlsit size : "<<obj.get_size();
            obj.display_whole_playlist() ; //this will call that particular playlist object and then that object will display automatically
        }
    }
    struct ids *get_search_results_for_playlist(string search_this){
        return search_playlist_name.search_for_this_string(search_this);
    }
    void display_all_playlist(){
        for(int i=0;i<=count;i++)
            display_this_playlist(i);
    }
    int display_specific_from_ids(struct ids *head,int temp){
        while(head!=NULL){
            temp++;
            cout<<temp<<") ";
            display_this_playlist(head->current_id);
            head=head->next;
        }
        return temp;
    }
};

#endif /* playlist_h */
