//
// Created by chrisvm on 04-24-16.
//

#include "option_parser.h"

option_parser::option_parser(int argc, char *argv[]) {
    this->verbose_ = false;
    this->error_ = false;
    this->script_path_ = NULL;
    this->parse_options(argc, argv);
}

void option_parser::parse_options(int argc, char* argv[]) {
    opterr = 0;

    int c;
    while ((c = getopt(argc, argv, "v")) != -1)
        switch (c) {
            case 'v':
                this->verbose_ = true;
                break;

            case '?':
                if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                }
                this->error_ = true;
                return;
        }

    int index = optind;
    if (index >= argc) {
        fprintf(stderr, "script path not given");
        this->error_ = true;
    }

    // set script path
    this->script_path_ = argv[index++];

    // check if more given
    if (index != argc) {
        fprintf(stderr, "unknown args given");
        this->error_ = true;
    }
}

bool option_parser::error() { return this->error_; }
bool option_parser::verbose() { return this->verbose_; }