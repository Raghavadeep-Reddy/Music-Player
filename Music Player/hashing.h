//
//  hashing.h
//  Music Player
//
//  Created by Navroop Singh Bajwa on 02/05/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef hashing_h
#define hashing_h
#include<iostream>
#include<math.h>
#include <stdlib.h>
using namespace std;
#include "songs.h"
struct song {
    int songid;
    string name;
    int counter;
    string artistname;
    bool love;
    struct song *prev,*next;
    song(string name,string artist,int idd){
        this->songid=idd;
        this->name=name;
        this->artistname=artist;
        this->prev=NULL;
        this->next=NULL;
    }
    
};
class hash_table{
private :
    int size_for_hash=5;
    song  *address[50]={NULL} ; //it can handle 500 * 50 songs = 25000 songs
public:
    void insert(struct song *song_address){
        if((song_address->songid)%size_for_hash==0){
            address[(song_address->songid)/size_for_hash]=song_address;
        }
    }
    struct song * get_address_song(int song_id){
        // if address = 5 it should go for 0 address and traverse 5 times
        // if address = 45 it should go for 50 address and traverse 5 times
        // if address 50 is not availabe the traverse will be of 45 times
        // if address = 2505 the traversal will be just 5
        // if address = 0, 50, 100 the retrival time will be O(1)
        // overall complexity will be approx. O(log n)
        int get_min,get_max;
        get_min=song_id/size_for_hash;
        get_max=song_id/size_for_hash +1;
        if(song_id%size_for_hash==0){
            return address[song_id/size_for_hash];
        }else{ // now go for travesal approach
            struct song *end;
            if(address[get_max]!=NULL && (address[get_max]->songid-song_id)<(song_id - address[get_min]->songid)){//go for travesal from back else start will be exexuted
                song *end=address[get_max];
                while(end!=NULL){
                    if(end->songid==song_id)return end;
                    end=end->prev;
                }
                
            }
                end=address[get_min];//else intialize end to start pointer
                while(end!=NULL){
                    if(end->songid==song_id)return end;
                    end=end->next;
                }
        }
        return NULL;
    }
    void show_hash_table(){
        for(int i=0;i<50;i++){
            if(address[i]!=NULL){
                cout<<address[i]->songid<<" ";
            }else break;
        }cout<<endl;
    }
    void delete_this_id(int song_id){
        if(song_id%size_for_hash==0){
            address[song_id/size_for_hash]=NULL;
        }
    }
    void delete_this_postion_from_hash(int uni_id){
        if(uni_id%size_for_hash == 0){
            if(address[uni_id/size_for_hash]!=NULL) //it will point to next pointer
                address[uni_id/size_for_hash]=address[uni_id/size_for_hash]->next;
        }
    }
};

#endif /* hashing_h */
