//
//  shuffle.h
//  Music Player
//
//  Created by Navroop Singh Bajwa on 01/05/18.
//  Copyright © 2018 Navroop Singh Bajwa. All rights reserved.
//

#ifndef shuffle_h
#define shuffle_h
#include<iostream>
#include <ctime>
using namespace std;

struct node {
    struct node *left,*right;
    int data;
    node (int d){
        data=d;
        left=NULL;
        right=NULL;
    }
};

// if song is deleted so shuffle will be informed that song is not availble in library now
// bst to be formed as to reduce time complexity of the code
class shuffle_songs{
private:
    private :
    int size;
    int counter=0; // if count exceeds size then reset bst to null
    struct node *head=NULL;
public:
    struct node *newNode(int item)
    {
        
        struct node *temp =  (struct node *)malloc(sizeof(struct node));
        temp->data = item;
        temp->left = temp->right = NULL;
        return temp;
    }
    void setnow(int number_of_songs){
        head=NULL;
        srand(time_t(0));
        size=number_of_songs;
        counter=0;
    }
    void display(){
        // bst display
    }
    struct node* inserted(struct node* node, int key)
    {
        if (node == NULL) return newNode(key);
        if (key < node->data)
            node->left  = inserted(node->left, key);
        else if (key > node->data)
            node->right = inserted(node->right, key);
        return node;
    }
    bool check_for_this_id(int uni,struct node *temp){
        if(temp!=NULL){
            if(temp->data==uni){
                return true;
            }
            if(temp->data>uni){
                return check_for_this_id(uni,temp->left);
            }
            else {
                return check_for_this_id(uni,temp->right);
            }
        }
        return false;
    }
    int next_song(int repeat_all){
        if(counter<size){
            counter ++;
            int new_id=rand()%size;
            while(check_for_this_id(new_id,head)){ // true means the id is present hence it will genrate new id
                
                new_id=rand()%size;
            }
            if(head==NULL)head=inserted( head,new_id);
            else inserted( head,new_id);
            return new_id;
        }
        return -1;// no null value
        
    }
    void reset_shuffle(){
        counter=0;
        dele_bst(head);
        head=NULL;
    }
    void dele_bst(struct node *temp){
        if(temp!=NULL){
            dele_bst(temp->right);
            dele_bst(temp->left);
            delete (temp);
        }
    }
    void mark_this_del(int songid){ //it will not let id of deleted song to be played again
        //nothing to worry
    }
    void reducesize(){
        counter--;
    }
};

#endif /* shuffle_h */
