// 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <getopt.h>
#include <deque>

/*
enum class OutputMode {
    Verbose,
    Statistics,
    Median
};
*/

class Game {
private:
    //input handling vars
    int _argc;
    char ** _argv; 
    bool _verbose_flag; //temp
    bool _stats_flag; //temp
    bool _median_flag; //temp
    uint32_t _stats_arg;

    //OutputMode _output_mode; //to remove
    //TODO: Implement:
    //          1) Master zombie list!
    //          2) Active list! (Alive)
    //          3) Inactive List (Dead)
public:
    //constructor handles get_opt options in constructor/and-or function
    Game(int argc, char** argv);
        
    
    //TESTING FUNCTIONS START:=====================================================
    uint32_t getStatsArg() const;
    //TESTING FUNCTIONS END:=======================================================
};


#endif // GAME_H