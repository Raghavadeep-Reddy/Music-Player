//
//  main.cpp
//  Music Player
//
//  Created by Navroop Singh Bajwa on 21/04/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#include "Header.h"
int main(int argc, const char * argv[]) {
    songs obj;
    obj.song_read_from_file();
    obj.display_all_songs();
    
    
    
    //obj.search_song.display_unique_ids(obj.search_song.search_for_this_string("geet"));
    //obj.search_artist.display();
    int t;
    cout<<"Input no of queries : ";
    cin>>t;
    while(t--){
        int choice;
        cout<<"1)search for singer\n2)search for song name\n";
        cin>>choice;
        string temp;
        cin>>temp;
        if(choice==1){
            //obj.display(1);
            obj.display_specific_from_ids(obj.search_artist.search_for_this_string(temp));
        }else{
            obj.display_specific_from_ids(obj.search_song.search_for_this_string(temp));
        }
    }
    return 0;
}
