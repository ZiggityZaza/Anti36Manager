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

#if __cplusplus < 202002L
  #error This program requires C++20
#endif

#ifndef _WIN32
  #error This program is only for Windows
#endif



namespace joat { // Jack of all trades (Helper functions and classes)
    static double image_similarity(const std::string &image1, const std::string &image2) {
      /*
        This function takes two images and calculates the similarity between them.
        The similarity is calculated by comparing the pixels of the images.

        Note:
          - If the images are the same, the result is 1.0
          - If the images are completely different, the result is 0.0
          - If the images are similar, the result is between 0.0 and 1.0
      */

      // Placeholder
      return 0.0;
    }


    static bool cmd(const std::string &command) {
      /*
        This function takes a command and executes it in the command prompt.
        The function returns true if the command was executed successfully and false otherwise.
      */

      // Placeholder
      system(command.c_str());
      return false;
    }


    static constexpr uint8_t MAX_GENERAL_STRING_LENGTH = 50;
    static std::string shorten_str_if_necessary(const std::string &str, uint8_t maxLength = MAX_GENERAL_STRING_LENGTH) {
        if (str.length() > maxLength) {
          return str.substr(0, maxLength - 3) + "...";
        }
        return str;
    }
    static std::string shorten_str_if_necessary_reverse(const std::string &str, uint8_t maxLength = MAX_GENERAL_STRING_LENGTH) {
        if (str.length() > maxLength) {
          return "..." + str.substr(str.length() - maxLength + 3); // +3 for the "..."
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
      ++longestStringLenght; // Add a space between the strings

      for (std::string &string : strings) {
        string.resize(longestStringLenght, ' ');
      }

      std::string result;
      std::size_t counter = 1; // Start at 1 because the first string is always added

      for (const std::string &string : strings) {
        result += string;
        if (counter < (MAX_CONSOLE_WIDTH / longestStringLenght)) {
          ++counter; // Hehe c++
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
        os << " at " << thisObject.hour << ':' << thisObject.minute << ':' << thisObject.second;
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
      const unsigned short depth() const { // 3
        if (this->path.back() == '\\') {
          return std::count(path.begin(), path.end(), '\\') - 1;
        }
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
      bool operator==(const VirtualPath &other) const {
        return path == other.path;
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




namespace Anti36Manager {
  // This namespace contains all the necessary classes, variables and whatnot for the A36M

  // Console styling
  static constexpr const char* HEAD = "\n >> "; // Line
  static constexpr const char* WHEAD = " >> "; // Line
  static constexpr const char* LINE = "---------------------------------------------------------------------------------------------------";
  static constexpr const char* NEXT = "\n\n >> "; // Next section
  static constexpr const char* SUBLINE = "\n  > "; // Subsection
  static constexpr const char* WSUBLINE = "  > "; // Subsection without creating a new line
  static constexpr const char* SUBSUBLINE = "\n   > "; // Subsubsection
  static constexpr const char* WSUBSUBLINE = "   > "; // Subsubsection without creating a new line
  static constexpr const char* CRAZYSUBLINE = "\n    > "; // Subsubsubsection
  static constexpr const char* WCRAZYSUBLINE = "    > "; // Subsubsubsection without creating a new line
  static constexpr const char* TURBOCRAZYSUBLINE = "\n     > "; // Subsubsubsubsection
  static constexpr const char* WTURBOCRAZYSUBLINE = "     > "; // Subsubsubsubsection without creating a new line

  // Default values and Configs
  std::ostream& console = std::cout;
  using index_t = unsigned short;
  static constexpr bool DEBUGGING = true;
  static constexpr char WELCOME_SCREEN_SORTING_OPTION = '0';
  static constexpr char WELCOME_SCREEN_VIEWING_OPTION = '1';
  static constexpr char WELCOME_SCREEN_SUMMARY_OPTION = '2';
  static constexpr char WELCOME_SCREEN_ERROR_OPTION = -1;

  enum MediaType : char {
    IMAGE = 'I',
    VIDEO = 'V',
    NONE = 'N',
    BOTH = 'B'
  };


  // Portrayal structs & classes
  struct Origin {
    const std::string name;
    const joat::VirtualPath *const where;
  };
  struct Persona {
    const Origin *const origin;
    const std::string name;
    const joat::VirtualPath *const where;
  };
  struct Portrayal {
    index_t index; // Can change incase of index gap fixing
    const Persona *const persona;
    const std::deque<char> tags;
    joat::VirtualPath *const where;
  };


  // Constants
  static constexpr const char* ANTI36_FOLDER = "E:\\Anti36Local";
  static constexpr const char* UNSORTED_FOLDER_PATH = "E:\\$unsorted";
  static constexpr const index_t INDEX_ERROR_VALUE = ~index_t(0); // Error value for index_t (largest possible value)


  // Template for portrayal HTML
  static constexpr const char* HTML_HEADER[3] = {
    "<h2 style=\"color: white\">Found ", /* AMOUNT_OF_PORTAYALS_FOUND */ " portrayals for [", /* FILTERS */ "]. Enjoy!</h2> <body style=\"background-color:#330000;\">\n"};
  static constexpr const char* HTML_VIDEO[2] = {"<video src=\"", /* FULL_FILE_PATH */ "\" controls width=\"300\"></video>\n"};
  static constexpr const char* HTML_IMAGE[2] = {"<img src=\"", /* FULL_FILE_PATH */ "\" controls width=\"300\">\n"};
  static constexpr const char* HTML_OUTPUT_FILE = "E:\\output.html";


  // Look ups
  static const std::unordered_map<std::string_view, MediaType> EXTENSION_TO_MEDIA = {
    {".mp4", VIDEO},
    {".webm", VIDEO},
    {".mkv", VIDEO},
    {".avi", VIDEO},
    {".jpg", IMAGE},
    {".jpeg", IMAGE},
    {".png", IMAGE},
    {".gif", IMAGE},
    {".bmp", IMAGE},
    {".webp", IMAGE}
  };
  static const std::map<char, std::string_view> TAGS_LOOKUP = {
    {'A', "_A"},
    {'B', "_B"},
    {'C', "_C"},
    {'D', "_D"},
    {'E', "_E"},
    {'F', "_F"},
    {'G', "_G"},
    {'H', "_H"},
    {'I', "_I"},
    {'J', "_J"},
    {'K', "_K"},
    {'L', "_L"},
    {'M', "_M"},
    {'N', "_N"},
    {'O', "_O"},
    {'P', "_P"},
    {'Q', "_Q"},
    {'R', "_R"},
    {'S', "_S"},
    {'T', "_T"},
    {'U', "_U"},
    {'V', "_V"},
    {'W', "_W"},
    {'X', "_X"},
    {'Y', "_Y"},
    {'Z', "_Z"},
    {'a', "_a"},
    {'b', "_b"},
    {'c', "_c"},
    {'d', "_d"},
    {'e', "_e"},
    {'f', "_f"},
    {'g', "_g"},
    {'h', "_h"},
    {'i', "_i"},
    {'j', "_j"},
    {'k', "_k"},
    {'l', "_l"},
    {'m', "_m"},
    {'n', "_n"},
    {'o', "_o"},
    {'p', "_p"},
    {'q', "_q"},
    {'r', "_r"},
    {'s', "_s"},
    {'t', "_t"},
    {'u', "_u"},
    {'v', "_v"},
    {'w', "_w"},
    {'x', "_x"},
    {'y', "_y"},
    {'z', "_z"},
    {'0', "zero"},
    {'1', "one"},
    {'2', "two"},
    {'3', "three"},
    {'4', "four"},
    {'5', "five"},
    {'6', "six"},
    {'7', "seven"},
    {'8', "eight"},
    {'9', "nine"}
  };





  class Main {
    /*
      The difference between the namespace and the class is that the class
      is specifically for mutable variables and methods.
    */


    // Pillar containers
    std::deque<joat::VirtualPath> folders;
    std::deque<joat::VirtualPath> files;
    std::deque<Origin> origins;
    std::deque<Persona> personas;
    std::deque<Portrayal> portrayals;

    // Containers for easy access
    std::unordered_map<Origin*, std::deque<Portrayal*>> portrayalsByOrigin;
    std::unordered_map<Origin*, std::deque<Persona*>> personasByOrigin;
    std::unordered_map<Persona*, std::deque<Portrayal*>> portrayalsByPersona;
    std::unordered_map<char, std::deque<Portrayal*>> portrayalsByTag;
    std::unordered_map<MediaType, std::deque<Portrayal*>> portrayalsByType;

    // Filters
    std::deque<char> byTagsFilter;
    std::unordered_map<Origin*, std::deque<Persona*>> byOriginsFilter;
    MediaType byTypeFilter = BOTH;

    // Other variables
    Persona* currentPersona = nullptr;
    std::deque<joat::VirtualPath> unsortedPortrayalsPaths;
    struct aboutToBeSortedPortrayal {
      joat::VirtualPath* currentPath;
      std::deque<char> assignedTags;
    };
    std::deque<aboutToBeSortedPortrayal> aboutToBeSortedPortrayalsQueue; // Enables skipping/undoing/redoing specific unsorted portrayals
    std::deque<Portrayal*> collection;


    // Helper methods (usually silent methods)
    std::string get_tag_chart(const bool showAmountOfPortrayals) {

      // Define variables
      std::deque<std::string> containerForChart;
      std::string result = "Available tags";
      if (showAmountOfPortrayals) {
        result += " with each's amount of portrayals";
      }
      result += ':';
      result += '\n';
      result += LINE;
      result += '\n';


      // Fill chart
      for (const auto& [tag, itsMeaning] : TAGS_LOOKUP) {
        std::string chartString;
        chartString += tag;
        chartString += " - ";
        chartString += itsMeaning;
        if (showAmountOfPortrayals) {
          chartString += " (";
          chartString += std::to_string(portrayalsByTag[tag].size());
          chartString += ')';
        }
        containerForChart.push_back(chartString);
      }


      // Add to result
      result += joat::form_2d_chart(containerForChart);
      return result;
    }
    std::string get_origin_chart(bool showAmountOfPortrayals, bool showAmountOfPersonas) {

      // Define variables
      std::deque<std::string> containerForChart;
      std::string result = "Available origins";
      if (showAmountOfPersonas or showAmountOfPortrayals) {
        result += " (";
        if (showAmountOfPersonas and showAmountOfPortrayals) {
          result += "with each's amount of personas and the personas' amount of portrayals";
        } else if (showAmountOfPersonas) {
          result += "with each's amount of personas";
        } else if (showAmountOfPortrayals) {
          result += "with each's amount of portrayals";
        }
        result += ')';
      }
      result += ':';
      result += '\n';
      result += LINE;
      result += '\n';


      // Fill chart
      for (Origin& origin : origins) {
        std::string chartString;
        chartString += origin.name;
        if (showAmountOfPersonas or showAmountOfPortrayals) {
          chartString += " (";

          if (showAmountOfPersonas) {
            if (showAmountOfPortrayals) {
              chartString += "Per. ";
            }
            chartString += std::to_string(personasByOrigin[&origin].size());
            if (showAmountOfPortrayals) {
              chartString += ", ";
            }
          }

          if (showAmountOfPortrayals) {
            if (showAmountOfPersonas) {
              chartString += "Por. ";
            }
            chartString += std::to_string(portrayalsByOrigin[&origin].size());
          }

          chartString += ')';
        }
        containerForChart.push_back(chartString);
      }

      // Add to result
      result += joat::form_2d_chart(containerForChart);
      return result;
    }
    std::string get_persona_chart(const Origin *const desecendingOrigin, bool showAmountOfPortrayals) {

      // Define variables
      std::deque<std::string> containerForChart;
      std::string result;
      if (!desecendingOrigin) {
        result += "All a";
      } else {
        result += 'A';
      }
      result += "vailable personas";
      if (desecendingOrigin) {
        result += " for \"";
        result += desecendingOrigin->name;
        result += '"';
      }
      if (showAmountOfPortrayals) {
        result += " with each's amount of portrayals";
      }
      result += ':';
      result += '\n';
      result += LINE;
      result += '\n';


      // Fill chart
      for (Persona& persona : personas) {
        if (desecendingOrigin and persona.origin != desecendingOrigin) {
          continue;
        }
        std::string chartString;
        chartString += persona.name;
        if (showAmountOfPortrayals) {
          chartString += " (";
          chartString += std::to_string(portrayalsByPersona[&persona].size());
          chartString += ')';
        }
        containerForChart.push_back(chartString);
      }


      // Add to result
      result += joat::form_2d_chart(containerForChart);
      return result;
    }



    Origin ORIGIN_ERROR_TYPE = {"[ORIGIN_ERROR_TYPE]", nullptr};
    Origin* origin_exists(const std::string& originName) {
      for (Origin& origin : origins) {
        if (origin.name == originName) {
          return &origin;
        }
      }
      return &ORIGIN_ERROR_TYPE;
    }
    Persona PERSONA_ERROR_TYPE = {&ORIGIN_ERROR_TYPE, "[PERSONA_ERROR_TYPE]", nullptr};
    Persona* persona_exists(const std::string& personaName, const Origin *const desecendingOrigin) {
      for (Persona& persona : personas) {
        if (persona.name == personaName and (!desecendingOrigin or persona.origin == desecendingOrigin)) {
          return &persona;
        }
      }
      return &PERSONA_ERROR_TYPE;
    }



    bool tag_exists(const std::string_view tag) {
      for (const auto& [tagChar, tagMeaning] : TAGS_LOOKUP) {
        if (TAGS_LOOKUP.at(tagChar) == tag) {
          return true;
        }
      }
      return false;
    }
    bool tag_exists(const char tag) {
      return TAGS_LOOKUP.find(tag) != TAGS_LOOKUP.end();
    }



    void change_portrayal_index(Portrayal *const portrayalInQuestion, index_t newIndex) {
      /*
        Changes the index attribute of the portrayalInQuestion object to newIndex and
        moves the file to the new path. The new path is determined by the origin name,
        the persona name, the new index, and the tags of the portrayalInQuestion object.
      */

      portrayalInQuestion->index = newIndex;

      std::string newPath = ANTI36_FOLDER;
      newPath += '\\';
      newPath += portrayalInQuestion->persona->origin->name;
      newPath += '\\';
      newPath += portrayalInQuestion->persona->name;
      newPath += '\\';
      newPath += std::to_string(newIndex);
      newPath += '_';
      for (char tag : portrayalInQuestion->tags) {
        newPath += tag;
      }
      newPath += '_';
      newPath += portrayalInQuestion->where->extension();

      if (!DEBUGGING) {
        portrayalInQuestion->where->move_to(newPath);
      } else {
        portrayalInQuestion->where->pretend_to_move_to(newPath);
      }
    }



    void summarize() {
      /*
        This function summarizes the data in the portrayals deque
        and prints it to the console.
      */

      console << "This is what we have so far:";

      // Pillar containers
      console << SUBLINE << folders.size() << " folders:";
      for (const joat::VirtualPath& folder : folders) {
        console << SUBSUBLINE << folder << " @ " << folder.lastInteraction;
      }
      console << SUBLINE << files.size() << " files:";
      for (const joat::VirtualPath& file : files) {
        console << SUBSUBLINE << file << " @ " << file.lastInteraction;
      }
      console << SUBLINE << origins.size() << " origins with " << personas.size() << " personas:";
      // Go through every origin
      for (Origin& origin : origins) {
        console << SUBSUBLINE << origin.name << " with " << personasByOrigin[&origin].size() << " personas:";
        // Go through every persona
        for (Persona* persona : personasByOrigin[&origin]) {
          console << CRAZYSUBLINE << persona->name << " with " << portrayalsByPersona[persona].size() << " portrayals:";
          // Finally, print the portrayals
          for (Portrayal* portrayal : portrayalsByPersona[persona]) {
            console << TURBOCRAZYSUBLINE << portrayal->where->filename();
          }
        }
      }
      console << '\n';

      // Filter containers
      console << SUBLINE << "Filters (should be empty):";
      console << SUBSUBLINE << "Tags with " << byTagsFilter.size() << " tags:";
      console << SUBSUBLINE << "Origins with " << byOriginsFilter.size() << " origins:";
      console << SUBSUBLINE << "Type: " << byTypeFilter;
      console << '\n';

      // Other containers
      console << SUBLINE << "Current persona: ";
      if (currentPersona) {
        console << currentPersona->name << " from " << currentPersona->origin->name;
      } else {
        console << "none";
      }
      console << SUBLINE << "Unsorted portrayals: ";
      for (const joat::VirtualPath& unsortedPortrayal : unsortedPortrayalsPaths) {
        console << SUBSUBLINE << joat::shorten_str_if_necessary_reverse(unsortedPortrayal.path);
      }
      console << '\n';
    }



    // Setup methods
    void read_ANTI36_FOLDER() {
      /*
        This function goes through every file and folder
        in the Anti36Local folder to add them to the folders and files deque.
      */

      console << "Reading content of " << ANTI36_FOLDER;

      for (const std::filesystem::directory_entry& fileEntry : std::filesystem::recursive_directory_iterator(ANTI36_FOLDER)) {

        joat::VirtualPath entry(fileEntry.path().string());

        console << SUBLINE << entry << " is ";

        if (entry.type == joat::VirtualPath::DICT) {
          folders.push_back(entry);
          console << "a folder";
        }

        else {
          files.push_back(entry);
          console << "a file";
        }

        console << " @ " << entry.lastInteraction;
      }

      console << SUBLINE << "Found " << folders.size() << " folders and " << files.size() << " files.";
    }
    void read_UNSORTED_FOLDER() {
      /*
        This function goes through every file in the $unsorted folder
        to add them to the unsortedPortrayals deque.

        Additionally, it rearranges the unsortedPortrayals deque by last interaction.
        in ascending order. (The oldest file is the first one)
      */

      console << "Reading unsorted files in " << UNSORTED_FOLDER_PATH;

      for (const std::filesystem::directory_entry& fileEntry : std::filesystem::recursive_directory_iterator(UNSORTED_FOLDER_PATH)) {

        joat::VirtualPath entry(fileEntry.path().string());

        console << SUBLINE << joat::shorten_str_if_necessary_reverse(entry.path) << " @ " << entry.lastInteraction;

        if (entry.type == joat::VirtualPath::FILE) {
          unsortedPortrayalsPaths.push_back(entry);
        }
      }


      // rearrange the files by last interaction
      std::sort(unsortedPortrayalsPaths.begin(), unsortedPortrayalsPaths.end(),
        // If a is older (smaller) than b, a comes first
        [](const joat::VirtualPath& a, const joat::VirtualPath& b) {
          return a.lastInteraction < b.lastInteraction;
        }
      );

      console << SUBLINE << "Found and rearranged " << unsortedPortrayalsPaths.size() << " files.";
    }



    void check_folders() {
      /*
        This function iterates though the folders deque and check if they
        comply with the naming convention. If they do, just ignore them.

        Rules:
          - No subfolders are allowed

        No changes are made here. The folders are just checked.
      */

      console << "Checking folders for compliance with the naming convention";

      for (const joat::VirtualPath& folder : folders) {
        console << SUBLINE << folder;

        if (folder.depth() > 4) {
          throw std::runtime_error("The folder \"" + folder.path + "\" doesn't comply with the naming convention. Subfolders are not allowed.");
        }
      }
    }



    void check_files() {
      /*
        This function iterates though the files deque and check if they
        comply with the naming convention. If they do, just ignore them.

        Rules (within this function):
          - The file should be in a persona folder
          - The file should have a supported extension
          - The file should have the correct naming convention
            - The index should be a number between 1 and the second largest number of index_t
            - The tags should be valid and unique
              - If the tag is 0, throw an exception

        No changes are made here. The files are just checked.
      */


      console << "Checking files for compliance with the naming convention";


      for (const joat::VirtualPath& file : files) {

        console << SUBLINE << file;


        if (file.depth() != 4) {
          throw std::runtime_error("The file \"" + file.path + "\" is trailing.");
        }


        if (EXTENSION_TO_MEDIA.find(file.extension()) == EXTENSION_TO_MEDIA.end()) {
          throw std::runtime_error("The extension \"" + file.extension() + "\" of the file \"" + file.path + "\" is not supported.");
        }


        // Split the filename into parts: index, tags, extension
        std::deque<std::string> splitFilename = joat::separate(file.filename(), '_');


        if (splitFilename.size() != 3) {
          throw std::runtime_error("The file \"" + file.path + "\" doesn't comply with the naming convention.");
        }


        // Translate index
        int translatingIndex = joat::stoi(splitFilename[0]);
        if (translatingIndex == joat::STOI_ERROR_CODE) {
          throw std::runtime_error("The index \"" + splitFilename[0] + "\" of the file \"" + file.path + "\" is not a number.");
        }

        else if (translatingIndex >= INDEX_ERROR_VALUE) {
          throw std::runtime_error("The index \"" + splitFilename[0] + "\" of the file \"" + file.path + "\" is too large.");
        }

        else if (translatingIndex <= 0) {
          throw std::runtime_error("The index \"" + splitFilename[0] + "\" of the file \"" + file.path + "\" is too small.");
        }


        // Validate tags
        std::deque<char> alreadyOccuredTags;
        for (char tag : splitFilename[1]) {

          if (!tag_exists(tag)) {
            throw std::runtime_error("The tag \"" + std::to_string(tag) + "\" of the file \"" + file.path + "\" doesn't exist.");
          }

          if (joat::does_this_exist_in_deque(alreadyOccuredTags, tag)) {
            throw std::runtime_error("The tag \"" + std::to_string(tag) + "\" of the file \"" + file.path + "\" has already occured.");
          }

          alreadyOccuredTags.push_back(tag);
        }
        if (alreadyOccuredTags.empty()) {
          throw std::runtime_error("The file \"" + file.path + "\" doesn't have any tags.");
        }
      }
    }



    void catagorize_A36L_folders() {
      /*
        This function goes through the folders deque and categorizes them to origins and personas.

        Since std::filesystem::recursive_directory_iterator() goes through the folders in a
        alphabetical surface-first order, we can be sure that the origins are always before the
        personas which means we can safely assign the personas to the last origin.
      */

      console << "Categorizing folders to origins and personas";

      for (joat::VirtualPath& folder : folders) {
        switch (folder.depth()) {
          case 2: {
            origins.push_back({folder[2], &folder});
            console << SUBLINE << "Adding origin \"" << origins.back().name << '"';
            break;
          }

          case 3: {
            personas.push_back({&origins.back(), folder[3], &folder}); // This is the place where I learned that std::vectors are not safe
            console << SUBSUBLINE << "with \"" << personas.back().name << '"';
            break;
          }
        }
      }

      console << SUBLINE << "Catagorized " << origins.size() << " origins and " << personas.size() << " personas";
    }



    void catagorize_files() {
      /*
        Just like the folders, we need to split the path into parts to categorize
        them into portrayals. The portrayals are then added to the portrayals deque.
      */

      console << "Categorizing files to portrayals.";

      for (joat::VirtualPath& file : files) {
        
        console << SUBLINE << "Categorizing file " << file;


        // Split the path into parts: E:, Anti36Local, origin, persona and filename (index_tags_.extension)
        std::deque<std::string> splitFilename = joat::separate(file.filename(), '_');


        index_t index = joat::stoi(splitFilename[0]);
        console << SUBSUBLINE << "At index " << index;


        Persona* rPersona = persona_exists(file[3], origin_exists(file[2]));
        console << SUBSUBLINE << "Persona \"" << rPersona->name << "\" from \"" << rPersona->origin->name << '"';


        std::deque<char> rTags;
        for (char tag : splitFilename[1]) {
          rTags.push_back(tag);
          console << SUBSUBLINE << "Tag \"" << TAGS_LOOKUP.at(tag) << '"';
        }


        console << SUBSUBLINE << "Path: " << file;
        console << SUBSUBLINE << "Extension: " << file.extension() << " which is an " << (EXTENSION_TO_MEDIA.at(file.extension()) == IMAGE ? "image" : "video"); 


        portrayals.push_back({index, rPersona, rTags, &file});
      }

      console << SUBLINE << "Catagorized " << portrayals.size() << " portrayals";
    }



    void sort_byXY_containers() {
      /*
        This function creates key-value pairs for the following maps so easier
        access to the portrayals can be achieved.
      */


      console << "Sorting portrayals";


      console << SUBLINE << "Resetting the byXYContainers";
      portrayalsByOrigin.clear();
      portrayalsByPersona.clear();
      portrayalsByTag.clear();
      portrayalsByType.clear();
      personasByOrigin.clear();


      console << SUBLINE << "Configuring portrayals by persona";
      for (Persona& persona : personas) {
        portrayalsByPersona[&persona] = {};
      }
      console << " (" << portrayalsByPersona.size() << " personas)";


      console << SUBLINE << "Configuring portrayals by origin";
      for (Origin& origin : origins) {
        portrayalsByOrigin[&origin] = {};
      }
      console << " (" << portrayalsByOrigin.size() << " origins)";


      console << SUBLINE << "Configuring personas by origin";
      for (Origin& origin : origins) {
        personasByOrigin[&origin] = {};
        for (Persona& persona : personas) {
          if (persona.origin == &origin) {
            personasByOrigin[&origin].push_back(&persona);
          }
        }
      }
      console << " (" << personasByOrigin.size() << " origins)";


      console << SUBLINE << "Configuring portrayals by tag";
      for (const auto& [tag, itsMeaning] : TAGS_LOOKUP) {
        portrayalsByTag[tag] = {};
      }
      console << " (" << portrayalsByTag.size() << " tags)";


      console << SUBLINE << "Configuring portrayals by type";
      portrayalsByType[IMAGE] = {};
      portrayalsByType[VIDEO] = {};
      console << " (" << portrayalsByType.size() << " types)";


      console << SUBLINE << "Adding portrayals to the maps";
      for (Portrayal& portrayal : portrayals) {
        portrayalsByOrigin[origin_exists(portrayal.persona->origin->name)].push_back(&portrayal);
        portrayalsByPersona[persona_exists(portrayal.persona->name, portrayal.persona->origin)].push_back(&portrayal);
        for (char tag : portrayal.tags) {
          portrayalsByTag[tag].push_back(&portrayal);
        }
        portrayalsByType[EXTENSION_TO_MEDIA.at(portrayal.where->extension())].push_back(&portrayal);
      }
    }



    void full_duplicate_index_fix() {
      /*
        This function goes through all the personas and their portrayals
        to check if any of them have the same index. If there is, the portrayal
        will be moved to the next open index.

        This can do some index gaps filling as well.
      */

      console << "Checking for duplicate indexes";


      for (const auto& [iteratedPersona, itsPortrayals] : portrayalsByPersona) {

        if (itsPortrayals.empty()) {
          continue;
        }


        console << SUBLINE << "Checking \"" << iteratedPersona->name << "\" - \"" << iteratedPersona->origin->name << "\" (" << itsPortrayals.size() << " portrayals)";


        std::deque<index_t> alreadyOccuredIndex;
        for (Portrayal* portrayal : itsPortrayals) {

          if (joat::does_this_exist_in_deque(alreadyOccuredIndex, portrayal->index)) {

            index_t nextAvailableIndex = 1;
            while (joat::does_this_exist_in_deque(alreadyOccuredIndex, nextAvailableIndex)) {
              ++nextAvailableIndex;
            }

            console << SUBSUBLINE << "Changing index of " << portrayal->where->filename() << " from " << portrayal->index << " to " << nextAvailableIndex;
            change_portrayal_index(portrayal, nextAvailableIndex);
          }


          // Continue
          else {
            alreadyOccuredIndex.push_back(portrayal->index);
          }
        }
      }
    }



    void full_index_gaps_fix() {
      /*
        This method's purpose is to find gaps in the indexes of the portrayals
        and fill them by renaming the last portrayal in the persona folder to
        the next available index.

        It's highly required every index to be unique since one an index gap
        is fixed which had a duplicate index, the gap will remain open since
        the duplicate still occupies the other end of the gap.

        Example:
          - 1.jpg
          - 2.jpg
          - 4.jpg
          - 5.jpg
          - 6.jpg
          - 8.jpg
          - 9.jpg

        The portrayal 9.jpg will be renamed to 3.jpg and the portrayal 8.jpg
        will be renamed to 7.jpg.
      */


      console << "Index management fix";


      // Iterate through every persona
      for (const auto& [iteratedPersona, itsPortrayals] : portrayalsByPersona) {

        // Skip empty personas
        if (itsPortrayals.empty()) {
          continue;
        }


        console << SUBLINE << "Checking \"" << iteratedPersona->name << "\" - \"" << iteratedPersona->origin->name << "\" (" << itsPortrayals.size() << " portrayals)";


        // Sort and define variables
        std::deque<Portrayal*> sortedByIndexPortrayals = itsPortrayals;
        struct SortByIndex {
          bool operator()(Portrayal* a, Portrayal* b) const {
            return a->index < b->index;
          }
        };
        std::sort(sortedByIndexPortrayals.begin(), sortedByIndexPortrayals.end(), SortByIndex());


        // Print index gap ranges
        index_t nextExpectedIndex = 1;
        for (Portrayal* portrayal : sortedByIndexPortrayals) {

          // Check if the next expected index is the same as the current index
          if (portrayal->index != nextExpectedIndex) {
            console << SUBSUBLINE << "Gap between " << nextExpectedIndex << " and " << portrayal->index;
          }

          // Continue
          ++nextExpectedIndex;
        }


        // Iterate through every portrayal
        index_t nextExceptedIndex = 1;
        while (nextExceptedIndex <= itsPortrayals.size()) {

          // Check if the next expected index is the same as the current index
          if (sortedByIndexPortrayals[nextExceptedIndex - 1]->index != nextExceptedIndex) {

            // Take the last portrayal and change it's index
            console << SUBSUBLINE << "Changing index of " << sortedByIndexPortrayals.back()->where->filename() << " from " << sortedByIndexPortrayals.back()->index << " to " << nextExceptedIndex;
            change_portrayal_index(sortedByIndexPortrayals.back(), nextExceptedIndex);

            std::sort(sortedByIndexPortrayals.begin(), sortedByIndexPortrayals.end(), SortByIndex());
          }

          // Continue
          ++nextExceptedIndex;
        }
      }
    }



    // User interface methods
    char welcome() {

      console << '\n' << LINE << ASCII_ART << LINE << '\n';
      console << "I was planning on planting a randomized message-of-the-day here.";
      if (DEBUGGING) {
        console << ".. (DEBUGGING)";
      }
      console << SUBLINE << '\'' << WELCOME_SCREEN_SORTING_OPTION << "' -> sort files in \"" << UNSORTED_FOLDER_PATH << '"';
      console << SUBLINE << '\'' << WELCOME_SCREEN_VIEWING_OPTION << "' -> view portrayals by filters";
      console << SUBLINE << '\'' << WELCOME_SCREEN_SUMMARY_OPTION << "' -> sum up all gathered data";

      console << "\n > ";
      return joat::question()[0];
    }



    // Sorting methods
    void user_choose_currentPersona(Origin *const desecendingOrigin) {
      /*
        This function will ask the user to pick a persona from the current origin.
        It will then set the currentPersona variable to the chosen persona.
      */

      console << get_persona_chart(desecendingOrigin, false) << "\n Choose a persona > "; // Display the personas with the amount of portrayals

      while (true) {
        std::string userInput = joat::question();
        currentPersona = persona_exists(userInput, desecendingOrigin); // borrowing global variable for definition without copying
        if (userInput.empty()) {
          return;
        } else if (currentPersona != &PERSONA_ERROR_TYPE) {
          break;
        }
        std::cerr<< "?> ";
      }
    }
    void user_choose_currentOrigin() {
      /*
        This function will ask the user to pick a origin and then a persona
        from that origin. It will then set the currentPersona variable to the
        chosen persona.
      */


      // Define variables
      std::string userInput;
      currentPersona = nullptr;
      Origin* originChoiceResult;


      // Get origin choice
      console << get_origin_chart(false, true) << "\n Choose an origin > ";

      while (true) {
        userInput = joat::question();
        originChoiceResult = origin_exists(userInput);
        if (originChoiceResult != &ORIGIN_ERROR_TYPE) {
          user_choose_currentPersona(originChoiceResult);

          if (currentPersona != &PERSONA_ERROR_TYPE) {
            return;
          }

          console << get_origin_chart(false, true) << "\n Choose an origin > ";
        } else if (userInput.empty()) {
          return;
        }
        std::cerr<< "?> ";
      }
    }



    void user_assign_tags_to_unsorted_files() {
      /*
        This function will ask the user to assign tags to each file in
        the unsortedPortrayals deque. Each file can be skipped and returned
        back to if needed.

        Just to make sure, the unsortedPortrayals deque is sorted by last
        interaction in ascending order. Meaning the first file added is
        the first file to be processed.

        Note: Keep in mind that the order still matters. Make sure
        the lambda function which checks which file is older aka.
        smaller is correct AND (!) executed.
      */

     if (unsortedPortrayalsPaths.empty()) {
       console << "Add some files into \"" << UNSORTED_FOLDER_PATH << "\" first.";
       return;
      }

      console << "You have " << unsortedPortrayalsPaths.size() << " unsorted files to assign single-character tags";
      console << SUBLINE << "The files are sorted by last interaction in ascending order (oldest first)";
      console << SUBLINE << "'/skip' or *enter* -> continue to the next file";
      console << SUBLINE << "'/undo' -> go back to the previous file";
      console << SUBLINE << "'/save' -> save and exit";
      console << SUBLINE << "'/exit' or *enter* -> exit without saving";
      console << SUBLINE << "'/tags' -> show the tag chart";
      console << SUBLINE << "[Position in filesystem / Amount of changes / Total amount of files]\n";


      // Question-answer loop
      unsigned int positionInUnsortedFolder = 0; // The position of the current file in the unsortedPortrayals deque
      while (positionInUnsortedFolder < unsortedPortrayalsPaths.size()) {


        // Shortened path to allow subfolder to be shown
        unsigned short depthOfUnsortedFile = unsortedPortrayalsPaths[positionInUnsortedFolder].depth();
        unsigned short depthOfUnsortedFolder = joat::VirtualPath(UNSORTED_FOLDER_PATH).depth();
        std::string pathShortend;
        for (unsigned short i = depthOfUnsortedFolder; i < depthOfUnsortedFile; ++i) {
          pathShortend += unsortedPortrayalsPaths[positionInUnsortedFolder][i];
          if (i != depthOfUnsortedFile - 1) {
            pathShortend += '\\';
          }
        }
        

        console << SUBLINE << "Tags for " << pathShortend;
        console << '[' << positionInUnsortedFolder + 1 << '/' << aboutToBeSortedPortrayalsQueue.size() << '/' << unsortedPortrayalsPaths.size() << "]: ";
        std::string userInput = joat::question();

        if (userInput.empty() or userInput == "/skip") {
          console << WSUBSUBLINE << "Skipped " << joat::shorten_str_if_necessary_reverse(unsortedPortrayalsPaths[positionInUnsortedFolder].path) << '\n';
          ++positionInUnsortedFolder;
          continue;
        }

        if (userInput == "/tags") {
          console << get_tag_chart(true);
          continue;
        }

        if (userInput == "/exit") {
          console << WSUBSUBLINE << "Reverting back to the previous state.";
          aboutToBeSortedPortrayalsQueue.clear();
          return;
        }

        if (userInput == "/save") {
          console << WSUBSUBLINE << "Applying " << aboutToBeSortedPortrayalsQueue.size() << " changes and exiting. Leave the rest to the program.";
          return;
        }


        if (userInput == "/undo") {

          // Nothing to undo at all
          if (positionInUnsortedFolder == 0 and aboutToBeSortedPortrayalsQueue.empty()) {
            console << WSUBSUBLINE << "Nothing to undo.";
            continue;
          } else if (positionInUnsortedFolder == 0 and !aboutToBeSortedPortrayalsQueue.empty()) {
            console << WSUBSUBLINE << "Reverted back to the previous state. No changes made.";
            aboutToBeSortedPortrayalsQueue.clear();
            continue;
          }

          // Undo skipping
          // If there has been a change to a file at all
          if (!aboutToBeSortedPortrayalsQueue.empty()) {
            // If the last change wasn't assigning tags to an unsorted portrayal
            if (aboutToBeSortedPortrayalsQueue.back().currentPath != &unsortedPortrayalsPaths[positionInUnsortedFolder]) { // Seg fault when trying to access the last element of an empty deque
              console << WSUBSUBLINE << "Reverted back to the previous file.";
              positionInUnsortedFolder--;
              continue;
            }
          } else if (aboutToBeSortedPortrayalsQueue.empty() and positionInUnsortedFolder > 0) {
            console << WSUBSUBLINE << "Reverted back to the previous file.";
            positionInUnsortedFolder--;
            continue;
          }

          console << WSUBSUBLINE << "Undid last change.";
          aboutToBeSortedPortrayalsQueue.pop_back();
          positionInUnsortedFolder--;
          continue;
        }


        std::deque<char> validTags;

        for (char tag : userInput) {
          if (!tag_exists(tag)) {
            console << WSUBSUBLINE << "No tag with key '" << tag << "' exists.\n";
            continue;
          }

          if (joat::does_this_exist_in_deque(validTags, tag)) {
            console << WSUBSUBLINE << TAGS_LOOKUP.at(tag) << " (" << tag << ") is already assigned.\n";
            continue;
          }

          console << WSUBSUBLINE << "Assigned " << TAGS_LOOKUP.at(tag) << " (" << tag << ")\n";
          validTags.push_back(tag);
        }

        if (validTags.empty()) {
          console << WSUBSUBLINE << "None of these were valid. Let's try again.";
          continue;
        }


        // Add to the queue
        aboutToBeSortedPortrayalsQueue.push_back({&unsortedPortrayalsPaths[positionInUnsortedFolder], validTags});
        ++positionInUnsortedFolder;
      }

      if (!aboutToBeSortedPortrayalsQueue.empty()) {
        console << SUBLINE << "Done and dusted. You've reached the end and the program will continue from here.";
      } else {
        console << SUBLINE << "No tags were assigned. No changes made.";
      }
      
      console << SUBLINE << "Press enter to go back to main-menu..."; std::cin.get(); // Pause
    }



    void place_aboutToBeSortedPortrayalsQueue_into_ecosystem() {
      /*
        This function will take the aboutToBeSortedPortrayalsQueue deque
        and apply the changes to the portrayals deque. The portrayals deque
        will be updated with the new portrayals and the unsortedPortrayalsPaths
        deque will be cleared from the files that were sorted.
      */

      console << "Applying changes " << aboutToBeSortedPortrayalsQueue.size() << " changes to the portrayals deque.";


      for (auto& [file, assignedTags] : aboutToBeSortedPortrayalsQueue) {

        console << SUBLINE << joat::shorten_str_if_necessary_reverse(file->path) << " -> ";


        index_t newIndex = portrayalsByPersona[currentPersona].size() + 1;
        Persona* persona = currentPersona;
        std::deque<char> newTags = assignedTags;


        std::string newPath = ANTI36_FOLDER;
        newPath += '\\';
        newPath += persona->origin->name;
        newPath += '\\';
        newPath += persona->name;
        newPath += '\\';
        newPath += std::to_string(newIndex);
        newPath += '_';
        for (char tag : newTags) {
          newPath += tag;
        }
        newPath += '_';
        newPath += file->extension();


        if (!DEBUGGING) {
          file->move_to(newPath);
        } else {
          file->pretend_to_move_to(newPath);
        }


        // Move file to the new path
        files.push_back(*file);
        unsortedPortrayalsPaths.erase(std::remove(unsortedPortrayalsPaths.begin(), unsortedPortrayalsPaths.end(), *file), unsortedPortrayalsPaths.end());


        // Integrate into the Anti36 ecosystem
        portrayals.push_back({newIndex, persona, newTags, &files.back()});

        portrayalsByPersona[persona].push_back(&portrayals.back());
        portrayalsByOrigin[origin_exists(persona->origin->name)].push_back(&portrayals.back()); // Work around for const
        for (char tag : portrayals.back().tags) {
          portrayalsByTag[tag].push_back(&portrayals.back());
        }
        portrayalsByType[EXTENSION_TO_MEDIA.at(portrayals.back().where->extension())].push_back(&portrayals.back());

        console << portrayals.back().where->filename();
      }

      aboutToBeSortedPortrayalsQueue.clear();
    }



    // Filter and view methods
    void set_collection_based_on_filters() {
      /*
        In this function, the collection deque will be filled with the portrayals
        that fit the filters set by the user. The filters are stored in the
        byOriginsFilter, byTagsFilter, and byTypeFilter deques. The filters are
        exclusive, meaning that the portrayals have to fit all the filters to be
        added to the collection deque.

        In case a byXYFilter is empty:
          - If byOriginsFilter are empty, all Origins and their personas are selected
          - If byTagsFilter is empty, tags are ignored
          - If byTypeFilter is both, all media is selected
      */

      collection.clear();


      // Quick check
      if (byOriginsFilter.empty()) {
        byOriginsFilter = personasByOrigin;
      }


      for (const auto& [origin, personas] : byOriginsFilter) {
        for (Persona* persona : personas) {
          for (Portrayal* portrayal : portrayalsByPersona[persona]) {

            bool fitsFilters = true;

            if (!byTagsFilter.empty()) {
              // If the portrayal doesn't have a tag from the byTagsFilter deque, it doesn't fit the filters
              for (char tag : byTagsFilter) {
                if (!joat::does_this_exist_in_deque(portrayal->tags, tag)) {
                  fitsFilters = false;
                  break;
                }
              }
            }

            if (byTypeFilter != BOTH) {
              if (EXTENSION_TO_MEDIA.at(portrayal->where->extension()) != byTypeFilter) {
                fitsFilters = false;
              }
            }

            if (fitsFilters) {
              collection.push_back(portrayal);
            }
          }
        }
      }
    }



    void user_choose_filter_tag() {

      console << get_tag_chart(true);

      while (true) {

        console << SUBLINE << "Choose a tag(!) or press enter to exit > ";
        char choiceAsChar = joat::question()[0];

        if (tag_exists(choiceAsChar)) {
          if (!joat::does_this_exist_in_deque(byTagsFilter, choiceAsChar)) {
            console << WSUBLINE << '"' << TAGS_LOOKUP.at(choiceAsChar) << '"';
            byTagsFilter.push_back(choiceAsChar);
          } else {
            console << WSUBLINE << "The tag \"" << TAGS_LOOKUP.at(choiceAsChar) << "\" is already selected.";
          }
        }

        else if (choiceAsChar == '\0') {
          return;
        }

        else {
          std::cerr << WSUBSUBLINE << "Invalid tag.";
        }
      }
    }
    void user_choose_filter_type() {

      console << WSUBLINE << "Choose a type (Both, ";
      console << "Image w. " << portrayalsByType[IMAGE].size() << ", ";
      console << "Video w. " << portrayalsByType[VIDEO].size() << ") > ";
      char choice = joat::question()[0];


      switch (choice) {
        case 'A':
          byTypeFilter = BOTH;
          console << WSUBSUBLINE << "Filtering by all types.";
          return;
        case 'I':
          byTypeFilter = IMAGE;
          console << WSUBSUBLINE << "Filtering by images.";
          return;
        case 'V':
          byTypeFilter = VIDEO;
          console << WSUBSUBLINE << "Filtering by videos.";
          return;
        default:
          std::cerr << WSUBSUBLINE << "Not invented yet.";
          return;
      }
    }
    void user_choose_filter_persona(Origin *const selectedOrigin) {

      console << get_persona_chart(selectedOrigin, true);
      console << "\nPick a persona from \"" << selectedOrigin->name << "\" ('*' to select the origin) > ";

      while (true) {

        std::string userInput = joat::question();

        if (userInput.empty()) {
          return;
        }

        if (userInput == "*") {
          console << WSUBLINE << "Selected origin \"" << selectedOrigin->name << '"';
          byOriginsFilter[selectedOrigin] = personasByOrigin[selectedOrigin];
          return;
        }

        Persona* selectedPersona = persona_exists(userInput, selectedOrigin);

        if (selectedPersona->name != ORIGIN_ERROR_TYPE.name) {
          if (joat::does_this_exist_in_deque(byOriginsFilter[selectedOrigin], selectedPersona)) {
            console << WSUBLINE << "The persona \"" << selectedPersona->name << "\" is already selected.";
            continue;
          }
          console << WSUBLINE << "Selected persona \"" << selectedPersona->name << '"';
          byOriginsFilter[selectedOrigin].push_back(selectedPersona);
          console << "\nAnother one? > ";
        }

        else {
          std::cerr << "Who's that > ";
        }
      }
    }



    void user_choose_filter_origin() {

      console << get_origin_chart(false, true);
      console << "\nPick an origin to reveal it's personas > ";

      while (true) {

        std::string userInput = joat::question();

        if (userInput.empty()) {
          return;
        }

        Origin* originChoice = origin_exists(userInput);

        if (originChoice == &ORIGIN_ERROR_TYPE) {
          std::cerr << "What's that? > ";
          continue;
        }

        if (byOriginsFilter[originChoice].size() == personasByOrigin[originChoice].size()) {
          console << "Already selected. > ";
          continue;
        }

        // Select persona (or origin)
        user_choose_filter_persona(originChoice);
        console << "\nPick an origin to reveal it's personas > ";
      }
    }



    void user_choose_filters() {
      /*
        This function will ask the user to select some filters like
        personas from specific origins (or * for the origin itself),
        tags, and media type. The filters will be stored in the
        byOriginsFilter, byTagsFilter, and byTypeFilter deques.
      */

      console << "Based on your filters, a collection of portrayals will be put together. Have fun!";
      console << SUBLINE << "How to set filters:";
      console << SUBSUBLINE << "'persona' -> select a persona from a specific origin. You can also use '*' for all personas from that origin.";
      console << SUBSUBLINE << "'tag' -> select a tag(s)";
      console << SUBSUBLINE << "'type' -> select a portrayal type (image or video)";

      console << SUBLINE << "Other commands:";
      console << SUBSUBLINE << "'/clear' -> reset all filters";
      console << SUBSUBLINE << "'/exit' -> exit without saving";
      console << SUBSUBLINE << "'/save' or *enter* -> save and exit";
      console << SUBSUBLINE << "'/summary' -> show the current filters and how many portrayals fit them\n";


      while (true) {

        console << SUBLINE; std::string userInput = joat::question();


        if (userInput.empty() or userInput == "/save") {
          console << WSUBSUBLINE << "Saved (not cleared) and exited";
          return;
        }

        else if (userInput == "/exit" or userInput == "/clear") {
          byOriginsFilter.clear();
          byTagsFilter.clear();
          byTypeFilter = BOTH;
          if (userInput == "/exit") {
            console << WSUBSUBLINE << "Cleared and exited";
            return;
          }
          console << WSUBSUBLINE << "All cleared";
        }


        else if (userInput == "/summary") {
          console << WSUBSUBLINE << "Those are the filters you've set:";

          console << SUBSUBLINE << byOriginsFilter.size() << " origins:";
          for (const auto& [origin, itsPersonas] : byOriginsFilter) {
            console << CRAZYSUBLINE << origin->name << ':';
            if (itsPersonas.size() == personasByOrigin[origin].size()) {
              console << " complete";
            } else {
              for (Persona* persona : itsPersonas) {
                console << TURBOCRAZYSUBLINE << persona->name;
              }
            }
          }

          console << SUBSUBLINE << byTagsFilter.size() << " tags:";
          for (char tag : byTagsFilter) {
            console << CRAZYSUBLINE << TAGS_LOOKUP.at(tag) << " (" << tag << ')';
          }

          console << SUBSUBLINE << "Type: ";
          switch (byTypeFilter) {
            case IMAGE: console << "image"; break;
            case VIDEO: console << "video"; break;
            case BOTH: console << "both"; break;
          }

          console << SUBSUBLINE << "So all in all, ";
          set_collection_based_on_filters();
          console << collection.size() << " portrayals fit those criteria.\n";

          collection.clear();
        }


        else if (userInput == "persona") {
          user_choose_filter_origin();
        }

        else if (userInput == "tag") {
          user_choose_filter_tag();
        }

        else if (userInput == "type") {
          user_choose_filter_type();
        }

        else {
          std::cerr << WSUBLINE << "Nuh uh!\n";
        }
      }
    }



    void generate_HTML_file() {
      /*
        This function will generate a HTML file which contains all the portrayals that fits the
        filters. See namespace Anti36Local as reference for the HTML structure.

        In the header, the mutable structure is as follows:
          - First are the origins with only their names if the entire origin is selected
          - Then are the personas with their names and their origin's name behind it as "'d origin"
          - Then, the tags (not as key) are listed
          - Finally, the type of the portrayals is listed (image, video, both)
        
        It also reverts the filters to their default state.  
      */

      console << "Generating HTML file";


      std::ofstream htmlContent(HTML_OUTPUT_FILE);

      // Header
      htmlContent << HTML_HEADER[0]; // <h2 style="color: white">Found_
      htmlContent << std::to_string(collection.size());
      htmlContent << HTML_HEADER[1]; // _portrayals for [


      if (byOriginsFilter.size() == origins.size()) {
        htmlContent << "everything, ";
        byOriginsFilter.clear(); // Clear to avoid executing a block below.
      } 

      while (byOriginsFilter.size() > 0) {
        const auto& [iteratedOrigin, itsPersonas] = *byOriginsFilter.begin();
        if (itsPersonas.size() == personasByOrigin[iteratedOrigin].size()) {
          htmlContent << iteratedOrigin->name;
          htmlContent << ", ";
        }

        // Personas
        else {
          for (Persona* persona : itsPersonas) {
            htmlContent << persona->name;
            htmlContent << " d'";
            htmlContent << iteratedOrigin->name;
            htmlContent << ", ";
          }
        }
        byOriginsFilter.erase(byOriginsFilter.begin());
      }


      // Tags
      while (byTagsFilter.size() > 0) {
        htmlContent << TAGS_LOOKUP.at(*byTagsFilter.begin());
        htmlContent << ", ";
        byTagsFilter.pop_front();
      }


      // Media type
      switch (byTypeFilter) {
        case IMAGE: htmlContent << "images"; break;
        case VIDEO: htmlContent << "videos"; break;
        case BOTH: htmlContent << "any type"; break;
      }
      byTypeFilter = BOTH;


      htmlContent << HTML_HEADER[2]; // ]. Enjoy!</h2> <body style="background-color:#330000;">


      while (collection.size() > 0) {
        Portrayal* portrayal = collection.front();
        switch (EXTENSION_TO_MEDIA.at(portrayal->where->extension())) {
          case IMAGE: {
            htmlContent << HTML_IMAGE[0]; // """<img src=""""
            htmlContent << portrayal->where->path; // the full path to the image
            htmlContent << HTML_IMAGE[1]; // """" controls width=\"300\">"""
            break;
          }
          case VIDEO: {
            htmlContent << HTML_VIDEO[0]; // """<video src=""""
            htmlContent << portrayal->where->path; // the full path to the video
            htmlContent << HTML_VIDEO[1]; // """" controls width=\"300\">"""
            break;
          }
        }
        collection.pop_front();
      }


      htmlContent.close();
      joat::cmd(HTML_OUTPUT_FILE);
    }



    public:
      explicit Main() {

        // Setup
        console << NEXT;
        read_ANTI36_FOLDER();
        console << NEXT;
        read_UNSORTED_FOLDER();
        console << NEXT;
        check_folders();
        console << NEXT;
        check_files();
        console << NEXT;
        catagorize_A36L_folders();
        console << NEXT;
        catagorize_files();
        console << NEXT;
        sort_byXY_containers();
        console << NEXT;
        full_duplicate_index_fix();
        console << NEXT;
        full_index_gaps_fix();


        // The user interface
        while (true) {
          char userInput = welcome(); // New-line is included in the function

          switch (userInput) {
            case WELCOME_SCREEN_SORTING_OPTION: {
              user_choose_currentOrigin(); // Exits with a new line due to user-interaction, entry-point for selecting a persona
              if (currentPersona != nullptr and currentPersona != &PERSONA_ERROR_TYPE) {
                user_assign_tags_to_unsorted_files();
                console << NEXT;
                place_aboutToBeSortedPortrayalsQueue_into_ecosystem();
              }
            }

            case WELCOME_SCREEN_VIEWING_OPTION: {
              break;
            }

            case WELCOME_SCREEN_SUMMARY_OPTION: {
              summarize();
              break;
            }

            default: {
              return;
            }
          }

          // Pause
          std::cout << "Press enter to go refresh...";
          std::cin.get();
        }
      }
  };
};


int main() {
  while (true) { // For refreshing without restarting
    Anti36Manager::Main main;
  }
}