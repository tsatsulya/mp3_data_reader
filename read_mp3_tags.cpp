#include "read_mp3_tags.h"
#include <vector>

int get_file_size(FILE *file) {

	int location = ftell(file);

	fseek(file,0,SEEK_END);
	int size = ftell(file);

	fseek(file, location, SEEK_SET);
	return size;
}

std::string simple_bites_reader(FILE *mp3_file, int num_of_bytes, int readloc) {

	std::string buffer(num_of_bytes, '\0');

	fseek(mp3_file, readloc, SEEK_SET); //?
	fread(&buffer[0], 1, num_of_bytes, mp3_file);

	return buffer;
}

bool check_symbol(char i) {
	return i && (int(i) > 31);
}

std::vector<std::string> get_tags(std::string text_with_garbage) {

	std::vector<std::string> words = {""};

	for (char i: text_with_garbage) {
		if (check_symbol(i)) {
			words.back()+=i;
		}
		else {
			if (words.back().length() != 0) words.push_back("");
		}
	}

	// for (std::string i: words) {
	// 	std::cout << i << std::endl;
	// }
	return words;
}

bool check_mp3_format(FILE *mp3_file) {

	if (simple_bites_reader(mp3_file, 3) == "ID3")
		return true;

	return false;
}
