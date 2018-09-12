// Copyright (c) 2018 by Tschokko.
// Author: tschokko

#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>

#include "parser.hpp"
#include "repair.hpp"

void usage() {
  std::cout << "movielist 0.1" << std::endl;
  std::cout << "The app parses the mediathek movie list file." << std::endl;
  std::cout << std::endl;
  std::cout << "USAGE" << std::endl;
  std::cout << "movielist [FILE]" << std::endl;
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  // Check if filename is passed as arg
  if (argc <= 1) {
    usage();
    return (EINVAL);
  }

  // std::cout << "Starting Movielist app..." << std::endl;

  std::string src_filename = argv[1];
  std::ifstream src{src_filename};
  std::stringstream dst{};

  repair_movie_list_json(src, dst);

  mediathek::parser::parse_movies(dst.str());

  return (0);
}
