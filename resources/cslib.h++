#ifndef LOCAL_SERVER_H
#define LOCAL_SERVER_H
#endif

#include <unordered_map> // Faster lookups
#include <filesystem> // Finding and moving files and folders in the Anti36Local folder
#include <algorithm> // Finding elements in a container
#include <iostream> // Printing out messages and std::string (and everything else that comes with it)
#include <fstream> // Logging
#include <cstdint> // Cooler numbers (small numbers supported by stl)
#include <chrono>
#include <deque> // Containers with continuous memory addresses

#include "httplib.h"
#include "json.hpp"



#pragma once
#if __cplusplus < 202002L
  #error This program requires C++20
#endif

#ifndef _WIN32
  #error This program is only for Windows
#endif



namespace cslib { // Jack of all trades (Helper functions and classes)

    static constexpr uint8_t MAX_GENERAL_STRING_LENGTH = 50;
    static std::string shorten_str_if_necessary_reverse(const std::string &str, uint8_t maxLength = MAX_GENERAL_STRING_LENGTH) {
        if (str.length() > maxLength) {
          return "..." + str.substr(str.length() - maxLength + 3); // +3 for the "..."
        }
        return str;
    }


    static std::string unescape_string(const std::string &escapedString) {

      std::string result;
      for (size_t i = 0; i < escapedString.length(); ++i) {
        if (escapedString[i] == '\\') {
          if (i + 1 < escapedString.length()) {
            switch (escapedString[i + 1]) {
              case 'n': result += '\n'; break;
              case 't': result += '\t'; break;
              case 'r': result += '\r'; break;
              case '0': result += '\0'; break;
              case '\\': result += '\\'; break;
              case '\'': result += '\''; break;
              case '\"': result += '\"'; break;
              default: result += escapedString[i + 1]; break;
            }
            ++i;
          }
        } else {
          result += escapedString[i];
        }
      }
      return result;
    }
    static std::string escape_string(const std::string &str) {
      std::string result;
      for (unsigned char c : str) {
        switch (c) {
          case '\n': result += "\\n"; break;
          case '\t': result += "\\t"; break;
          case '\r': result += "\\r"; break;
          case '\0': result += "\\0"; break;
          case '\\': result += "\\\\"; break;
          case '\'': result += "\\\'"; break;
          case '\"': result += "\\\""; break;
          default: result += c; break;
        }
      }
      return result;
    }


    static void crash(std::string errorMessage) {
      std::cerr << "Error: " << errorMessage << std::endl;
      std::exit(EXIT_FAILURE);
    }


    static std::deque<std::string> separate(const std::string &str, const char delimiter) {
      /*
        This function takes a string and a delimiter and splits the string into
        a deque of strings. The delimiter is used to split the string into different parts.

        Note:
          - The delimiter is not included in the result
          - If the string or delimiter is empty, an empty deque is returned
          - If between two delimiters is nothing, an empty string is added to the deque
          - If the string ends with a delimiter, an empty string is added to the deque
          - If delimiter is not found, the whole string is added to the deque
      */

        std::deque<std::string> result;
        std::string temp;

        if (str.empty() or delimiter == '\0') {
          return result;
        }

        for (unsigned char c : str) {
            if (c == delimiter) {
                result.push_back(temp);
                temp.clear();
            } else {
                temp += c;
            }
        }

        result.push_back(temp);

        return result;
    }


  static constexpr int STOI_EMPTY_CODE = -1; // Empty value for joat::stoi
  static constexpr int STOI_ERROR_CODE = -2; // Error value for joat::stoi
  static int stoi(const std::string &str) {
    if (str.empty()) {
      return STOI_EMPTY_CODE;
    }
    try {
      return std::stoi(str);
    } catch (...) {
      return STOI_ERROR_CODE;
    }
  }


  template <typename T>
  static bool does_this_exist_in_deque(const std::deque<T>& dequeInQuestion, const T& elementInQuestion) {
    return std::find(dequeInQuestion.begin(), dequeInQuestion.end(), elementInQuestion) != dequeInQuestion.end();
  }


  template <typename T>
  static bool do_these_deques_have_something_in_similar(const std::deque<T>& deque1, const std::deque<T>& deque2) {
    for (const T& element : deque1) {
      if (does_this_exist_in_deque(deque2, element)) {
        return true;
      }
    }
    return false;
  }


