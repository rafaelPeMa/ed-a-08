#ifndef BROADCASTER_H_INCLUDED
#define BROADCASTER_H_INCLUDED

#include <iostream>
#include <string>

#include "list.h"
#include "song.h"

class Broadcaster {

    private:
        bool orderByName;
        bool orderByAuthor;

        List<Song>* songs;
        int isPosValid(std::string);
        void showMenu();
        void addSong();
        void editSong();
        void deleteSong();
        void enterToContinue();
        void orderData();
        void searchSong();

    public:
        Broadcaster(List<Song>*);
    };

#endif // BROADCASTER_H_INCLUDED
