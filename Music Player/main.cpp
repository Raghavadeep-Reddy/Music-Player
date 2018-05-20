//
//  main.cpp
//  Music Player
//
//  Created by Navroop Singh Bajwa on 21/04/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//
#include<iostream>
using namespace std;
#include "songs.h"

int main(int argc, const char * argv[]) {
    Music_Player obj;
    while(true){
        obj.ask_for_options();
    }
    /*
    songs obj;
    obj.song_read_from_file();
    obj.display_all_songs();
    
    //obj.search_song.display();
    //obj.search_song.display_unique_ids(obj.search_song.search_for_this_string("geet"));
    //obj.search_artist.display();
    int t;
    cout<<"Input no of queries : ";
    cin>>t;
    while(t--){
        int choice;
        cout<<"1)search for singer\n2)search for song name\n3)delete from hash table song\n4)delete from hash for artist\n5)for deleting any song from library\n6)Show hash Table\n";
        cin>>choice;
        if(choice==1){
            string temp;
            cin.ignore();
            getline(cin,temp);
            obj.display_specific_from_ids(obj.search_artist.search_for_this_string(temp));
        }else if(choice==2){
            string temp;
            cin.ignore();
            getline(cin,temp);
            obj.display_specific_from_ids(obj.search_song.search_for_this_string(temp));
        }else if(choice==3){ //song
            string temp;
            cin.ignore();
            getline(cin,temp);
            int uni_id;
            cin>>uni_id;
            obj.search_song.deletion_process(temp, uni_id);
            obj.display_specific_from_ids(obj.search_song.search_for_this_string(temp));
        }else if(choice==4){
            string temp;
            cin.ignore();
            getline(cin,temp);
            int uni_id;
            cin>>uni_id;
            obj.search_artist.deletion_process(temp, uni_id);
            obj.display_specific_from_ids(obj.search_artist.search_for_this_string(temp));
        }else if(choice == 5 ){
            int song_no;
            cout<<"Enter song no u want to delete : ";
            cin>>song_no;
            obj.delete_this_pointer(obj.song_address(song_no));
            obj.display_all_songs();
        }else if(choice==6){
            obj.address_hashing.show_hash_table();
        }else{
            obj.play_with_playlist();//this will shift the program to playlist object
        }
    }*/
    return 0;
}
