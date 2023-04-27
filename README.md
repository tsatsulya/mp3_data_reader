# mp3_data_reader
This is a small simple tool for reading basic track metadata in ID3 encoding - Title, Artist, Album, Comment, Date, Year, Genre

## Usage

```cpp

#include <iostream>
#include "read_mp3_tags.h"

int main() {
  mp3_info info = read_mp3_info("/home/varvara/Music/Yes - The Ice Bridge.mp3");

  print_mp3_info(info);
  return 0;
}
```
```bush
ALBUM		The Quest
ARTIST		Yes
COMMENT		empty comment
DATE		2021-10-01
GENRE		unknown genre
TITLE		The Ice Bridge
YEAR		2021
```