  class DualOutput {
    /*
      Everything that std::cout can but with the addition that
      the output is also being written to a file.
    */

    public:
    std::ofstream file;

    DualOutput(std::string fileName) {
      file.open(fileName);
    }
    ~DualOutput() {
      file.close();
    }

    template <typename T>
    DualOutput& operator<<(const T& output) {
      std::cout << output;
      file << output;
      file.flush();
      return *this;
    }

    template <typename T>
    DualOutput& operator<<(T&& output) {
      std::cout << output;
      file << output;
      file.flush();
      return *this;
    }
  };


  class TimeStamp {
    // Specialized replacement for std::chrono::system_clock::time_point
    public:
      enum Weekday : unsigned char {
        MONDAY = 'M',
        TUESDAY = 'U', // U for tUesday
        WEDNESDAY = 'W',
        THURSDAY = 'T',
        FRIDAY = 'F',
        SATURDAY = 'A', // A for sAturday
        SUNDAY = 'S',
        ERROR_DAY = 'E'
      };

      static constexpr short ERROR_CODE = -1;
      Weekday weekday = ERROR_DAY;
      short day = ERROR_CODE;
      short month = ERROR_CODE;
      short year = ERROR_CODE;
      short hour = ERROR_CODE;
      short minute = ERROR_CODE;
      short second = ERROR_CODE;

      void update() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        struct tm* timeinfo = std::localtime(&currentTime);

        switch (timeinfo->tm_wday) {
          case 0: weekday = SUNDAY; break;
          case 1: weekday = MONDAY; break;
          case 2: weekday = TUESDAY; break;
          case 3: weekday = WEDNESDAY; break;
          case 4: weekday = THURSDAY; break;
          case 5: weekday = FRIDAY; break;
          case 6: weekday = SATURDAY; break;
          default: weekday = ERROR_DAY; break;
        }
        day = timeinfo->tm_mday;
        month = timeinfo->tm_mon + 1;
        year = timeinfo->tm_year + 1900;
        hour = timeinfo->tm_hour;
        minute = timeinfo->tm_min;
        second = timeinfo->tm_sec;
      }

      friend std::ostream& operator<<(std::ostream& os, const TimeStamp& thisObject) {
        os << thisObject.day << '.' << thisObject.month << '.' << thisObject.year;
        os << " at ";
        if (thisObject.hour < 10) {os << '0';}
        os << thisObject.hour << ':';
        if (thisObject.minute < 10) {os << '0';}
        os << thisObject.minute;
        os << " (" << thisObject.weekday << ')';
        return os;
      }
      bool operator==(const TimeStamp &other) const {
        return day == other.day and
              month == other.month and
              year == other.year and
              hour == other.hour and
              minute == other.minute and
              second == other.second;
      }
      bool operator!=(const TimeStamp &other) const {
        return !(*this == other);
      }
      bool operator<(const TimeStamp &other) const {
        if (year < other.year) {return true;}
        if (year > other.year) {return false;}
        if (month < other.month) {return true;}
        if (month > other.month) {return false;}
        if (day < other.day) {return true;}
        if (day > other.day) {return false;}
        if (hour < other.hour) {return true;}
        if (hour > other.hour) {return false;}
        if (minute < other.minute) {return true;}
        if (minute > other.minute) {return false;}
        if (second < other.second) {return true;}
        return false;
      }
      bool operator>(const TimeStamp &other) const {
        return !(*this < other or *this == other);
      }
      bool operator<=(const TimeStamp &other) const {
        return *this < other or *this == other;
      }
      bool operator>=(const TimeStamp &other) const {
        return *this > other or *this == other;
      }

      uint64_t diff_in_s(const TimeStamp &other) const {
        if (*this < other) { // If this is smaller than other
          return ~((static_cast<uint64_t>(year - other.year) * 31536000) +
                  (static_cast<uint64_t>(month - other.month) * 2592000) +
                  (static_cast<uint64_t>(day - other.day) * 86400) +
                  (static_cast<uint64_t>(hour - other.hour) * 3600) +
                  (static_cast<uint64_t>(minute - other.minute) * 60) +
                  static_cast<uint64_t>(second - other.second));
        }
        return (static_cast<uint64_t>(year - other.year) * 31536000) +
               (static_cast<uint64_t>(month - other.month) * 2592000) +
               (static_cast<uint64_t>(day - other.day) * 86400) +
               (static_cast<uint64_t>(hour - other.hour) * 3600) +
               (static_cast<uint64_t>(minute - other.minute) * 60) +
               static_cast<uint64_t>(second - other.second);
      }

