#pragma once 

#include <iostream>
#include <vector>
#include <map>
struct mp3_info {
    std::string title = "unknown title";
    std::string artist = "unknown artist";
    std::string album = "unknown album";
    std::string comment = "empty comment";
    std::string date = "00_00_00";
    std::string year = "0000";
    std::string genre = "unknown genre";
};

//title: TIT2 TIT3
//album: TALB
//composer: TCOM
//genre: TCON
//date: tyer tdat
//artist: tpe1
//album_artist: tpe2

mp3_info read_mp3_info(const char *file_name);
void print_mp3_info(mp3_info& info);
