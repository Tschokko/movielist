// Copyright (c) 2018 by Tschokko.
// Author: tschokko

#include <iostream>
#include <sstream>
#include <string_view>

#include <nlohmann/json.hpp>

#include "parser.hpp"

namespace mediathek {
namespace parser {

using json = nlohmann::json;

enum {
  COL_CHANNEL = 0,
  COL_TOPIC = 1,
  COL_TITLE = 2,
  COL_DATE = 3,
  COL_TIME = 4,
  COL_DURATION = 5,
  COL_SIZE = 6,
  COL_DESCR = 7,
  COL_URL = 8,
  COL_WEBSITE_URL = 9,
  COL_SUB_TITLE_URL = 10,
  COL_SMALL_FORMAT_URL = 12,
  COL_HD_FORMAT_URL = 14,
  COL_UNIX_DATE = 16,
  COL_HISTORY_URL = 17,
  COL_GEO = 18,
  COL_IS_NEW = 19
};

movie_entry::movie_entry(const std::vector<std::string> &v) {
  for (std::size_t i = 0; i < v.size(); i++) {
    switch (i) {
      case COL_CHANNEL:
        channel_ = v[i];
        break;
      case COL_TOPIC:
        topic_ = v[i];
        break;
      case COL_TITLE:
        title_ = v[i];
        break;
      case COL_DATE:
        date_ = v[i];
        break;
      case COL_TIME:
        time_ = v[i];
        break;
      case COL_DURATION:
        duration_ = v[i];
        break;
      case COL_SIZE:
        size_ = v[i];
        break;
      case COL_DESCR:
        descr_ = v[i];
        break;
      case COL_URL:
        url_ = v[i];
        break;
      case COL_WEBSITE_URL:
        website_url_ = v[i];
        break;
      case COL_SUB_TITLE_URL:
        sub_title_url_ = v[i];
        break;
      case COL_SMALL_FORMAT_URL:
        small_format_url_ = v[i];
        break;
      case COL_HD_FORMAT_URL:
        hd_format_url_ = v[i];
        break;
      case COL_UNIX_DATE:
        unix_date_ = v[i];
        break;
      case COL_HISTORY_URL:
        history_url_ = v[i];
        break;
      case COL_GEO:
        geo_ = v[i];
        break;
      case COL_IS_NEW:
        is_new_ = v[i];
        break;
    }
  }
}

std::string movie_entry::str() const {
  std::stringstream s{};

  s << channel_ << ";";
  s << topic_ << ";";
  s << title_ << ";";
  s << date_ << ";";
  s << time_ << ";";
  s << duration_ << ";";
  s << size_ << ";";
  s << descr_ << ";";
  s << url_ << ";";
  s << website_url_ << ";";
  s << sub_title_url_ << ";";
  s << small_format_url_ << ";";
  s << hd_format_url_ << ";";
  s << unix_date_ << ";";
  s << history_url_ << ";";
  s << geo_ << ";";
  s << url_;

  return s.str();
}

void parse_movies(const std::string_view &data) {
  auto j = json::parse(data);

  // Get the movies key and check if it's an array!
  auto movies = j["movies"];
  std::vector<movie_entry> entries{};

  if (!movies.is_array()) {
    return;
  }

  for (json::iterator it = movies.begin(); it != movies.end(); ++it) {
    // The movie entry himself should also be an array!
    if ((*it).is_array()) {
      std::vector<std::string> vals = *it;
      entries.push_back(movie_entry{vals});
    }
  }

#ifdef DEBUG
  for (auto e : entries) std::cout << e.str() << std::endl;
#endif
}

}  // namespace parser

}  // namespace mediathek
