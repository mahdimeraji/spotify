#ifndef _PLAYLIST_HPP_
#define _PLAYLIST_HPP_

#include "Exceptions.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Music.hpp"
#include <sstream>
using namespace std;

class PlayList {
public:
    PlayList(string playlist_name);
    ~PlayList();
    string get_name(){return name;}
    void add_music(Music* music);
    int get_num_of_musics(){return musics.size();}
    string get_duration(){return duration;}

private:

    void add_to_duration(Music* music);

    vector<Music*> musics;
    string name;
    string duration;
 
    
};


#endif