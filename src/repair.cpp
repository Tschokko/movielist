// Copyright (c) 2018 by Tschokko.
// Author: tschokko

#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

static int remove_curly_brackets(std::string* buf) {
  // Find first curly bracket and remove it
  std::size_t pos = buf->find("{");
  if (pos == std::string::npos) {
    std::cerr << "Invalid movie list" << std::endl;
    return (EINVAL);
  }
  buf->erase(pos, pos + 1);

  // Find last curly bracket and remove it
  pos = buf->rfind("}");
  if (pos == std::string::npos) {
    std::cerr << "Invalid movie list" << std::endl;
    return (EINVAL);
  }
  buf->erase(pos, pos + 1);

  return (0);
}

static inline std::string trim(const std::string& s) {
  auto wsfront = std::find_if_not(s.begin(), s.end(),
                                  [](int c) { return std::isspace(c); });
  auto wsback = std::find_if_not(s.rbegin(), s.rend(),
                                 [](int c) { return std::isspace(c); })
                    .base();
  return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

static void extract_movie_entries(const std::string& buf,
                                  std::vector<std::string>* entries) {
  // Extract all movie entries from buffer
  static std::string entry_key{"\"X\""};
  auto entry_pos = buf.find(entry_key);
  while (entry_pos != std::string::npos) {
    auto next_entry_pos = buf.find(entry_key, entry_pos + 1);

    auto raw_entry = buf.substr(entry_pos, next_entry_pos - entry_pos);
    if (raw_entry.size() < 3) {
      entry_pos = next_entry_pos;
      continue;
    }

    // Get rid of the key from entry and trim whitespaces
    raw_entry = trim(raw_entry.substr(3));

    // Check if entry starts with colon, remove and trim
    if (raw_entry.size() < 1 && raw_entry[0] != ':') {
      entry_pos = next_entry_pos;
      continue;
    }
    raw_entry = trim(raw_entry.substr(1));

    // Check if entry starts with squared bracket
    if (raw_entry.size() < 1 && raw_entry[0] != '[') {
      entry_pos = next_entry_pos;
      continue;
    }

    // Check if entry ends with comma and remove the comma
    if (raw_entry.size() >= 2 && raw_entry[raw_entry.size() - 1] == ',') {
      raw_entry = trim(raw_entry.substr(0, raw_entry.size() - 1));
    }

    // Check if entry ends with squared bracket
    if (raw_entry.size() < 2 && raw_entry[raw_entry.size() - 1] != ']') {
      entry_pos = next_entry_pos;
      continue;
    }

    // std::cout << "____ENTRY____(" << raw_entry << ")____" << std::endl;
    // std::cout << std::endl;

    entries->push_back(raw_entry);
    entry_pos = next_entry_pos;
  }
}

int repair_movie_list_json(std::istream& src, std::ostream& dst) {
  int err{0};

  // Read whole file into a string buffer
  src.seekg(0, std::ios::end);
  std::size_t buf_size = src.tellg();
  std::string buf(buf_size, ' ');
  src.seekg(0);
  src.read(&buf[0], buf_size);

  // Remove the curly brackets for better parsing
  if ((err = remove_curly_brackets(&buf)) != 0) {
    return (err);
  }

  // Extract all movie entries
  std::vector<std::string> entries;
  extract_movie_entries(buf, &entries);

  // Write the results
  dst << "{\"movies\":[";
  for (std::size_t i = 0; i < entries.size(); i++) {
    dst << entries[i];
    if ((i + 1) < entries.size()) dst << ",";
  }
  dst << "]}" << std::endl;

  return (0);
}
