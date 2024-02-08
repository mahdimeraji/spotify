#include "System_Interface.hpp"

System_Interface::~System_Interface() {
    delete system;
}
System_Interface::System_Interface() {
    system = new System();
}

void System_Interface::run() {
    string input_line;
    while(getline(cin, input_line)) {
        try {
            command_line.clear();
            command_line.str(input_line);
            handle_command();
        }
        catch (const Bad_request& e) {
            cout << e.what() << endl;
        }
        catch (const Not_Found& e) {
            cout << e.what() << endl;                                       
        }
        catch (const Permission_denied& e) {
            cout << e.what() << endl;
        }
    }
}

void System_Interface::handle_command() {
    string request;
    string command;
    bool is_playlist=false;
    command_line >> request;
    command_line >> command;

    if (request == REQ_GET) {
        auto iterator = GET_commands.find(command);
        if (iterator == GET_commands.end())
            throw Not_Found();
        (this->*(iterator->second))();
    }
    else if (request == REQ_POST) {
        auto iterator = POST_commands.find(command);
        if (iterator == POST_commands.end())
            throw Not_Found();
        (this->*(iterator->second))();
    }
    else if (request == REQ_DELETE) {
        auto iterator = DELETE_commands.find(command);
        if (iterator == DELETE_commands.end())
            throw Not_Found();
        (this->*(iterator->second))();
    }else if (request == REQ_PUT) {
        auto iterator = PUT_commands.find(command);
        if (iterator == PUT_commands.end())
            throw Not_Found();
        (this->*(iterator->second))();
    }
    else 
        throw Bad_request(); 
}

bool System_Interface::cmnd_dlmtr_check() {
    string dlmtr;
    command_line >> dlmtr;
    if (dlmtr == "")
        return false;
    if (dlmtr != COMMAND_DELIMITER)
        throw Bad_request();
    return true;
}

bool System_Interface::cmnd_end_check() {
    string end_input;
    
    command_line >> end_input;
   
    if (end_input.empty())
        return true;
    return false;
}

bool System_Interface::check_reapeted_input_type(const vector<string>& inputs_type) {
    int size_vec = inputs_type.size();
    for(int i = 0; i < size_vec - 1; i++) {
        for (int j = i + 1; j < size_vec; j++) {
            if (inputs_type[i] == inputs_type[j]) 
                return false;
        }
    }
    return true;
}

bool System_Interface::has_empty_field(const vector<string>& inputs, const vector<string>& needed_inputs) {
    unordered_set<string> input_set(inputs.begin(), inputs.end());

    for (string s : needed_inputs) {
        if (input_set.find(s) == input_set.end())
            return true;
    }
    return false;
}

void System_Interface::signup() {
    string input_type;
    string username;
    string password;
    string mode;
    if (!cmnd_dlmtr_check())
        throw Bad_request();

    vector<string> inputs_type;

    for (int i = 0; i < 3; i++) {
        command_line >> input_type;
        inputs_type.push_back(input_type);
        if (input_type == USERNAME)
            command_line >> username;
        else if (input_type == PASSWORD)
            command_line >> password;
        else if (input_type == MODE)
            command_line >> mode;
        else
           throw Bad_request();
    }
    
    if (!check_reapeted_input_type(inputs_type))
        throw Bad_request();

    if(!cmnd_end_check()) 
        throw Bad_request();

    if (has_empty_field(inputs_type, signup_field))
        throw Bad_request();
    
    system->signup(username, password,mode);
        print_successful_message();
}

void System_Interface::login() {
    string input;
    string username;
    string password;
    vector<string> inputs_type;
    
    if (!cmnd_dlmtr_check())
        throw Bad_request();

    for (int i = 0; i < 2; i++) {
        command_line >> input;
        inputs_type.push_back(input);
        if (input == USERNAME)
            command_line >> username;
        else if (input == PASSWORD)
            command_line >> password;
        else
            throw Bad_request();
    }
    if (!cmnd_end_check())
        throw Bad_request();

    if (!check_reapeted_input_type(inputs_type))
        throw Bad_request();

    if (has_empty_field(inputs_type, login_field))
        throw Bad_request();

    system->login(username, password);
    print_successful_message();
}

void System_Interface::logout() {
    if (!cmnd_dlmtr_check())
        throw Bad_request();
    system->logout();
    print_successful_message();
}

void System_Interface::make_playlist() {
    if (!cmnd_dlmtr_check())
        throw Bad_request();
    string input;
    string playlist_name;
    command_line >> input;
    if (input != NAME)
        throw Bad_request();

    command_line >> playlist_name;

    if (!cmnd_end_check())
        throw Bad_request();
    
    system->make_playlist(playlist_name);
    print_successful_message();
}

