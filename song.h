#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <string>

class Song {

    private:
        std::string name;
        std::string author;
        std::string interpreter;
        int ranking;
        std::string sourceMP3;

        static int COMPARE;

    public:
        static const int COMPARE_BY_RANKING     = 0;
        static const int COMPARE_BY_NAME        = 1;
        static const int COMPARE_BY_INTERPRETER = 2;
        static const int COMPARE_BY_AUTHOR      = 3;

        Song();
        Song(const Song&);

        std::string getName() const;
        std::string getAuthor() const;
        std::string getInterpreter() const;
        int getRanking() const;
        std::string getSourceMP3() const;

        static int getCompare();

        std::string toString() const;

        void setName(const std::string&);
        void setAuthor(const std::string&);
        void setInterpreter(const std::string&);
        void setRanking(const int&);
        void setSourceMP3(const std::string&);

        static void setCompare(const int&);

        bool operator == (const Song&) const;
        bool operator != (const Song&) const;
        bool operator < (const Song&) const;
        bool operator <= (const Song&) const;
        bool operator > (const Song&) const;
        bool operator >= (const Song&) const;

        Song& operator = (const Song&);

    };

#endif // SONG_H_INCLUDED
