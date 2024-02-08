#include  "Music.hpp"

Music::Music(Artist* artist_ ,string title_, string path_ ,string year_, string album_,string tags_, string duration_){
   
    artist=artist_;

    title=title_;
    path=path_;
    year=year_;
    album=album_;
    duration= duration_;
    tagss=tags_;
    store_tags(tags_);
}

Music::~Music() {};


void Music::print_info(){
    cout<<Id<<", "<<title<<", "<<artist->get_username()<<endl;
}

void Music::print_all_info(){
    cout<<Id<<", "<<title<<", "<<artist->get_username()<<", "<<year<<", "
    <<album<<", "<<tagss<<", "<<duration<<endl;
}

vector<string> splitString(const std::string &input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream tokenStream(input);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


void Music::store_tags(string tags_){
    tags = splitString(tags_, ';');
}

Artist* Music::get_artist(){
    return artist;
}


