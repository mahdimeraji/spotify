#include "Artist.hpp"

Artist::Artist(string username_, string password_) {
    username = username_;
    password = password_;
}
Artist::~Artist() {}

string Artist::get_username() {
    return username;
}

bool Artist::check_password(const string& password_) {
    if (password_ == password)
        return true;
    return false;
}

void Artist::print_info(){
    cout<<Id<<", "<<"artist, "<<username<<", "<<endl;
}

void Artist::print_all_info(){
    cout<<"ID: "<<Id<<endl<<"Mode: "<<"user"<<endl;
    cout<<"Username: "<<username<<endl;
    cout<<"Songs: ";
}