      static Weekday determine_day_of_weeky(const TimeStamp &atThisDate) {
        // Zeller's Congruence (chatgpt be my goat fr fr)
        short q = atThisDate.day; // Day of the month
        short m = atThisDate.month; // Month
        short K = atThisDate.year % 100; // Year of the century
        short J = atThisDate.year / 100; // Zero-based century
        if (m < 3) {
          m += 12;
          K--;
        }
        short h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
        switch (h) {
          case 0: return SATURDAY;
          case 1: return SUNDAY;
          case 2: return MONDAY;
          case 3: return TUESDAY;
          case 4: return WEDNESDAY;
          case 5: return THURSDAY;
          case 6: return FRIDAY;
          default: return ERROR_DAY;
        }
      }

      explicit TimeStamp() {update();};
      explicit TimeStamp(short day, short month, short year, short hour, short minute, short second) {
        this->day = day;
        this->month = month;
        this->year = year;
        this->hour = hour;
        this->minute = minute;
        this->second = second;
        weekday = determine_day_of_weeky(*this);
      }
  };


  class VirtualPath {
    // Specialized-lightweight replacement for std::filesystem::path
    // VirtualPath as in it's not a real path, but a representation of it
    public:
      enum Type : char {
        FILE = 'F',
        DICT = 'D'
      };

      std::string path;
      Type type; // Can't const because of std::sort... Sacrifices must be made...
      TimeStamp lastInteraction;

      explicit VirtualPath(const std::string &path) : path(path), type(std::filesystem::is_directory(path) ? DICT : FILE), lastInteraction(last_modified(path)) {
        while (this->path.back() == '\\') {
          this->path.pop_back();
        }
      }

      const std::string extension() const {
        if (type == DICT) {throw std::invalid_argument("Can't get extension of a directory");} // .txt
        return path.substr(path.find_last_of('.'));
      }
      const std::string filename() const {
        return path.substr(path.find_last_of('\\') + 1); // exmpl.txt
      }
      const std::string parent_path() const {
        return path.substr(0, path.find_last_of('\\')); // C:\Users\txts
      }
      const std::filesystem::path std_path() const {
        return std::filesystem::path(path); // C:\Users\txts\exmpl.txt
      }
      unsigned short depth() const { // 3 (0 -> C:\, 1 -> Users, 2 -> txts, 3 -> exmpl.txt)
        if (this->path.back() == '\\') {
          return std::count(path.begin(), path.end(), '\\') - 1;
        }
        return std::count(path.begin(), path.end(), '\\');
      }


      void move_to(const std::string &newPath) {
        // Deletes the old file and creates a new one with the same content
        std::filesystem::rename(std::filesystem::path(path), std::filesystem::path(newPath));
        this->path = newPath;
        this->lastInteraction = last_modified(path);
      }
      void pretend_to_move_to(const std::string &newPath) {
        this->path = newPath;
        this->lastInteraction = TimeStamp();
      }

      friend std::ostream& operator<<(std::ostream& os, const VirtualPath& thisObject) {
        os << thisObject.path;
        return os;
      }
      const std::string operator[](const uint8_t index) const {
        std::deque<std::string> parts = separate(path, '\\');
        if (index >= parts.size()) {
          throw std::out_of_range("Index out of range");
        }
        return parts[index];
      }
      bool operator==(const VirtualPath &other) const {
        return path == other.path;
      }
      bool operator!=(const VirtualPath &other) const {
        return path != other.path;
      }

      static size_t file_size(const std::string &filePath) {
        return std::filesystem::file_size(filePath);
      }
      static TimeStamp last_modified(const std::string &filePath) { // Special thanks to co-pilot
        std::filesystem::file_time_type ftime = std::filesystem::last_write_time(filePath);
        std::chrono::system_clock::time_point timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
        std::time_t cftime = std::chrono::system_clock::to_time_t(timePoint);
        struct tm* timeinfo = std::localtime(&cftime);
        return TimeStamp(timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
                         timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
      }
  };
};


