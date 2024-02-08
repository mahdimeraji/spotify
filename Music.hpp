#ifndef _MUSIC_HPP_
#define _MUSIC_HPP_

#include "Exceptions.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Artist.hpp"
#include <sstream>
using namespace std;

class Music {
public:
    Music(Artist* artist_, string title_, string path_ ,string year_, string album_,string _tags, string duration );
    ~Music();
    void set_id(int id){Id=id;}
    int get_id(){return Id;}  
    void print_info();
    void print_all_info();
    string get_duration(){return duration;};
    Artist* get_artist();


private:

    Artist* artist;
    int Id;
    string tagss;
    string title;
    string path;
    string year;
    string album;
    string duration;

    vector<string> tags;

    void store_tags(string tags_);
    
};


#endif