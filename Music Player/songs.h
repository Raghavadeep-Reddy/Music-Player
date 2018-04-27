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
#include<iostream>
using namespace std;
//MRU
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
/*
 |song name*artist name|
 */



class songs{
    private:
        struct song *head,*tail;
        struct song *songshash[50]={NULL};
        int counterforkey=-1;
   
    public:
     make_search_easy search_song,search_artist;
        songs(){
            tail=head=NULL;
        }
        void insert(string name,string artist){
            struct song *t=new song(name,artist,++counterforkey);
            
            //name artist here is the time to put it into tries;
            search_song.insert(name,counterforkey);
            search_artist.insert(artist, counterforkey);
            if(head==NULL){
                head=t;
                tail=t;
            }else{
                tail->next=t;
                t->prev=tail;
                tail=t;
            }
        }
    void song_read_from_file(){
        //cout<<"Called";
        string sentences="\0";
        ifstream file("allsongshere.dat");
        if(file.is_open()){
            while(getline(file, sentences)){
                int len=(int)sentences.length();
                if(len>0){
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
    
    
    
    void display(int songid){
        song *temp=head;
        while(temp){
            if(temp->songid==songid)
            { cout<<"\'"<<temp->name<<"\'"<<" \t\tBy \'"<<temp->artistname<<"\'"<<endl;return;}
            temp=temp->next;
        }
        cout<<endl;
    }
    
    void display_specific_from_ids(struct ids *head){
        while(head){
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
