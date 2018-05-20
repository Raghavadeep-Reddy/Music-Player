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
#include "shuffle.h"
#include"playlist.h"
#include"hashing.h"
#include<iostream>


//MRU


/*
 |song name*artist name|
 */



class songs{
    private:
    struct song *head,*tail;
    
        //struct song *songshash[50]={NULL}; // 50 * 50 max no of songs
    int counterforkey;
    int actual_songs;
    public:
    playlist_handler all_playlist_here;
    shuffle_songs shuffle_song;
    make_search_easy search_song,search_artist;
    hash_table address_hashing;
        songs(){
            counterforkey=-1;
            tail=head=NULL;
            actual_songs=0;
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
        /*
         This code will shift last song to deleted postion so as to reduce any other complexity
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
        }*/
        //next code will actually delete song and the postion will be left vacant for that id
        //this will also edit the main file and delete required song from there
        // output ot file to be made later on
        if(song_detail!=NULL){
            struct song *back=song_detail->prev;
            struct song *next_one=song_detail->next;
            if(back!=NULL){
                back->next=next_one;
                if(next_one!=NULL){
                    next_one->prev=back;
                }
            }
            if(song_detail==head){
                head=next_one;
            }
            if(song_detail==tail){
                tail=back;
            }
            actual_songs--;
            shuffle_song.mark_this_del(song_detail->songid);
            address_hashing.delete_this_postion_from_hash(song_detail->songid);
            search_song.deletion_process( song_detail->name, song_detail->songid);
            search_artist.deletion_process( song_detail->artistname, song_detail->songid);
            //now delete this song from respective playlist referenced with there playlist id
            
            //TO DO  so this will call playlist handler one by one and delete respective song
            
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
        //shuffle_songs obj(counterforkey);
        //shuffle formed after all songs are assigned respective ids
        shuffle_song.setnow(counterforkey);
    }
    
    struct song *song_address(int songid){ // to be optimized later on
        return address_hashing.get_address_song(songid);
    }
    struct song *get_head(){
        return head;
    }
    struct song *get_tail(){
        return tail;
    }
    int no_of_songs_present(){
        return counterforkey;
    }
    void display(int songid){
        song *temp=address_hashing.get_address_song(songid);
        cout<<"\'"<<temp->name<<"\'"<<" \t\tBy \'"<<temp->artistname<<"\'"<<endl;
        //cout<<endl;
    }
    
    int display_specific_from_ids(struct ids *head,int start){
        while(head!=NULL){
            start++;
            cout<<start<<") ";
            display(head->current_id);
            head=head->next;
        }
        return start;
    }
    
    void display_all_songs(){
        song *temp=head;
        while(temp){
            cout<<"\'"<<temp->name<<"\'"<<" \t\tBy \'"<<temp->artistname<<"\' "<<temp->songid<<endl;
            temp=temp->next;
        }
        cout<<endl;
    }
    void play_with_playlist(){
        // all_playlist_here object take control from here
        string name;cout<<"Enter name of playlist u want to create : ";
        cin>>name;
        all_playlist_here.create_new_playlist(name);
        all_playlist_here.display_all_playlist();
    }
};

class Playing:public songs{
private:
    int shuffle_status=0,repeat_all=0,repeat_one=0;
    struct ids *now_playing_sequence=NULL;// this will be used to store currently playing songs or played songs
public:
    
