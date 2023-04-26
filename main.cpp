#include <iostream>
#include "read_mp3_tags.h"
#include <vector>
#include <algorithm>
#include <map>


int main() {

	// FILE* mp3_file = fopen("/home/varvara/Music/Rogér Fakhr - Fine Anyway.mp3", "r");
	// std::string header = simple_bites_reader(mp3_file, 10);
	// // std::cout << header.substr(5, 4);
	// std::string title = simple_bites_reader(mp3_file, 600, 10);

	// std::vector<std::string> words = get_words(title);
	// std::map<std::string, std::string> tag_values = extract_tag_values(words);
	
	// // for (const auto& key: tag_values)
	// // 	std::cout << key.first << "\t" << key.second << "\n";

	mp3_info info = read_mp3_info("/home/varvara/projects/mp3_data_reader/Tim Buckley - Once I Was.mp3");

	//fill_mp3_info(info, tag_values);

	print_mp3_info(info);
	return 0;
}

