#ifndef _USER_HPP_
#define _USER_HPP_

#include "Exceptions.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include "PlayList.hpp"
#include "Music.hpp"
using namespace std;

class User {
public:
    User(string username_, string password_);
    ~User();
    string get_username();
    void set_id(int id){Id=id;}
    int  get_id(void){return Id;}
    bool check_password(const string& password_);
    void print_info();
    void print_all_info();
    void make_playlist(string PlayList_name);
    void add_playlist(string PlayList_name ,Music* music);
    void get_playlists();

private:
    string username;
    string password;
    int Id;
    vector<PlayList*> playlists;
    int num_of_playlists;

    
};


#endif