    void insert(int song_no_currently_playing){
        struct ids *temp=new ids(song_no_currently_playing);
        if(now_playing_sequence==NULL){
            now_playing_sequence=temp;
        }else{
            temp->next=now_playing_sequence;
            now_playing_sequence->prev=temp;
            now_playing_sequence=temp;
        }
    }
    void first_song_was_so_del_form_list(){
        now_playing_sequence=now_playing_sequence->next;
        if(now_playing_sequence!=NULL)now_playing_sequence->prev=NULL;
    }
    void Play_from_this_list(songs all_songs_here){
        cout<<"Reached\n";
        struct song *now_head=all_songs_here.get_head();
        struct song *now_tail=all_songs_here.get_tail();
        struct song *now_pointing_to=now_head;
        shuffle_songs obj;
        obj.setnow(all_songs_here.no_of_songs_present());
        if(now_head==NULL){
            cout<<"No songs in Library\n";
            return ;
        }
         //since shuffle can be turned on once and needs to be on next time also
        while(true){
            if(now_pointing_to==NULL){cout<<"Well Played\n";return ;}
            cout<<"Now Playing -> "<<now_pointing_to->name<<" "<<now_pointing_to->artistname<<endl;
            int inp;
            cout<<"1) Next\n2) Prev\n3) Shuffle\n4) Add this song to Playlist\n5) Delete this song\n6)Repeat ALL\n7)Repeat One\n8)Stop\n";//more opt to come soon
            cin>>inp;
            switch (inp) {
                    
                case 1:
                    //next
                    if(repeat_one==1){
                        //no action required
                    }else{
                        if(shuffle_status==1){
                            int shuffle_song_id_=obj.next_song(repeat_all);
                            if(shuffle_song_id_!=-1)now_pointing_to=all_songs_here.song_address(obj.next_song(shuffle_song_id_));//get next from shuffle
                            else {
                                if(repeat_all==1){
                                    obj.reset_shuffle();
                                    shuffle_song_id_=obj.next_song(repeat_all);
                                    now_pointing_to=all_songs_here.song_address(obj.next_song(shuffle_song_id_));
                                }else{
                                    now_pointing_to=NULL;
                                }
                            }
                        }else{
                            //simple next will be performed
                            now_pointing_to=now_pointing_to->next;
                            if(now_pointing_to==NULL){
                                if(repeat_all==1){
                                    now_pointing_to=now_head;// again start from start
                                }else{
                                    cout<<"All songs had been played THANK YOU\n";
                                    return ;
                                }
                            }
                        }
                    }
                    
                    break;
                case 2:
                    //prev
                    if(now_playing_sequence==NULL){
                        if(repeat_all==1){
                            now_pointing_to=now_tail; //point to end of songs
                        }
                    }else{
                        now_pointing_to=all_songs_here.song_address(now_playing_sequence->current_id); //get prev from currently played
                        first_song_was_so_del_form_list();
                    }
                    break;
                case 3:
                    //shuffle
                    if(shuffle_status==0){
                        cout<<"Shuffle Now turned ON\n";
                        shuffle_status=1;
                    }else{
                        cout<<"Shuffle Now turned OFF\n";
                        shuffle_status=0;
                    }
                    break;
                case 4:
                    //add this song to playlist
                    cout<<"SOon Comming\n";
                    break;
                case 5:
                    // delete this song from lib
                    cout<<"SOnn Coming\n";
                    break;
                case 6:
                    //repeat all
                    if(repeat_all==1){cout<<"Repeat ALL turned OFF\n";repeat_all=0;}
                    else{cout<<"Repeat ALL turned ON\n";repeat_all=1;}
                    break;
                case 7:
                    //repeat one
                    if(repeat_one==1){cout<<"Repeat ONE turned OFF\n";repeat_one=0;}
                    else{cout<<"Repeat ONE turned ON\n";repeat_one=1;}
                    break;
                case 8:
                    //stop
                    return ;
                default:
                    cout<<"Invalid INPUT\n";
                    break;
            }
        }
    }
};

class Music_Player : public  songs{ //using only library songs // for playlist it will be soon ready
    private :
    string output_functions;
    songs all_songs;
    public :
    Music_Player(){
        output_functions="1)Display all songs\n2)Play\n3)Search\n4)Create new Playlist\n";
        this->all_songs.song_read_from_file();
    }
    
    void ask_for_options(){
        string temp;
        struct ids *head_for_songs=NULL,*head_for_artist=NULL,*head_for_playlist=NULL;
        int songs=0,artist=0,playlist=0;int inp_opt,simple_counter=0;
        Playing obj;
        cout<<output_functions;
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                all_songs.display_all_songs();
                break;
            case 2:
                // here code need's to be written
                obj.Play_from_this_list(all_songs);
                break;
            case 3:
                //songs=songs //final value
                // artist =songs +artist
                //playlist=songs+artist
                cin.ignore();
                getline(cin,temp);
                
                head_for_songs=all_songs.search_song.search_for_this_string(temp);
                if(head_for_songs!=NULL){
                    cout<<"Songs found : \n";
                    songs=all_songs.display_specific_from_ids(head_for_songs,songs);
                    cout<<endl;
                }
                simple_counter=songs;
                head_for_artist=all_songs.search_artist.search_for_this_string(temp);
                if(head_for_artist!=NULL){
                    cout<<"Artist found : \n";
                    artist=all_songs.display_specific_from_ids(head_for_artist,simple_counter);
                    cout<<endl;
                }
                artist=artist-simple_counter;
                simple_counter+=artist;
                head_for_playlist=all_songs.all_playlist_here.get_search_results_for_playlist(temp);
                if(head_for_playlist!=NULL){
                    cout<<"Playlist Found: \n";
                    playlist=all_songs.all_playlist_here.display_specific_from_ids(head_for_playlist,simple_counter);
                    cout<<endl;
                }
                playlist=playlist-simple_counter;
                simple_counter+=playlist;
                //cin>>inp_opt;
                
                //here ask if u want to use any of your search results to play
                
                // delete any song or playlist etc.
                //cout<<"song :"<<songs<<" artist "<<artist<<" playlist"<<playlist<<endl;
                
                break;
            case 4:
                cout<<"Enter playlist name :";
                cin.ignore();
                getline(cin,temp);
                all_songs.all_playlist_here.create_new_playlist(temp);
                break;
            case 5:
                all_songs.all_playlist_here.display_all_playlist();
            case 6:
                // deletion of playlist
            default:
                cout<<"Invalid Input\n";
        }
    }
};

#endif /* Header_h */
