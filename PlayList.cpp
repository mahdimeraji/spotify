#include "PlayList.hpp"

PlayList::PlayList(string playlist_name){

    name=playlist_name;
    duration="00:00:00";
}



PlayList::~PlayList(){}

void PlayList::add_music(Music* music){
    musics.push_back(music);
    add_to_duration(music);
    
}


void PlayList::add_to_duration(Music* music) {
    int hours1, minutes1, seconds1;
    char colon;

    string time_str1=music->get_duration();
    string time_str2=duration;
    std::istringstream iss1(time_str1);
    iss1 >> hours1 >> colon >> minutes1 >> colon >> seconds1;

    int hours2, minutes2, seconds2;
    std::istringstream iss2(time_str2);
    iss2 >> hours2 >> colon >> minutes2 >> colon >> seconds2;

    int total_seconds1 = hours1 * 3600 + minutes1 * 60 + seconds1;
    int total_seconds2 = hours2 * 3600 + minutes2 * 60 + seconds2;

    int total_seconds = total_seconds1 + total_seconds2;

    int hours_result = total_seconds / 3600;
    int minutes_result = (total_seconds % 3600) / 60;
    int seconds_result = total_seconds % 60;

    std::ostringstream oss;
    oss << hours_result << ":" << minutes_result << ":" << seconds_result;
    duration= oss.str();
}

