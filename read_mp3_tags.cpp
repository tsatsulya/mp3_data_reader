#include "read_mp3_tags.h"
#include <algorithm>


std::string simple_bites_reader(FILE *mp3_file, int num_of_bytes, int readloc = SEEK_CUR-1) {

	std::string buffer(num_of_bytes, '\0');

	fseek(mp3_file, readloc, SEEK_SET); //?
	fread(&buffer[0], 1, num_of_bytes, mp3_file);

	return buffer;
}


bool check_symbol(char i) {
	return i && (int(i) > 31);
}


std::vector<std::string> get_words(std::string text_with_garbage) {

	std::vector<std::string> words = {""};

	for (char i: text_with_garbage) {
		if (check_symbol(i)) {
			words.back()+=i;
		}
		else {
			if (words.back().length() != 0) words.push_back("");
		}
	}
	return words;
}


std::vector<std::string> id3v1_tags = {"Title", "Artist", "Album", "Year", "Comment", "Track" , "Genre"};

std::vector<std::string> id2v2_2_tags =                             \
	{"BUF", "CNT", "COM", "CRA", "CRM"  , "ETC", "EQU", "GEO",      \
	"IPL", "LNK", "MCI", "MLL", "PIC", "POP", "REV", "RVA", "SLT",  \
	"STC", "TAL", "TBP", "TCM", "TCO", "TCR", "TDA", "TDY", "TEN",  \
	"TFT", "TIM", "TKE", "TLA", "TLE", "TMT", "TOA", "TOF", "TOL",  \
	"TOR", "TOT", "TP1", "TP2", "TP3", "TP4", "TPA", "TPB", "TRC",  \
	"TRD", "TRK", "TSI", "TSS", "TT1", "TT2", "TT3", "TXT", "TXX",  \
	"TYE", "UFI", "ULT", "WAF", "WAR", "WAS", "WCM", "WCP", "WPB",  \
	"WXX"};

std::vector<std::string> id3v2_3_tags =                              \
	{"COMM", "COMR", "ENCR", "EQUA", "ETCO", "GEOB", "GRID", "IPLS", \
	"LINK", "MCDI", "MLLT", "OWNE", "PRIV", "PCNT", "POPM", "POSS",  \
	"RBUF", "RVAD", "RVRB", "SYLT", "SYTC", "TALB", "TBPM", "TCOM",  \
	"TCON", "TCOP", "TDAT", "TDLY", "TENC", "TEXT", "TFLT", "TIME",  \
	"TIT1", "TIT2", "TIT3", "TKEY", "TLAN", "TLEN", "TMED", "TOAL",  \
	"TOFN", "TOLY", "TOPE", "TORY", "TOWN", "TPE1", "TPE2", "TPE3",  \
	"TPE4", "TPOS", "TPUB", "TRCK", "TRDA", "TRSN", "TRSO", "TSIZ",  \
	"TSRC", "TSSE", "TYER", "TXXX", "UFID", "USER", "USLT", "WCOM",  \
	"WCOP", "WOAF", "WOAR", "WOAS", "WORS", "WPAY", "WPUB", "WXXX"};

std::vector<std::string> id3v2_4_tags =                              \
	{"AENC", "APIC", "ASPI", "COMM", "COMR", "ENCR", "EQU2", "ETCO", \
	"GEOB", "GRID", "LINK", "MCDI", "MLLT", "OWNE", "PRIV", "PCNT",  \
	"POPM", "POSS", "RBUF", "RVA2", "RVRB", "SEEK", "SIGN", "SYLT",  \
	"SYTC", "TALB", "TBPM", "TCOM", "TCON", "TCOP", "TDEN", "TDLY",  \
	"TDOR", "TDRC", "TDRL", "TDTG", "TENC", "TEXT", "TFLT", "TIPL",  \
	"TIT1", "TIT2", "TIT3", "TKEY", "TLAN", "TLEN", "TMCL", "TMED",  \
	"TMOO", "TOAL", "TOFN", "TOLY", "TOPE", "TOWN", "TPE1", "TPE2",  \
	"TPE3", "TPE4", "TPOS", "TPRO", "TPUB", "TRCK", "TRSN", "TRSO",  \
	"TSOA", "TSOP", "TSOT", "TSRC", "TSSE", "TSST", "TXXX", "WCOM",  \
	"WCOP", "WOAF", "WOAR", "WOAS", "WORS", "WPAY", "WPUB", "WXXX"};


static std::map<std::string, std::vector<std::string>> metadata_main_tags = {
	{"YEAR", {"Year", "TYE", "TYER"}},
	{"DATE", {"TDA", "TDAT", "TDOR", "TDRL"}},
	{"TITLE", {"TIT2", "TT2", "Title"}},
	{"ARTIST", {"TPE1", "TP1", "Artist"}},
	{"GENRE", {"TCON", "TCO", "Genre"}},
	{"ALBUM", {"TALB", "TAL", "Album"}},
	{"COMMENT", {"COM", "COMM", "Comment"}},
};

static std::map<std::string, std::string mp3_info::*> metadata = {
	{"YEAR", &mp3_info::year},
    {"TITLE",  &mp3_info::title},
    {"ARTIST", &mp3_info::artist},
    {"ALBUM",  &mp3_info::album},
    {"COMMENT", &mp3_info::comment},
    {"DATE", &mp3_info::date},
    {"GENRE", &mp3_info::genre},
};


template<typename T> 
bool element_is_contained(T elem, std::vector<T> vec) {

	if (vec.size()) 
		return std::find(vec.begin(), vec.end(), elem) != vec.end();
	return false;
}


std::map<std::string, std::string> extract_tag_values(std::vector<std::string>& words) {

	std::string tag = "";
	std::map<std::string, std::string> tag_values{{"", ""}};

	for (std::string i: words) {
		if (element_is_contained(i, id3v2_4_tags) || element_is_contained(i, id3v2_3_tags) || \
			element_is_contained(i, id2v2_2_tags) || element_is_contained(i, id3v1_tags)) {

			tag_values[i] = "";
			tag = i;
		}
		else
			tag_values[tag]+=i;
	}

	return tag_values;
}


void fill_mp3_info(mp3_info& track_info, std::map<std::string, std::string>& tags) {

	for (auto& tag: tags) {
		for (auto& main_tag: metadata_main_tags) {
			if (std::find(main_tag.second.begin(), main_tag.second.end(), tag.first) != main_tag.second.end()) {
				track_info.*metadata[main_tag.first] = tag.second;
			}
		}
	}
}


void print_mp3_info(mp3_info& info) {

	for (auto& field: metadata) 
		std::cout << field.first << '\t' << info.*field.second << std::endl;
}


bool check_mp3_format(FILE *mp3_file) {

	if (simple_bites_reader(mp3_file, 3) == "ID3")
		return true;

	return false;
}


mp3_info read_mp3_info(const char *file_name) {

	FILE* file = fopen(file_name, "r");

	mp3_info info;

	if (!file || !check_mp3_format(file)) return info; //<--------------------error!!!!!!!!!!!!!!!!!!!!!!!!

	std::string tags_without_header = simple_bites_reader(file, 600, 10);
	std::vector<std::string> words = get_words(tags_without_header);

	std::map<std::string, std::string> tag_values = extract_tag_values(words);
	fill_mp3_info(info, tag_values);

	return info;
}