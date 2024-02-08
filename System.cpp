#include "System.hpp"

System::~System() {
    for (User* u : users)
        delete u;
    users.clear();
    for (Artist* a : artists)
        delete a;
    artists.clear();

}
System::System() {

    num_of_artists=0;
    num_of_users=0;


    logged_in_user = nullptr;
    logged_in_artist = nullptr;
}

string System::getStringInsideBrackets(const string& input) {
    if (input.size() < 2 || input.front() != '<' || input.back() != '>') {
        throw Bad_request();
    }
    
    return input.substr(1, input.size() - 2);
}

bool System::username_is_already_taken(const string& username) {
    if (find_user(username) == nullptr)
        return false;
    return true;    
}

User* System::find_user(const string& username) {
    
    for (User* u : users)
        if (u->get_username() == username)
            return u;
    return nullptr;
}

Artist* System::find_artist(const string& username) {
    
    for (Artist* a : artists)
        if (a->get_username() == username)
            return a;
    return nullptr;
}

void System::signup(const string& username, const string& password,const string& mode) {

    
    if(getStringInsideBrackets(mode)==USER)
        signup_user(getStringInsideBrackets(username),getStringInsideBrackets(password));
    else if(getStringInsideBrackets(mode)==ARTIST)
        signup_artist(getStringInsideBrackets(username),getStringInsideBrackets(password));
    else
        throw Bad_request();
}

void System::signup_user(const string& username, const string& password) {
    if(username_is_already_taken(username))
        throw Bad_request();
    if(logged_in_user!=nullptr){
        if(logged_in_user->get_username() ==username)
        throw Bad_request();
    }
    User* new_user = new User(username, password);
    users.push_back(new_user);
    
    logged_in_user = new_user;
    num_of_users++;
    logged_in_user->set_id(num_of_users+num_of_artists);
}

void System::signup_artist(const string& username, const string& password) {
    if(username_is_already_taken(username))
        throw Bad_request();
    if(logged_in_artist!=nullptr){
        if(logged_in_artist->get_username() ==username)
        throw Bad_request();
    }
    Artist* new_artist = new Artist(username, password);
    artists.push_back(new_artist);
    
    logged_in_artist = new_artist;
    num_of_artists++;
    logged_in_artist->set_id(num_of_artists+num_of_users);
}

void System::login(const string& username, const string& password) {
    User* login_user = find_user(getStringInsideBrackets(username));
    if (login_user == nullptr) {
        Artist* login_artist = find_artist(getStringInsideBrackets(username));
        if (login_artist == nullptr)
            throw Bad_request();
        if (!login_artist->check_password((getStringInsideBrackets(password))))
            throw Permission_denied();
        
        logged_in_user = nullptr;
        logged_in_artist = login_artist;  
    }
    else {
        if (!login_user->check_password(getStringInsideBrackets(password)))
            throw Permission_denied();
        
        logged_in_user = login_user;  
        logged_in_artist = nullptr;  
    }
}

void System::logout() {
    if (logged_in_user == nullptr && logged_in_artist== nullptr)
        throw Permission_denied();
    logged_in_user = nullptr;
    logged_in_artist = nullptr;
}

void System::post_musics(string title_,string path_,string year_,string album_,string tags_,string duration_){
    if (logged_in_artist== nullptr){
        throw Permission_denied();
    }

    Music *new_music;
    new_music=new Music(logged_in_artist,getStringInsideBrackets(title_),getStringInsideBrackets(path_),getStringInsideBrackets(year_)
                        ,getStringInsideBrackets(album_),getStringInsideBrackets(tags_),getStringInsideBrackets(duration_));
    num_of_musics++;
    new_music->set_id(num_of_musics);
    musics.push_back(new_music);
}

void System::get_music(string id) {
    if (logged_in_user == nullptr && logged_in_artist== nullptr)
        throw Permission_denied(); 
    string idd=getStringInsideBrackets(id);
    if (stoi(idd)>num_of_musics)
        throw Not_Found();
    for(int i=0;i<musics.size();i++){
        if (to_string(musics[i]->get_id())==idd){
            cout<<"ID"<<VIRGOUL<<" "<<NAME<<VIRGOUL<<" "<<"Year, "<<"Album, "
            <<"Tags, "<<"Duration"<<endl;
            musics[i]->print_all_info();
        } 
    }
    
}

