//
//  shuffle.h
//  Music Player
//
//  Created by Navroop Singh Bajwa on 01/05/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef shuffle_h
#define shuffle_h
#include<iostream.h>
#include <ctime>
using namespace std;

class shuffle_songs{
private:
    int *pointer;
    int size=-1;
    int counter=-1;
public:
    shuffle_songs(int number_of_songs){
        pointer=new int[number_of_songs];
        for(int i=0;i<number_of_songs;i++){
            pointer[i]=0;
        }
        srand(time(0));
        size=number_of_songs;
        counter=0;
    }
    void display(){
        for(int i=0;i<size;i++){
            cout<<pointer[i]<<" ";
        }cout<<endl;
    }
    
    int next_song(){
        while(true){
            int rand_value=random()%size;
            if(counter<size){
                if( rand_value<size &&rand_value>=0 && pointer[rand_value]==0  ){
                    pointer[rand_value]=1;
                    counter++;
                    return rand_value;
                }
            }else{
                for(int i=0;i<size;i++){
                    pointer[i]=0;
                }
                counter=0;
            }
            
        }
    }
    void reducesize(){
        counter--;
    }
};

#endif /* shuffle_h */
