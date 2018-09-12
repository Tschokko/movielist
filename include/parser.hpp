// Copyright (c) 2018 by Tschokko.
// Author: tschokko

#ifndef _PARSER_HPP
#define _PARSER_HPP

#include <string>
#include <string_view>
#include <vector>

namespace mediathek {
namespace parser {

class movie_entry {
 public:
  movie_entry();
  explicit movie_entry(const std::vector<std::string> &v);

  std::string str() const;

 private:
  std::string channel_;
  std::string topic_;
  std::string title_;
  std::string date_;
  std::string time_;
  std::string duration_;
  std::string size_;
  std::string descr_;
  std::string url_;
  std::string website_url_;
  std::string sub_title_url_;
  std::string small_format_url_;
  std::string hd_format_url_;
  std::string unix_date_;
  std::string history_url_;
  std::string geo_;
  std::string is_new_;
};

void parse_movies(const std::string_view &data);

}  // namespace parser
}  // namespace mediathek

#endif  // _PARSER_HPP
