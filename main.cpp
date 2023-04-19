#include <iostream>
#include "read_mp3_tags.h"
#include <vector>
#include <algorithm>

int main() {

	FILE* mp3_file = fopen("/home/varvara/Music/Connie Converse - There Is a Vine.mp3", "r");

	std::string title = simple_bites_reader(mp3_file, 200, 10);

	std::vector<std::string> words = get_tags(title);
	for (std::string i: words)
		std::cout << i << std::endl;

	return 0;
}

