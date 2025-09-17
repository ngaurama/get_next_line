# get_next_line

A C function that reads a line from a file descriptor, part of the 42 Common Core curriculum.
This project implements a function that returns lines one by one, handling files and standard input efficiently without reading the entire content at once

---

## Features

get_next_line(int fd) : Reads from the given file descriptor and returns one line per call.

Returns NULL when there’s nothing left to read or if an error occurs.
The returned line includes the newline character (\n), except at the end of the file if no newline exists.

Supports multiple file descriptors simultaneously (bonus):

You can read from fd 3, then fd 4, then fd 5, and back to fd 3, without mixing lines between descriptors.

Uses a single static variable (bonus requirement) to maintain reading state per file descriptor.

Efficient reading:
Reads only as much data as necessary per call.
Works with any BUFFER_SIZE defined at compile-time via -D BUFFER_SIZE=n.

---

## Project Structure

```
├── get_next_line.c               # Core function for mandatory part
├── get_next_line_utils.c         # Helper functions for mandatory part
├── get_next_line_bonus.c         # Core function for bonus (multiple FDs)
├── get_next_line_utils_bonus.c   # Helper functions for bonus
├── get_next_line.h               # Header file for mandatory part
└── get_next_line_bonus.h         # Header file for bonus
```

---

## Installation

### Clone
```bash
git clone https://github.com/ngaurama/get_next_line.git
cd get_next_line
```

### Usage

Include the header in your C programs:
```
#include "get_next_line.h"

int main(void) {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}

```

Compile with a custom buffer size (optional):
```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_file.c get_next_line.c get_next_line_utils.c -o your_binary
```
---

### Learning Outcomes

Through this project, I gained experience with:
+ Managing file descriptors and reading files efficiently.
+ Working with static variables to maintain state across function calls.
+ Implementing modular C code with helper functions.
+ Handling dynamic memory safely (malloc/free).
+ Managing multiple file descriptors simultaneously (bonus).
---
## Author
+ Nitai Gauramani
  - 42 Paris – Common Core project <br>

![Nitai's GitHub stats](https://github-readme-stats.vercel.app/api?username=ngaurama&show_icons=true&theme=transparent)
