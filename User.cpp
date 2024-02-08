#include "User.hpp"

User::User(string username_, string password_) {
    username = username_;
    password = password_;
    num_of_playlists=0;
}
User::~User() {}

string User::get_username() {
    return username;
}

bool User::check_password(const string& password_) {
    if (password_ == password)
        return true;
    return false;
}

void User::print_info(){
    cout<<Id<<", "<<"user, "<<username<<", "<<num_of_playlists<< endl;
}

void User::print_all_info(){
    cout<<"ID: "<<Id<<endl<<"Mode: "<<"user"<<endl;
    cout<<"Username: "<<username<<endl;
    cout<<"Playlists: "<<endl;;
}

void User::make_playlist(string PlayList_name){

    PlayList* new_playlist = new  PlayList (PlayList_name);
    playlists.push_back(new_playlist);
    num_of_playlists++;
}

void User::add_playlist(string PlayList_name,Music* music){
    for(int i=0; i<playlists.size();i++){
        if(playlists[i]->get_name()==PlayList_name)
            playlists[i]->add_music(music);
    }
}

void User::get_playlists(){
    
        sort(playlists.begin(), playlists.end(), []( PlayList* a,  PlayList* b) {
        return a->get_name() < b->get_name();
    });
    cout<<"Playlist_name, Songs_number, Duration"<<endl;
    for (int i = 0; i < playlists.size(); i++) {
            cout << playlists[i]->get_name()<<", "<<playlists[i]->get_num_of_musics() <<", "<<playlists[i]->get_duration()<< endl;  
    }
}

