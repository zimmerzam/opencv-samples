g++  -g -Wall -Wno-unused-function $(pkg-config --cflags --libs opencv) $1 -o $2
