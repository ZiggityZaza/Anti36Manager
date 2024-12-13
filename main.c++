// &&&&%%%%%%###%#(#%%&@@@@@@@@@@@@@@&&&%&@@@@&&%%%%&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// %%%%%%%  &  @  *   %     &%%&    &@  ,/  @  .  (      .  (  @    /,     @&&@@@@@
// &%#####(   (&  *   %  #  %#%@  * *@   .  #  &  .%(  &@.  .  @   .#,  .  @@@&@@@@
// @@@@@&(#  .%&  *   %  ##(/(#/  /  @  ,   #  &  .&(  &@.  (  @  .@&,  %  @&&@@@@@
// @@@@@@@&  ,#%.    (#  (#  ((   &  #  &   @     &%(  &@.  (  @    .,  %  @%%&@@@@
// &@@&&&&&&&&%%%#(/*******(*,*/(////((#####%%##%%&&&&&&@@@@@@@&&@@@%##&%%%&&&@@@@@
// &&&@@&&&%%#(/**,,,***,,*****/////(((#####%#%%&%%%%%%&&&&%%%###&@@@@&%&&&&@@@@@@@
// #####(((#((((/////////(((((((((((((((#%%##%%&&&%%%%%&&%%((&&##&&%%&&@&&&&@@@@@@@
// /////////****//((###(((((((/////////(((###%&&&&%%%#%%&%%&&##%#%%&&@@@@@@@@@@@@@@
// */(((/*,,,,*////**,,,,,..,,,,,,,,,*///((##%%%%%#%%%&&&&&&@%%%%##(#%&@@@@@@@@@@@@
// /####/**,,/**/,..,,,,,,,,,,,,,,,,,*///(((###%%###%&@@&&%%(###&&%%%&@@@@@@@@@@@@@
// (%##&#(#(,**,,,,,,,,,........,,,,,**,,*/(((###%%%%%#(#(#&&@@@&@@@@@@@@@@@@@@@@@@
// #%%(#&&##%&%####%%%%%%%&&&&&&&&&&&%%###(((###%%%%#%%###%##%@&%%&@@@@@@@@@@@@@@@@
// ////(#%%%&&&@@@@@@@@&&%#(/**,****/(##%%%%%%%%#####%%%#%&%@&%#%%&@@@@@@@@@@@@@@@@
// ,..,*/(/####%%&&%%######%%%%%####%%#(/***,,**/((#%%%%%%&%%((#(&@@@@@@@@@@@@@@@@@
// ....,,****/**,,,*(#######(((//**,,.,...,,,**/((##%%%%%&%((%#(&@@@@@@@@@@@@@@@@@@
// ..,,,,,*,,,,,,,,,,,,***,,,,,,,......,,,****//((#%%%%%###%((#&@@@@@@@@@@@@@@@@@@@
// ,.,,,****,,,,,....,....,****,,,,,,,,,*/*///((#%%#%#%(((((#&@@@@@&&&@&&@&@@@@@@@@
// ,,,,****,,,,,,,,,,,,,,,,,,,,,,,,,,,,**(((#%%%#((#%#%%%&&@@@@@@@@@@&&&@@@&@@@@@@@
// ,.,,*****,,,***,,,,,,,,,,,,,,,,*,*//((##%###(///(#%&@@@@@@@@@@@@@@&@&&&@@@&@@@@@
// ..,.,**,,,,,,***,,,,,,,,,,,,,,,**//((((((((//////(#%&@@@@@@@@@@@@&@&&&&@@@&&@@@@
// *,,,**/(%%#(((/,..,,,,,,,,,,,,,,*//((((/////(/(((((%&@@@@@@@@@@@@@@&@@@@&&&&&&&@
// &%%%%#(*,,,.................,,,,*///////******///((#&@@@@@@@@@@@@@@@&&&@&@@@@@&@
// (/((#(,...........,..,....,,,,,,*////*****/////(####&@@@@@@@@@@@@@@@@@@@@@@@@@@@
// *,,,*/**,,,,,,,.....,,,,,,,,,,,,*//////*///*//(#%##&@@@@@@@@@@@@@@@@@&&&@@@@@@@&
// /(##(///**///(#####////****,,,****//////***//(#%%%%&@@@@@@@@@@@@@@@@@@@&&&&@@&&&
// %%#######((((//*,,,,,....,,,,,***/////***//((#(/(##%@@@@@@@@@@@@@@@@@@@@&&&&&&&&
// (/*(#(*,,*(#/***(#(*,//*/(//(##(####///(#%&&#/*/###%@@@@@@@@@@@@@@@@@@@@@@@@@@@&
// *%  #  (. .,  #  %  &  .* *,  (#  .  *##/  %  &  /#%    @* .* .*  *  (  @  (  *@
// (%  #**(  .*  #  &  &     *,   #     &((*  #%%#  /#%  . %@.   @@    @(  @  #@@@@
// (&  &  *  .*  #  &  &  #  *,  &%  ,. *(**  %  &  (&*     *  #  /  (  (  @  #  ,@
// &%&/*&#%&&**%&%&/*(&###%##############*,,#**((/######%%##&@**#@@@**#@&##@@#**@&&
/*
Some syntax notes:
  New lines are used to separate different sections of the code
  - 4 new lines are used to separate sections like namespaces, classes, and others (include, define, etc.)
  - 3 new lines are used to separate fragments such as structs, functions/methods and containers
  - 2 new lines are used for different tasks inside the same fragment for example a part of code which is
      responsible reading a file and the other for printing out the content of that specific file
  - 1 new line is used for splitting different things inside the same task like one line for declaring a variable
      and the other for initializing it

  Tabs and spaces:
    - In each 2-liner section of code, putt a comment above to explain what the code does.
      - Feel free to use more

  Commenting:
    - To every block small black (1-2 newlines seprated from the next block with the same size), add a comment above, explaining what the block does
    - To every block larger block (3 and more newlines separated from the next block with the same size), add a comment below, explaining what the block does
    - Comments should be avoided and the code should be self-explanatory

  Performance and memory:
    - Use of the constexpr keyword is encouraged
    - Use of the stack memory is encouraged
    - Use only what you need. For example, if you need to calculate small numbers. no need to use size_t or int. Just use short or uint8_t
        - Unless the number is temporary

  Direct syntax:
    - The less the code, the better
      - but brackets need to be used for every if, else, for, while, etc. statement and fully extended.
 
    Syntax naming convention:
      - Classes, Enums, Structs: PascalCase
      - Functions: snake_case
      - Variables: camelCase
      - Constants: UPPER_CASE
      - Others: Crazy_Case


  Usages of features:
    - I discourage the use of the noexcept keyword due to readability and maintainability reasons.
    - Structs should be used as structs and not as classes
    - No settings default values for arguments in functions/methods
    - When getting the length of a string, I encourage you to use the length() method instead of size()
    - Encapsulation is overrated. My gut prefers to have everything public
    - Use "or" and "and" instead of "||" and "&&"
    - Creating a method instead of a static function is encouraged
    - Using std::endl is forbidden unless truly necessary

    Here are some banned random keywords:
      - const_case (breaks the very reason of using const. Really unsafe)
      - auto (because it's not clear what the type is)
        - Unless it's obvious and makes the code more readable
      - new / delete (memory leaks and encourages bad practices)
      - using namespace std; (polluting the global namespace)
      - goto (spaghetti code)
      - consteval (unpredictable behavior)
      - Union (unpredictable and unnecessary)
      - Noexcept (not worth gaining a few nanoseconds)
      - Inline (compiler is better at deciding what to inline)
      - No idea what it does:
        - volatile
        - mutable
        - extern
        - mutable
        - thread_local
        - alignas
        - alignof
        - decltype
        - typeid
*/


