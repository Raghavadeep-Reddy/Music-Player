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
        struct trie *number[10];
        struct ids *head;
        trie(char t){
            for(int i=0;i<=26;i++)this->next[i]=NULL;
            for(int i=0;i<=10;i++)this->number[i]=NULL;
            this->data=t;
            count=1;
            this->head=NULL;
        }
        
    };
    
    struct trie *headnumber[10]={NULL};//total=10 heads
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
                    if(t[i]>='a'&&t[i]<='z'){
                        agla->next[t[i]-'a']=new trie(t[i]);
                        agla=agla->next[t[i]-'a'];
                    }else{
                        agla->number[t[i]-'0']=new trie(t[i]);
                        agla=agla->number[t[i]-'0'];
                    }
                    agla->head=add_id_for_song(song_id, agla->head);// addition for song id
                }
            }
            
            return rethead;
        }else{
            //match for same string till we get desired pos to insert and simply increase counter by one when we pass one
            trie *last=head;
            int index=0;
            while(index<t.length() && head!=NULL && head->data==t[index]){
                last=head;
                head->head=add_id_for_song(song_id, head->head);// addition for song id
                last->count=last->count+1;
                if(index+1<t.length()){
                    if(t[index+1]>='a'&&t[index+1]<='z')
                        head=head->next[t[index+1]-'a'];
                    else
                        head=head->number[t[index+1]-'0'];
                }//else break;
                index++;
            }
            //head=last;
            string remainingsub=t.substr(index,t.length());
            if(remainingsub.length()>0){
                if(remainingsub[0]>='a'&&remainingsub[0]<='z'){
                if(head)
                    head->next[remainingsub[0]-'a']=perform_insertion(remainingsub, NULL,song_id);
                else
                    last->next[remainingsub[0]-'a']=perform_insertion(remainingsub, NULL,song_id);
                    
                }
                else{
                   if(head)
                       head->number[remainingsub[0]-'0']=perform_insertion(remainingsub, NULL,song_id);
                    else
                        last->number[remainingsub[0]-'0']=perform_insertion(remainingsub, NULL,song_id);
                }
            }
        }
        return head;
    }
    
    
    void insertt(string name,int key){
        if(name.length()>0&&(name[0]>='a'&&name[0]<='z')){
            if(head[name[0]-'a']==NULL){
                head[name[0]-'a']=perform_insertion(name, head[name[0]-'a'],key);
            }else{
                perform_insertion(name, head[name[0]-'a'],key);
            }
        }else if(name.length()>0&&(name[0]>='1'&&name[0]<='9')){
            if(headnumber[name[0]-'0']==NULL){
                headnumber[name[0]-'0']=perform_insertion(name, headnumber[name[0]-'0'],key);
            }else{
                perform_insertion(name, headnumber[name[0]-'0'],key);
            }
        }
    }
    
    void insert(string t,int key){   //to be called for insertion purpose //MAIN INSERT Function
        if(t.length()>0){
            string nonspaced="";
            for(int i=0;i<t.length();i++){
                if((t[i]>='a'&&t[i]<='z')||(t[i]>='1'&&t[i]<='9'))nonspaced=nonspaced+t[i];
            }
            for(int i=0;i<nonspaced.length();i++){
                //cout<<i<<" "<<nonspaced.substr(i,nonspaced.length())<<endl;
                insertt(nonspaced.substr(i,nonspaced.length()), key);
            }
        }
    }
    /*
     insert new file"
     newfile
     ewfile
     wfile
     file
     ile
     le
     e

     */
    string getparsed(string t){
        string ret="";
        for(int i=0;i<t.length();i++){
            if((t[i]>='a'&&t[i]<='z')||(t[i]>='0'&&t[i]<='9'))ret+=t[i];
        }
        return ret;
    }
    
    struct ids* search_for_this_string(string t){
        if(t.length()>0){
            
            t=getparsed(t);
            
            int index=0;
            // struct ids *rethead=NULL;
            char start=t[0];
            if(start>='a'&&start<='z'&&head[start-'a']!=NULL){
                struct trie *temp=head[start-'a'],*last;
                last=temp;
                while(index<=t.length()&&temp!=NULL && temp->data==t[index] ){
                    last=temp;
                    
                        if(t[index+1]>='a'&&t[index+1]<='z')
                            temp=temp->next[t[index+1]-'a'];
                        else if(t[index+1]>='0'&&t[index+1]<='1')
                            temp=temp->number[t[index+1]-'0'];
                    
                    index++;
                    //temp=temp->next[t[index]-'a'];
                }
                cout<<"Showing results for : \""<<t.substr(0,index)<<"\""<<endl;
                if(temp)return temp->head;
                return last->head;
            }else{
                if(headnumber[start-'0']!=NULL){
                    struct trie *temp=headnumber[start-'0'],*last;
                    last=temp;
                    while(index<t.length()&&temp!=NULL && temp->data==t[index] ){
                        last=temp;
                        
                            if(t[index+1]>='a'&&t[index+1]<='z'){
                                temp=temp->next[t[index+1]-'a'];
                                
                            }
                            else if(t[index+1]>='0'&&t[index+1]<='9'){
                                temp=temp->number[t[index+1]-'0'];
                                //index++;
                            }
                        index++;
                        
                    }
                    cout<<"Showing results for : \""<<t.substr(0,index)<<"\""<<endl;
                    if(temp)return temp->head;
                    return last->head;
                }
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
            for(int i=0;i<10;i++)
                if(head->number[i]!=NULL){
                    display_thishead(head->number[i]);
                    cout<<endl;
                }
        }
    }
    void display(){
        for (int i=0;i<26;i++)display_thishead(head[i]);
        for(int i=0;i<10;i++)display_thishead(headnumber[i]);
    }
    struct ids *delete_this_id_from_list(int unid,struct ids *head){
        if(head){
            if(head->current_id==unid)return head->next;
            else {
                struct ids *last=head;//start from 2nd position
                struct ids *rethead=head;
                head=head->next;
                while(head){
                    if(head->current_id==unid){
                        last->next=head->next;
                        return rethead;
                    }
                    last=head;
                    head=head->next;
                }
                last->next=NULL;
                return rethead;
            }
        }
        return head;
    }
    void delete_this_entry(string t,int uni_id){ //recursion for deletion makes code easy to design
        if(t.length()>0){
            char start=t[0];
            struct trie *headp=NULL;
            if(start>='a'&&start<='z'){
                headp=head[start-'a'];
            }else{
                headp=headnumber[start-'0'];
            }
            headp->count=headp->count-1;
            struct trie *agla=headp,*last=headp;
            for(int i=1;i<t.length()&&agla!=NULL;i++){ // deleting from tries
                agla->count=agla->count-1;
                if(agla->count==0){
                    free(agla);
                    if(t[i-1]>='a'&&t[i-1]<='z'){
                        last->next[t[i-1]-'a']=NULL;
                    }else{
                        last->number[t[i-1]-'0']=NULL;
                    }
                }else{
                    agla->head=delete_this_id_from_list(uni_id, agla->head);
                }
                last=agla;
                if(last){
                    if(t[i]>='a'&&t[i]<='z')
                        agla=agla->next[t[i]-'a'];
                    else
                        agla=agla->number[t[i]-'0'];
                }
            }
            if(headp->count==0){
                free(headp);
                head[start-'a']=NULL; //if start is from a to z
            }else{
                headp->head=delete_this_id_from_list(uni_id, headp->head);
            }
        }
    }

    
};


#endif /* searching_h */
