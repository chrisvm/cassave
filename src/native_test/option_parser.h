//
// Created by chrisvm on 04-24-16.
//

#ifndef CASSAVE_JS_OPTIONPARSER_H
#define CASSAVE_JS_OPTIONPARSER_H
#include <list>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
using namespace std;


class option_parser {
    bool verbose_, error_;
    char *script_path_;

public:
    option_parser(int argc, char *argv[]);
    void parse_options(int argc, char *argv[]);

    bool verbose();
    bool error();
    char* script();
};


#endif //CASSAVE_JS_OPTIONPARSER_H
