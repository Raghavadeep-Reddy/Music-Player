//
//  searching.h
//  Music Player
//
//  Created by Navroop Singh Bajwa on 24/04/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef searching_h
#define searching_h
#include<iostream>
using namespace std;
struct ids{
    int current_id;
    struct ids *next;
    ids(int idd){
        this->current_id=idd;
        this->next=NULL;
    }
};




class make_search_easy{
    private :
    
    
    
    struct trie{
        //int idforsong; //to be used for song searching instead use head for ids as ids can be multiple
        int count;
        char data;
        struct trie *next[26];
        struct ids *head;
        trie(char t){
            for(int i=0;i<=26;i++)next[i]=NULL;
            this->data=t;
            count=1;
            this->head=NULL;
        }
        
    };
    
    
    struct trie *head[26]={NULL};//total 26 heads
    public :
    
    struct ids *add_id_for_song(int no,struct ids *head){
        if(head==NULL){
            return new ids (no);
        }else{
            struct ids *rethead=head;
            int flag=0;
            struct ids* last=head;
            while(head){
                last=head;
                if(head->current_id==no){
                    flag=1;
                    break;
                }
                head=head->next;
            }
            if(flag==0){
                last->next=add_id_for_song(no, NULL);
            }
            return rethead;
        }
    }
    
    trie *perform_insertion(string t,trie *head,int song_id){ //perform from start to advance
        if(head==NULL){
            struct trie *rethead=NULL,*agla=head;
            for(int i=0;i<t.length();i++){
                if(rethead==NULL){
                    rethead=new trie (t[i]);
                    agla=rethead;
                    agla->head=add_id_for_song(song_id, agla->head);// addition for song id
                }else{
                    agla->next[t[i]-'a']=new trie(t[i]);
                    agla=agla->next[t[i]-'a'];
                    agla->head=add_id_for_song(song_id, agla->head);// addition for song id
                }
            }
            return rethead;
        }else{
            //match for same string till we get desired pos to insert and simply increase counter by one when we pass one
            trie *last=head;
            int index=0;
            while(index<t.length() && head && head->data==t[index++]){
                last=head;
                head->head=add_id_for_song(song_id, head->head);// addition for song id
                last->count=last->count+1;
                head=head->next[t[index]-'a'];
            }
            //head=last;
            string remainingsub=t.substr(index,t.length()-1);
            if(remainingsub.length()>0){
                if(head)head->next[remainingsub[0]-'a']=perform_insertion(remainingsub, NULL,song_id);
                else last->next[remainingsub[0]-'a']=perform_insertion(remainingsub, NULL,song_id);
            }
        }
        return head;
    }
    
    
    void insertt(string name,int key){
        if(name.length()>0){
            if(head[name[0]-'a']==NULL){
                head[name[0]-'a']=perform_insertion(name, head[name[0]-'a'],key);
            }else{
                perform_insertion(name, head[name[0]-'a'],key);
            }
        }
    }
    
    void insert(string t,int key){
        if(t.length()>0){
            for(int i=0;i<t.length();i++){
                string tem="";
                for(int j=i;j<t.length()&&t[i]>='a'&&t[i]<='z';j++,i++){
                    tem+=t[j];
                }
                insertt(tem,key);
            }
        }
    }
    
    struct ids* search_for_this_string(string t){
        if(t.length()>0){
            int index=0;
            // struct ids *rethead=NULL;
            char start=t[0];
            if(head[start-'a']!=NULL){
                struct trie *temp=head[start-'a'],*last;
                last=temp;
                while(index<t.length()&&temp && temp->data==t[index++] ){
                    last=temp;
                    temp=temp->next[t[index]-'a'];
                }
                return last->head;
            }
        }
        return NULL;
    }
    void display_unique_ids(struct ids *head){
        if(head){
            while(head){
                cout<<head->current_id<<" ";
                head=head->next;
            }cout<<endl;
        }else cout<<"Empty";
        
    }
    
    
    void display_thishead(trie *head){
        if(head!=NULL){
            cout<<head->data<<" "<<head->count<<" | ";
            display_unique_ids(head->head);
            for(int i=0;i<26;i++)
                if(head->next[i]!=NULL){
                    display_thishead(head->next[i]);
                    cout<<endl;
                }
        }
    }
    void display(){
        for (int i=0;i<26;i++)display_thishead(head[i]);
    }
    
};

#endif /* searching_h */
