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
    song(string name,string artist){
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
        songs(){
            tail=head=NULL;
        }
        void insert(string name,string artist){
            struct song *t=new song(name,artist);
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
        string sentences;
        ifstream file("allsongshere.txt");
        if(file.is_open()){
            getline(file, sentences);
        }else{
            cout<<"No";
        }
        file.close();
        cout<<"S"<<sentences<<endl;
        int len=(int)sentences.length();
        if(len>0){
            int i=1;
            while(i<len){
                string name,artist;
                name=artist="";
                for(int t=i;t<len&&sentences[t]!='*'&&sentences[t]!='|';t++,i++){
                    name=name+sentences[t];
                }
                i++;
                for(int t=i;t<len&&sentences[t]!='*'&&sentences[t]!='|';t++,i++){
                    artist=artist+sentences[t];
                }
                insert(name, artist);
                i++;
            }
        }
    }
    
    void display_all_songs(){
        song *temp=head;
        while(temp){
            cout<<temp->name<<" By "<<temp->artistname<<endl;
            temp=temp->next;
        }
        cout<<endl;
        temp=tail;
        while(temp){
            cout<<temp->name<<" By "<<temp->artistname<<endl;
            temp=temp->prev;
        }        cout<<endl;
    }
    
};

class playlist{
    
};

#endif /* Header_h */
