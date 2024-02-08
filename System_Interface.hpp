#ifndef _SYSTEM_INTERFACE_HPP_
#define _SYSTEM_INTERFACE_HPP_


#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <sstream>
#include "Exceptions.hpp"
#include "System.hpp"
using namespace std;


const string REQ_GET = "GET";
const string REQ_POST = "POST";
const string REQ_DELETE = "DELETE";
const string REQ_PUT = "PUT";
const string COMMAND_DELIMITER ="?";

const string ID = "id";

const string SIGNUP = "signup";
const string LOGIN =  "login";
const string LOGOUT = "logout";
const string PLAYLIST = "playlist";
const string MUSIC = "music";

const string MUSICS = "musics";
const string USERS = "users";
const string SEARCH_MUSIC = "search_music";
const string REGISTERED_MUSICS = "registered_musics";


const string ADD_PLAYLIST = "add_playlist";

const string  USERNAME = "username";
const string  PASSWORD = "password";
const string  MODE = "mode";



const string TITLE="title";
const string PATH="path";
const string YEAR="year";
const string ALBUM="album";
const string TAG="tag";
const string TAGS="tags";
const string DURATION="duration";



class System_Interface {
public:
    ~System_Interface();
    System_Interface();
    void run();
   
private:
    System* system;
    stringstream command_line;
    
    void handle_command();
    bool cmnd_dlmtr_check();
    bool cmnd_end_check();

    bool check_reapeted_input_type(const vector<string>& inputs_type);
    bool has_empty_field(const vector<string>& inputs, const vector<string>& needed_inputs);

    void print_successful_message();

    void signup();
    void login();
    void logout();

    void make_playlist();
    void post_music();

    void get_musics();
    void get_user();
    void get_users();
    void get_playlist();
    void search_music();
    void get_registered_musics();

    void add_playlist();

    void del_music();


    const vector<string> signup_field = {USERNAME, PASSWORD,MODE};
    const vector<string> login_field = {USERNAME, PASSWORD};
    const vector<string> post_music_field={TITLE,PATH,YEAR,ALBUM,TAGS,DURATION};
    const vector<string> add_playlist_field = {NAME, ID};
    const vector<string> search_music_field = {NAME,ARTIST,TAG};

    typedef void(System_Interface::*call_func_ptr)();

    const unordered_map<string , call_func_ptr> POST_commands = {
        {SIGNUP, &System_Interface::signup},
        {LOGIN, &System_Interface::login},
        {LOGOUT, &System_Interface::logout},
        {PLAYLIST, &System_Interface::make_playlist},
        {MUSIC, &System_Interface::post_music},

    };

    const unordered_map<string, call_func_ptr> GET_commands = {
        {MUSICS, &System_Interface::get_musics},
        {PLAYLIST, &System_Interface::get_playlist},
        {USERS, &System_Interface::get_user},
        {SEARCH_MUSIC, &System_Interface::search_music},
        {REGISTERED_MUSICS, &System_Interface::get_registered_musics},
    };
    
    const unordered_map<string, call_func_ptr> DELETE_commands = {
        {MUSIC, &System_Interface::del_music},
        
    };

    const unordered_map<string, call_func_ptr> PUT_commands = {
         {ADD_PLAYLIST, &System_Interface::add_playlist},

        
    };

};

#endif