#ifndef _ARTIST_HPP_
#define _ARTIST_HPP_

#include "Exceptions.hpp"
#include <string>
#include <iostream>
using namespace std;

class Artist {
public:
    Artist(string username_, string password_);
    ~Artist();
    string get_username();
    void set_id(int id){Id = id;}
    int get_id(void){return Id;}
    bool check_password(const string& password_);
    void print_info();
    void print_all_info();
    void get_registered_musics();
private:
    string username;
    string password;
    int Id;

};


#endif