// Previous: https://patorjk.com/software/taag/#p=display&h=3&v=3&f=Small%20Keyboard&t=Anti36Manager%20v1.2
// https://patorjk.com/software/taag/#p=display&h=3&v=3&f=Slant&t=Anti36Manager%20v1.3
static constexpr const char* ASCII_ART = R"(
    ___          __  _ _____ _____ __  ___                                          _____ __
   /   |  ____  / /_(_|__  // ___//  |/  ____ _____  ____ _____ ____  _____   _   _<  / // /
  / /| | / __ \/ __/ / /_ </ __ \/ /|_/ / __ `/ __ \/ __ `/ __ `/ _ \/ ___/  | | / / / // /_
 / ___ |/ / / / /_/ /___/ / /_/ / /  / / /_/ / / / / /_/ / /_/ /  __/ /      | |/ / /__  __/
/_/  |_/_/ /_/\__/_//____/\____/_/  /_/\__,_/_/ /_/\__,_/\__, /\___/_/       |___/_(_)/_/   
                                                        /____/                              
)";
// Next: https://patorjk.com/software/taag/#p=display&h=3&v=3&f=Sweet&t=Anti36Manager%20v1.4
// Next: https://patorjk.com/software/taag/#p=display&h=3&v=3&f=NScript&t=Anti36Manager%20v1.4

#include <unordered_map> // Faster lookups
#include <filesystem> // Manipulating and reading files and folders in the Anti36Local folder
#include <algorithm> // Finding elements in a container
#include <iostream> // Printing out messages and std::string (and everything that comes with it)
#include <fstream> // Generating html file
#include <cstdint> // Cooler numbers
#include <chrono> // Calculate start-up time
#include <deque> // Containers with continuous memory addresses
#include <map> // Specifically for TAGS lookup



namespace joat { // Jack of all trades (Helper functions and classes)
    static constexpr uint8_t MAX_GENERAL_STRING_LENGTH = 50;
    static std::string shorten_str_if_necessary(const std::string &str) {
        if (str.length() > MAX_GENERAL_STRING_LENGTH) {
        return str.substr(0, MAX_GENERAL_STRING_LENGTH - 3) + "...";
        }
        return str;
    }


    static constexpr uint8_t MAX_CONSOLE_WIDTH = 120; // for 1080p screens
    static std::string form_2d_chart(std::deque<std::string> strings) {
    /*
      This function takes a deque of strings and forms a 2D chart out of them. The
      strings are resized to the longest string in the deque, put together, and a
      new line is added after a certain amount of characters.

      Note:
        - First string is always added
        - If the input is empty, an empty string is returned
    */

      std::size_t longestStringLenght = 0; 
      for (const std::string &string : strings) {
        longestStringLenght = std::max(longestStringLenght, string.length());
      }
      longestStringLenght++; // Add a space between the strings

      for (std::string &string : strings) {
        string.resize(longestStringLenght, ' ');
      }

      std::string result;
      std::size_t counter = 1; // Start at 1 because the first string is always added

      for (const std::string &string : strings) {
        result += string;
        if (counter < (MAX_CONSOLE_WIDTH / longestStringLenght)) {
          counter++;
        } else {
          counter = 1;
          result += '\n';
        }
      }

      return result;
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

        for (char c : str) {
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


  static std::string question() {
    std::string r;
    std::getline(std::cin, r);
    return r;
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


  class TimeStamp {
    // Specialized replacement for std::chrono::system_clock::time_point
    public:
      enum Weekday : char {
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
      static constexpr short NOT_SUPPORTED_CODE = -2;
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
        os << '-' << thisObject.hour << ':' << thisObject.minute << ':' << thisObject.second;
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
    public:
      enum Type : char {
        FILE = 'F',
        DICT = 'D'
      };

      std::string path;
      const Type type;
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
      const unsigned short depth() const { // 3
        return std::count(path.begin(), path.end(), '\\');
      }

      void move_to(const std::string &newPath) {
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
        std::deque<std::string> parts = joat::separate(path, '\\');
        if (index >= parts.size()) {
          throw std::out_of_range("Index out of range");
        }
        return parts[index];
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