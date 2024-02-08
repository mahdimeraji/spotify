#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include "Exceptions.hpp"
#include "User.hpp"
#include "Artist.hpp"
#include "Music.hpp"
#include "PlayList.hpp"


#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
const string USER = "user";
const string ARTIST= "artist";
const string ARtist= "Artist";
const string NAME ="name";
const string Username="Username";
const string Mode= "Mode";
const string NUMBERS ="Playlists_number/Songs_number";
const string VIRGOUL=",";
const string M_SUCCESSFUL_COMMAND = "OK\n";
const string M_EMPTY_LIST = "Empty\n";

class System {
public:
    ~System();
  System();

    void signup_user(const string& username, const string& password);
    void signup_artist(const string& username, const string& password);
    void signup(const string& username, const string& password,const string& mode);
    void login(const string& username, const string& password);
    void logout();

    void post_musics(string title_,string path_,string year_,string album_,string tags_,string duration_);
    void make_playlist(string PlayList_name);
    void get_user(string id);
    void get_users();
    void get_musics();
    void get_music(string id);
    void get_playlist(string id);

    void add_playlist(string name,string id);

    void del_music(string id);

    void get_registered_musics();

private:
    int num_of_artists;
    int num_of_users;
    int num_of_musics;



    vector<User*> users;
    vector<Artist*> artists;
    vector<Music*> musics; 
    User* logged_in_user;
    Artist* logged_in_artist;
    vector<string> split(const string& line,char delimiter);

    bool username_is_already_taken(const string& username);
    User* find_user(const string& username);
    Artist* find_artist(const string& username);
    string getStringInsideBrackets(const string& input);
};


#endif