void System_Interface::post_music() {
    string input_type;
    string title;
    string path;
    string year;
    string album;
    string tags;
    string duration;

    if (!cmnd_dlmtr_check())
        throw Bad_request();

    vector<string> inputs_type;

    for (int i = 0; i < 6; i++) {
        command_line >> input_type;
        inputs_type.push_back(input_type);
        if (input_type == TITLE)
            command_line >> title;
        else if (input_type == PATH)
            command_line >> path;
        else if (input_type == YEAR)
            command_line >> year;
        else if (input_type == ALBUM)
            command_line >> album;
        else if (input_type == TAGS)
            command_line >> tags;
        else if (input_type == DURATION)
            command_line >> duration;
        else
           throw Bad_request();
    }
    
    if (!check_reapeted_input_type(inputs_type))
        throw Bad_request();

    if(!cmnd_end_check()) 
        throw Bad_request();

    if (has_empty_field(inputs_type, post_music_field))
        throw Bad_request();

    system->post_musics(title,path,year, album, tags,duration);
    print_successful_message();
}

void System_Interface::get_musics(){
        string input;
        string id;
    
        if (!cmnd_dlmtr_check())
        throw Bad_request();

        command_line >> input;
        if(!input.empty()){
        if(input!=ID)
            throw Bad_request();
        else{
            command_line >> id;
            system->get_music(id);
        }
        }else if(cmnd_end_check())
        system->get_musics();
}

void System_Interface::get_user() {
    string input;
    string id;
        if (!cmnd_dlmtr_check())
            throw Bad_request();
        command_line >> input;
        if(!input.empty()){
        if(input!=ID)  
            throw Bad_request();   
        command_line>>id;
        system->get_user(id);            
        }
    else if (cmnd_end_check())
        system->get_users();
}

void System_Interface:: get_users(){
        if (!cmnd_dlmtr_check())
        throw Bad_request();
        system->get_users();
}

void System_Interface:: add_playlist(){
    string input;
    string name;
    string id;
    vector<string> inputs_type;
    
    if (!cmnd_dlmtr_check())
        throw Bad_request();

    for (int i = 0; i < 2; i++) {
        command_line >> input;
        inputs_type.push_back(input);
        if (input == NAME)
            command_line >> name;
        else if (input == ID)
            command_line >> id;
        else
            throw Bad_request();
    }
    if (!cmnd_end_check())
        throw Bad_request();

    if (!check_reapeted_input_type(inputs_type))
        throw Bad_request();

    if (has_empty_field(inputs_type, add_playlist_field))
        throw Bad_request();

    system->add_playlist(name,id);
    print_successful_message();
}

void System_Interface:: get_playlist(){
    string input;
    string user_id;

    if (!cmnd_dlmtr_check())
            throw Bad_request();

        command_line >> input;
        if (input == ID)
            command_line >> user_id;
        else
            throw Bad_request();
    if (!cmnd_end_check())
        throw Bad_request();

    system->get_playlist(user_id);  
}

void System_Interface::search_music(){
    string input_type;
    string name;
    string artist;
    string tag;
    if (!cmnd_dlmtr_check())
        throw Bad_request();

    vector<string> inputs_type;

    for (int i = 0; i < 3; i++) {
        command_line >> input_type;
        inputs_type.push_back(input_type);
        if (input_type == NAME)
            command_line >> name;
        else if (input_type == ARTIST)
            command_line >> artist;
        else if (input_type == TAG)
            command_line >> tag;
        else
           throw Bad_request();

    }
    
    if (!check_reapeted_input_type(inputs_type))
        throw Bad_request();

    if(!cmnd_end_check()) 
        throw Bad_request();

    if (has_empty_field(inputs_type, search_music_field))
        throw Bad_request();

 //   system->search_music(name,artist,tag);
    print_successful_message();
}

void System_Interface:: del_music(){
    string input;
    string id;
    
    if (!cmnd_dlmtr_check())
        throw Bad_request();

    command_line >> input;
    if (input == ID)
        command_line >> id;
    else
        throw Bad_request();
    if (!cmnd_end_check())
        throw Bad_request();

    system->del_music(id);
    print_successful_message();   
}

void System_Interface:: get_registered_musics(){
        if (!cmnd_dlmtr_check())
        throw Bad_request();
        system->get_registered_musics();
}

void System_Interface::print_successful_message() {
    cout << M_SUCCESSFUL_COMMAND;
}


