//
//  Header.h
//  Music Player
//
//  Created by Navroop Singh Bajwa on 21/04/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <fstream>
#include<string>
#include "searching.h"

#include"playlist.h"
#include"hashing.h"
#include<iostream>
using namespace std;
//MRU


/*
 |song name*artist name|
 */



class songs{
    private:
        struct song *head,*tail;
        //struct song *songshash[50]={NULL}; // 50 * 50 max no of songs
        int counterforkey=-1;
    
    public:
     make_search_easy search_song,search_artist;
    hash_table address_hashing;
        songs(){
            tail=head=NULL;
        }
        void insert(string name,string artist){
            struct song *t=new song(name,artist,++counterforkey);
            //cout<<"created";
            //name artist here is the time to put it into tries;
            search_song.insert(name,counterforkey);
            search_artist.insert(artist, counterforkey);
            address_hashing.insert(t);
            if(head==NULL){
                head=t;
                tail=t;
            }else{
                tail->next=t;
                t->prev=tail;
                tail=t;
            }
        }
    void delete_this_pointer(struct song *song_detail){ // it will replace last song with current
        struct song *last=tail;
        if(tail!=song_detail){
            tail=tail->prev;
            tail->next=NULL;
            //delete artist and song name from tries
            search_song.deletion_process( song_detail->name, song_detail->songid);
            search_artist.deletion_process( song_detail->artistname, song_detail->songid);
            song_detail->name=last->name;
            song_detail->artistname=last->artistname;
            //now update this id
            address_hashing.delete_this_id(last->songid);//if last is on hash it should also be removed
            int new_id=song_detail->songid;
            int old_id=last->songid;
            search_song.changing__id_process(song_detail->name,old_id,new_id);
            counterforkey--;
        }
    }
    void song_read_from_file(){
       // cout<<"Called";
        string sentences="\0";
        ifstream file("allsongshere.dat");
        if(file.is_open()){
            while(getline(file, sentences) && sentences.length()>0){
                int len=(int)sentences.length();
                if(len>0){
                	//cout<<sentences<<endl;
                    int i=0;
                    while(i<len&&sentences[i]!='\0'){
                        string name,artist;
                        name=artist="";
                        for(int t=i;t<len&&sentences[t]!='*'&&sentences[t]!='|'&&sentences[i]!='\0';t++,i++){
                            name=name+sentences[t];
                        }
                        i++;
                        for(int t=i;t<len&&sentences[t]!='*'&&sentences[t]!='|'&&sentences[i]!='\0';t++,i++){
                            artist=artist+sentences[t];
                        }
                        insert(name, artist);
                        i++;
                    }
                }
            }
        }else{
            cout<<"No";
        }
        file.close();
        //cout<<"S"<<sentences<<endl;
        
        
    }
    
    struct song *song_address(int songid){ // to be optimized later on
        return address_hashing.get_address_song(songid);
    }
    
    
    void display(int songid){
        song *temp=address_hashing.get_address_song(songid);
        cout<<"\'"<<temp->name<<"\'"<<" \t\tBy \'"<<temp->artistname<<"\'"<<endl;
        cout<<endl;
    }
    
    void display_specific_from_ids(struct ids *head){
        while(head!=NULL){
            display(head->current_id);
            head=head->next;
        }
    }
    
    void display_all_songs(){
        song *temp=head;
        while(temp){
            cout<<"\'"<<temp->name<<"\'"<<" \t\tBy \'"<<temp->artistname<<"\' "<<temp->songid<<endl;
            temp=temp->next;
        }
        cout<<endl;
    }
    
};




#endif /* Header_h */
