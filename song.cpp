#include "song.h"

using namespace std;

int Song::COMPARE = Song::COMPARE_BY_RANKING;
const int Song::COMPARE_BY_AUTHOR;
const int Song::COMPARE_BY_INTERPRETER;
const int Song::COMPARE_BY_NAME;
const int Song::COMPARE_BY_RANKING;

Song::Song() { }

Song::Song(const Song& s) : name(s.name), author(s.author), interpreter(s.interpreter), ranking(s.ranking), sourceMP3(s.sourceMP3) { }

Song& Song::operator = (const Song& s) {
    name = s.name;
    interpreter = s.interpreter;
    author = s.author;
    ranking = s.ranking;
    sourceMP3 = s.sourceMP3;

    return *this;
    }

string Song::getName() const {
    return name;
    }

string Song::getAuthor() const {
    return author;
    }

string Song::getInterpreter() const {
    return interpreter;
    }

int Song::getRanking() const {
    return ranking;
    }

int Song::getCompare() {
    return COMPARE;
    }

string Song::getSourceMP3() const {
    return sourceMP3;
    }

string Song::toString() const {
    string str;
    str += name + " | ";
    str += author + " | ";
    str += interpreter + " | ";
    str += to_string(ranking) + " | ";
    str += sourceMP3;
    return str;
    }

void Song::setName(const std::string& n) {
    name = n;
    }

void Song::setAuthor(const std::string& a) {
    author = a;
    }

void Song::setInterpreter(const std::string& i) {
    interpreter = i;
    }

void Song::setRanking(const int& r) {
    ranking = r;
    }

void Song::setSourceMP3(const std::string& s) {
    sourceMP3 = s;
    }

void Song::setCompare(const int& i) {
    COMPARE = i;
    }

bool Song::operator == (const Song& s) const {
    switch ( COMPARE ) {
        case COMPARE_BY_AUTHOR: {
            return author == s.author;
            }
        break;
        case COMPARE_BY_INTERPRETER: {
            return interpreter == s.interpreter;
            }
        break;
        case COMPARE_BY_NAME: {
            return name == s.name;
            }
        break;
        case COMPARE_BY_RANKING: {
            return ranking == s.ranking;
            }
        break;
        }
    }

bool Song::operator != (const Song& s) const {
    return !(*this == s);
    }

bool Song::operator < (const Song& s) const {
    switch ( COMPARE ) {
        case COMPARE_BY_AUTHOR: {
            return author < s.author;
            }
        break;
        case COMPARE_BY_INTERPRETER: {
            return interpreter < s.interpreter;
            }
        break;
        case COMPARE_BY_NAME: {
            return name < s.name;
            }
        break;
        case COMPARE_BY_RANKING: {
            return ranking < s.ranking;
            }
        break;
        }
    }

bool Song::operator <= (const Song& s) const {
    return ( *this < s ) || ( *this == s);
    }

bool Song::operator > (const Song& s) const {
    return !(*this < s) && (*this != s);
    }

bool Song::operator >= (const Song& s) const {
    return !(*this < s) || (*this == s);
    }
