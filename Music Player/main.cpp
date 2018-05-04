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
        cout<<"1)search for singer\n2)search for song name\n3)delete from hash table song\n4)delete from hash for artist\n";
        cin>>choice;
        string temp;
        cin>>temp;
        if(choice==1){
            obj.display_specific_from_ids(obj.search_artist.search_for_this_string(temp));
        }else if(choice==2){
            obj.display_specific_from_ids(obj.search_song.search_for_this_string(temp));
        }else if(choice==3){ //song
            int uni_id;
            cin>>uni_id;
            obj.search_song.deletion_process(temp, uni_id);
            obj.display_specific_from_ids(obj.search_song.search_for_this_string(temp));
        }else{
            int uni_id;
            cin>>uni_id;
            obj.search_artist.deletion_process(temp, uni_id);
            obj.display_specific_from_ids(obj.search_artist.search_for_this_string(temp));
        }
    }
    return 0;
}