void System::get_musics(){
    if (logged_in_user == nullptr && logged_in_artist== nullptr)
        throw Permission_denied();
    if(musics.size()==0)
        cout<<M_EMPTY_LIST;
        else{
            cout<<"ID"<<VIRGOUL<<" "<<NAME<<VIRGOUL<<" "<<"Artist"<<endl;
            for(int i=0;i<musics.size();i++){
                musics[i]->print_info();
            }
        }
     
}

void System::get_user(string id){
    string idd=getStringInsideBrackets(id);
    if(stoi(idd)>num_of_users+num_of_artists)
        throw Not_Found();
    if (logged_in_user == nullptr && logged_in_artist== nullptr)
        throw Permission_denied(); 
    for(int j=0; j<num_of_users;j++)
            {

            if(users[j]->get_id()==stoi(idd)){
                users[j]->print_all_info();}
        }
        for(int j=0; j<num_of_artists;j++)
            {
            if(artists[j]->get_id()==stoi(idd)){
                artists[j]->print_all_info();}
            }
    }   

void System::get_users() {
    if (logged_in_user == nullptr && logged_in_artist== nullptr)
        throw Permission_denied(); 
    bool is_there_user = false;
    cout<<"ID"<<VIRGOUL<<" "<<Mode<<VIRGOUL<<" "<<Username<<VIRGOUL<<" "<<NUMBERS<<endl;
    for(int i = 1; i <= num_of_artists+num_of_users; i++) {
        for(int j=0; j<num_of_users;j++)
            {

                if(users[j]->get_id()==i){
                    users[j]->print_info();
                    is_there_user=true;}
        }
        for(int j=0; j<num_of_artists;j++)
            {
                if(artists[j]->get_id()==i){
                    artists[j]->print_info();
                    is_there_user=true;}
            }
    }
    if (!is_there_user)
        cout << M_EMPTY_LIST;
}

void System::make_playlist(string PlayList_name){
    if (logged_in_user == nullptr )
        throw Permission_denied(); 
    logged_in_user->make_playlist(getStringInsideBrackets(PlayList_name));
   
}

void System::add_playlist(string name, string id){
    if (logged_in_user == nullptr )
        throw Permission_denied(); 
    string idd=getStringInsideBrackets(id);
    string name_=getStringInsideBrackets(name);
    if(stoi(idd)>num_of_musics)
        throw Not_Found();
    for(int i=0;i<musics.size();i++){
        if(musics[i]->get_id()==stoi(idd))
            logged_in_user->add_playlist(name_,musics[i]);
    } 
}

void System::get_playlist(string id){
    if(logged_in_user==nullptr)
        throw Permission_denied();
    string idd= getStringInsideBrackets(id);
    bool found_user = false;
    for(int i=0; i<users.size();i++){
        if(users[i]->get_id()==stoi(idd)){
            users[i]->get_playlists();
            found_user=true;
            }
    }
            if(found_user==false)
            throw Not_Found();
}

void System::del_music(string id){
    if(logged_in_artist==nullptr)
        throw Permission_denied();
    string idd=getStringInsideBrackets(id);
    if(stoi(idd)>num_of_artists)
        throw Not_Found();
    if (musics[stoi(idd) - 1]->get_artist() != logged_in_artist)
        throw Not_Found();
    
    delete musics[stoi(idd)-1];
    musics.erase(musics.begin() + (stoi(idd)-1));
    
    
}

void System::get_registered_musics(){
    if(logged_in_artist==nullptr)
        throw Permission_denied();
    bool found_musics=false;
    for(int i=0;i<musics.size(); i++){
        if(musics[i]->get_artist()==logged_in_artist){
            musics[i]->print_all_info();
            found_musics=true;
        }
    }
    if(found_musics==false )
        cout<< M_EMPTY_LIST;
}