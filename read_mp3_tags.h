#pragma once 

#include <iostream>
#include <vector>

typedef struct {
	std::string title;
	std::string artist;
	std::string album;
	std::string year;
	std::string comment;
	std::string genre;
	std::string album_artist;

} mp3_tags;

std::vector<std::string> get_tags(std::string text_with_garbage);
bool check_symbol(char i);

bool check_mp3_format(FILE *mp3_file);
int get_file_size(FILE *mp3_file);

std::string simple_bites_reader(FILE *mp3_file, int num_of_bytes, int readloc = SEEK_CUR-1);
void read_tags(FILE *mp3_file, mp3_tags *tags);
