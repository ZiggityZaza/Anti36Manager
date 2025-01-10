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

#include "cslib.h++" // Custom library for Anti36Manager
#include <unordered_map> // Faster lookups
#include <filesystem> // Manipulating and reading files and folders in the Anti36Local folder
#include <algorithm> // Finding elements in a container
#include <iostream> // Printing out messages and std::string (and everything that comes with it)
#include <fstream> // Generating html file
#include <cstdint> // Cooler numbers (small numbers supported by stl)
#include <deque> // Containers with continuous memory addresses
#include <map> // Specifically for TAGS lookup


#pragma once
#if __cplusplus < 202002L
  #error This program requires C++20
#endif

#ifndef _WIN32
  #error This program is only for Windows
#endif


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
  static constexpr bool DEBUGGING = false;
  static constexpr char WELCOME_SCREEN_SORTING_OPTION = '0';
  static constexpr char WELCOME_SCREEN_VIEWING_OPTION = '1';
  static constexpr char WELCOME_SCREEN_SUMMARY_OPTION = '2';
  static constexpr char WELCOME_SCREEN_LEAVING_OPTION = '3';
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
    const cslib::VirtualPath *const where;
  };
  struct Persona {
    const Origin *const origin;
    const std::string name;
    const cslib::VirtualPath *const where;
  };
  struct Portrayal {
    index_t index; // Can change incase of index gap fixing
    const Persona *const persona;
    const std::deque<char> tags;
    cslib::VirtualPath *const where;
  };


  // Constants
  static constexpr const char* ANTI36_FOLDER = "E:\\Anti36Local";
  static constexpr const char* UNSORTED_FOLDER_PATH = "E:\\$unsorted";
  static constexpr index_t INDEX_ERROR_VALUE = ~index_t(0); // Error value for index_t (largest possible value)
  static constexpr index_t INDEX_AUTO_INCREMENT_CODE = 0;
  static constexpr Portrayal* NOT_MEANT_TO_REPLACE_CODE = nullptr;


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
    {'0', "_0"},
    {'1', "_1"},
    {'2', "_2"},
    {'3', "_3"},
    {'4', "_4"},
    {'5', "_5"},
    {'6', "_6"},
    {'7', "_7"},
    {'8', "_8"},
    {'9', "_9"}
  };




  class Main {
    /*
      The difference between the namespace and the class is that the class
      is specifically for mutable variables and methods.
    */


    // Pillar containers
    std::deque<cslib::VirtualPath> folders;
    std::deque<cslib::VirtualPath> files;
    std::deque<Origin> origins;
    std::deque<Persona> personas;
    std::deque<Portrayal> portrayals;

    // Containers for easy access
    std::unordered_map<Origin*, std::deque<Portrayal*>> portrayalsByOrigin;
    std::unordered_map<Origin*, std::deque<Persona*>> personasByOrigin;
    std::unordered_map<Persona*, std::deque<Portrayal*>> portrayalsByPersona;
    std::unordered_map<char, std::deque<Portrayal*>> portrayalsByTag;
    std::unordered_map<MediaType, std::deque<Portrayal*>> portrayalsByType;
    /*
      Important note: The order of portrayals in easy-access containers typically
      follows the first-to-last index, as std::filesystem::recursive_directory_iterator
      traverses directories surface-first alphabetically. However, some methods may
      disrupt this order by swapping indexes.

      Refreshing the program resolves this by reloading and re-adding content.
    */


    // Filters
    std::deque<char> byTagsFilter;
    std::unordered_map<Origin*, std::deque<Persona*>> byOriginsFilter;
    MediaType byTypeFilter = BOTH;

    // Other variables
    cslib::LocalServer localServer;

    Persona* currentPersona = nullptr;
    std::deque<cslib::VirtualPath> unsortedPortrayalsPaths;
    struct aboutToBeSortedPortrayal {
      cslib::VirtualPath currentPath;
      std::deque<char> assignedTags;
      index_t squeezeInAs;
      Portrayal* replacementFor;
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
      result += cslib::form_2d_chart(containerForChart);
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
      result += cslib::form_2d_chart(containerForChart);
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
      result += cslib::form_2d_chart(containerForChart);
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
      for (const cslib::VirtualPath& folder : folders) {
        console << SUBSUBLINE << folder << " @ " << folder.lastInteraction;
      }
      console << SUBLINE << files.size() << " files:";
      for (const cslib::VirtualPath& file : files) {
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
      for (const cslib::VirtualPath& unsortedPortrayal : unsortedPortrayalsPaths) {
        console << SUBSUBLINE << cslib::shorten_str_if_necessary_reverse(unsortedPortrayal.path,75);
        console << " @ " << unsortedPortrayal.lastInteraction;
      }
      console << '\n';
    }
    std::string summarize_json() {
      /*
        This function summarizes the data in the portrayals deque
        and returns it as a JSON string using nlohmann::json.
      */

      nlohmann::json result;

      // Pillar containers
      result["folders"] = {};
      for (const cslib::VirtualPath& folder : folders) {
        result["folders"].push_back(folder.path);
      }
      result["files"] = {};
      for (const cslib::VirtualPath& file : files) {
        result["files"].push_back(file.path);
      }
      result["origins"] = {};
      for (Origin& origin : origins) {
        result["origins"][origin.name] = {};
        for (Persona* persona : personasByOrigin[&origin]) {
          result["origins"][origin.name][persona->name] = {};
          for (Portrayal* portrayal : portrayalsByPersona[persona]) {
            result["origins"][origin.name][persona->name].push_back(portrayal->where->filename());
          }
        }
      }

      // Filter containers
      result["filters"] = {};
      result["filters"]["tags"] = {};
      for (char tag : byTagsFilter) {
        result["filters"]["tags"].push_back(tag);
      }
      result["filters"]["origins"] = {};
      for (const auto& [origin, personas] : byOriginsFilter) {
        result["filters"]["origins"][origin->name] = {};
        for (Persona* persona : personas) {
          result["filters"]["origins"][origin->name].push_back(persona->name);
        }
      }

      // Other containers
      result["currentPersona"] = currentPersona ? currentPersona->name : "none";
      result["unsortedPortrayals"] = {};
      for (const cslib::VirtualPath& unsortedPortrayal : unsortedPortrayalsPaths) {
        result["unsortedPortrayals"].push_back(unsortedPortrayal.path);
      }

      // Tags
      result["tags"] = nlohmann::json::object();
      for (const auto& [tag, tagMeaning] : TAGS_LOOKUP) {
        std::string nlohmannJsonUsableTag = std::string(1, tag); // nlohmann::json thinks char is a number
        result["tags"][nlohmannJsonUsableTag] = tagMeaning;
      }

      // Constants
      result["UNSORTED_FOLDER_PATH"] = UNSORTED_FOLDER_PATH;

      return result.dump(2);
    }



    // Setup methods
    void read_ANTI36_FOLDER() {
      /*
        This function goes through every file and folder
        in the Anti36Local folder to add them to the folders and files deque.
      */

      console << "Reading content of " << ANTI36_FOLDER;

      for (const std::filesystem::directory_entry& fileEntry : std::filesystem::recursive_directory_iterator(ANTI36_FOLDER)) {

        cslib::VirtualPath entry(fileEntry.path().string());

        console << SUBLINE << entry << " is ";

        if (entry.type == cslib::VirtualPath::DICT) {
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

        cslib::VirtualPath entry(fileEntry.path().string());

        console << SUBLINE << cslib::shorten_str_if_necessary_reverse(entry.path) << " @ " << entry.lastInteraction;

        if (entry.type == cslib::VirtualPath::FILE) {
          unsortedPortrayalsPaths.push_back(entry);
        }
      }


      // rearrange the files by last interaction
      std::sort(unsortedPortrayalsPaths.begin(), unsortedPortrayalsPaths.end(), // Since no pointers are used, the deque is rearranged
        // If a is older (smaller) than b, a comes first
        [](const cslib::VirtualPath& a, const cslib::VirtualPath& b) {
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

      for (const cslib::VirtualPath& folder : folders) {
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


      for (const cslib::VirtualPath& file : files) {

        console << SUBLINE << file;


        if (file.depth() != 4) {
          throw std::runtime_error("The file \"" + file.path + "\" is trailing.");
        }


        if (EXTENSION_TO_MEDIA.find(file.extension()) == EXTENSION_TO_MEDIA.end()) {
          throw std::runtime_error("The extension \"" + file.extension() + "\" of the file \"" + file.path + "\" is not supported.");
        }


        // Split the filename into parts: index, tags, extension
        std::deque<std::string> splitFilename = cslib::separate(file.filename(), '_');


        if (splitFilename.size() != 3) {
          throw std::runtime_error("The file \"" + file.path + "\" doesn't comply with the naming convention.");
        }


        // Translate index
        int translatingIndex = cslib::stoi(splitFilename[0]);
        if (translatingIndex == cslib::STOI_ERROR_CODE) {
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

          if (cslib::does_this_exist_in_deque(alreadyOccuredTags, tag)) {
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

      for (cslib::VirtualPath& folder : folders) {
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

      for (cslib::VirtualPath& file : files) {
        
        console << SUBLINE << "Categorizing file " << file;


        // Split the path into parts: E:, Anti36Local, origin, persona and filename (index_tags_.extension)
        std::deque<std::string> splitFilename = cslib::separate(file.filename(), '_');


        index_t index = cslib::stoi(splitFilename[0]);
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

          if (cslib::does_this_exist_in_deque(alreadyOccuredIndex, portrayal->index)) {

            index_t nextAvailableIndex = 1;
            while (cslib::does_this_exist_in_deque(alreadyOccuredIndex, nextAvailableIndex)) {
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
      console << SUBLINE << '\'' << WELCOME_SCREEN_LEAVING_OPTION << "' -> leave the program";

      console << "\n > ";
      return cslib::question()[0];
    }



    // Sorting methods
    void user_choose_currentPersona(Origin *const desecendingOrigin) {
      /*
        This function will ask the user to pick a persona from the current origin.
        It will then set the currentPersona variable to the chosen persona.
      */

      console << get_persona_chart(desecendingOrigin, false) << "\n Choose a persona > "; // Display the personas with the amount of portrayals

      while (true) {
        std::string userInput = cslib::question();
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

      std::string userInput;
      currentPersona = nullptr;
      Origin* originChoiceResult;

      console << get_origin_chart(false, true) << "\n Choose an origin > ";

      while (true) {
        userInput = cslib::question();
        originChoiceResult = origin_exists(userInput);
        if (originChoiceResult != &ORIGIN_ERROR_TYPE) {
          user_choose_currentPersona(originChoiceResult);

          if (currentPersona != &PERSONA_ERROR_TYPE) {
            return;
          }

          console << get_origin_chart(false, true) << "\n Back to selecting an origin > ";
          continue;
        } else if (userInput.empty()) {
          return;
        }
        std::cerr<< "?> ";
      }
    }



    void user_undid_last_change(unsigned int& positionInUnsortedFolder) {

      if (positionInUnsortedFolder == 0) {
        console << WSUBSUBLINE << "Nothing to undo.";
        return;
      }

      else if (aboutToBeSortedPortrayalsQueue.empty() or aboutToBeSortedPortrayalsQueue.back().currentPath != unsortedPortrayalsPaths[positionInUnsortedFolder-1]) {
        console << WSUBSUBLINE << "Went back to the previous file.";
      }

      else {
        console << WSUBSUBLINE << "Undid last change.";
        aboutToBeSortedPortrayalsQueue.pop_back();
      }

      positionInUnsortedFolder--;
    }
    std::string get_short_unsorted_file_path(cslib::VirtualPath& file, unsigned int positionInUnsortedFolder) {

      // Shortened path to allow subfolder to be shown
      unsigned short depthOfUnsortedFile = file.depth();
      unsigned short depthOfUnsortedFolder = cslib::VirtualPath(UNSORTED_FOLDER_PATH).depth();
      uint8_t recommendedSubfolderStringLenght = 5;

      std::string pathShortend;
      for (uint8_t folderDepthPos = depthOfUnsortedFolder; folderDepthPos < depthOfUnsortedFile; ++folderDepthPos) { // Start with relative path
        pathShortend += cslib::shorten_str_if_necessary(file[folderDepthPos], recommendedSubfolderStringLenght);

        // Remove last dot to make output look better and add a backslash to indicate a subfolder
        if (pathShortend.back() == '.') {
          pathShortend.pop_back();
        }
        pathShortend += '\\';
      }
      pathShortend += cslib::shorten_str_if_necessary(file.filename());

      pathShortend += '[';
      pathShortend += std::to_string(positionInUnsortedFolder + 1);
      pathShortend += '/';
      pathShortend += std::to_string(unsortedPortrayalsPaths.size());
      pathShortend += '/';
      pathShortend += std::to_string(aboutToBeSortedPortrayalsQueue.size());
      pathShortend += ']';

      return pathShortend; // Example: "$unso..\subfo..\file.jpg[1/3/2]"
    }
    void user_squeeze_and_choose_tags(std::string& userInput, index_t& squeezedInAs) {

      std::deque<std::string> splitUserInput = cslib::separate(userInput.substr(9), ','); // Remove the "/squeeze:" part

      if (splitUserInput.size() != 2) {
        console << WSUBSUBLINE << "One comma is needed.";
        squeezedInAs = INDEX_ERROR_VALUE;
        return;
      }
      else if (splitUserInput[0].empty() or splitUserInput[1].empty()) {
        console << WSUBSUBLINE << "'newIndex' or 'tags' are empty.";
        squeezedInAs = INDEX_ERROR_VALUE;
        return;
      }

      squeezedInAs = cslib::stoi(splitUserInput[0]);

      if (squeezedInAs == cslib::STOI_ERROR_CODE) {
        console << WSUBSUBLINE << "The index '" << splitUserInput[0] << "' is not a number.";
        squeezedInAs = INDEX_ERROR_VALUE;
        return;
      }
      else if (squeezedInAs < 1) {
        console << WSUBSUBLINE << "Index is smaller than possible.";
        squeezedInAs = INDEX_ERROR_VALUE;
        return;
      }
      else if (squeezedInAs > portrayalsByPersona[currentPersona].size() + 1) {
        console << WSUBSUBLINE << "Squeezing only works if the index is smaller than the amount of portrayals + 1.";
        squeezedInAs = INDEX_ERROR_VALUE;
        return;
      }
      else if (squeezedInAs == cslib::STOI_EMPTY_CODE) {
        squeezedInAs = INDEX_ERROR_VALUE;
        return;
      }

      // Continue as planned
      userInput = splitUserInput[1];
    }
    void user_replaceses_portrayal(std::string& userInput, Portrayal*& replacingPortrayal) {

      std::string splitUserInput = userInput.substr(9); // Remove the "/replace:" part

      index_t replacingId = cslib::stoi(splitUserInput);
      
      if (replacingId == cslib::STOI_ERROR_CODE) {
        console << WSUBSUBLINE << "The index \"" << splitUserInput << "\" is not a number.";
        replacingPortrayal = NOT_MEANT_TO_REPLACE_CODE;
        return;
      }
      else if (replacingId < 1) {
        console << WSUBSUBLINE << "Index is smaller than possible.";
        replacingPortrayal = NOT_MEANT_TO_REPLACE_CODE;
        return;
      }
      else if (replacingId > portrayalsByPersona[currentPersona].size()) {
        console << WSUBSUBLINE << "Index is larger than possible.";
        replacingPortrayal = NOT_MEANT_TO_REPLACE_CODE;
        return;
      }
      else if (replacingId == cslib::STOI_EMPTY_CODE) {
        replacingPortrayal = NOT_MEANT_TO_REPLACE_CODE;
        return;
      }


      // Continue as planned
      for (Portrayal* portrayal : portrayalsByPersona[currentPersona]) {
        if (portrayal->index == replacingId) {
          replacingPortrayal = portrayal;
          break;
        }
      }
      userInput = "/replace:";
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
      console << SUBLINE << "'/exit' -> exit without saving";
      console << SUBLINE << "'/tags' -> show the tag chart";
      console << SUBLINE << "'/squeeze:ownId,tags' -> put this portrayal infront of another";
      console << SUBLINE << "'/replace:replacedId' -> replace this portrayal with another";
      console << SUBLINE << "[Position in filesystem / Amount of changes / Total amount of files]\n";


      // Question-answer loop
      unsigned int positionInUnsortedFolder = 0; // The position of the current file in the unsortedPortrayals deque
      while (positionInUnsortedFolder < unsortedPortrayalsPaths.size()) {

        index_t squeezedInAs = INDEX_AUTO_INCREMENT_CODE;
        Portrayal* replacingPortrayal = NOT_MEANT_TO_REPLACE_CODE;
        cslib::VirtualPath& file = unsortedPortrayalsPaths[positionInUnsortedFolder];


        console << SUBLINE << get_short_unsorted_file_path(file, positionInUnsortedFolder) << ": ";
        std::string userInput = cslib::question();

        if (userInput.empty() or userInput == "/skip") {
          console << WSUBSUBLINE << "Skipped" << '\n';
          ++positionInUnsortedFolder;
          continue;
        }

        else if (userInput == "/tags") {
          console << get_tag_chart(false);
          continue;
        }

        else if (userInput == "/exit") {
          console << WSUBSUBLINE << "Reverting back to the previous state.";
          aboutToBeSortedPortrayalsQueue.clear();
          return;
        }

        else if (userInput == "/save") {
          console << WSUBSUBLINE << "Applying " << aboutToBeSortedPortrayalsQueue.size() << " changes and exiting.";
          return;
        }

        else if (userInput == "/undo") {
          user_undid_last_change(positionInUnsortedFolder);
          continue;
        }

        else if (userInput.find("/squeeze:") == 0) {
          user_squeeze_and_choose_tags(userInput, squeezedInAs);
          if (squeezedInAs == INDEX_ERROR_VALUE) {
            ++positionInUnsortedFolder;
            continue;
          }
        }

        else if (userInput.find("/replace:") == 0) {
          user_replaceses_portrayal(userInput, replacingPortrayal);
          if (replacingPortrayal == NOT_MEANT_TO_REPLACE_CODE) {
            ++positionInUnsortedFolder;
            continue;
          }
        }


        std::deque<char> validTags;

        if (userInput != "/replace:") { // Tags already determined from replaced portrayal
          for (char tag : userInput) {
            if (!tag_exists(tag)) {
              console << WSUBSUBLINE << "No tag with key '" << tag << "' exists.\n";
              continue;
            }

            if (cslib::does_this_exist_in_deque(validTags, tag)) {
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
        }


        if (squeezedInAs != INDEX_AUTO_INCREMENT_CODE) {
          console << WSUBSUBLINE << "Squeezing in as " << squeezedInAs;
        }
        if (replacingPortrayal != NOT_MEANT_TO_REPLACE_CODE) {
          console << WSUBSUBLINE << "Replacing " << replacingPortrayal->where->filename();
        }

        aboutToBeSortedPortrayalsQueue.push_back({unsortedPortrayalsPaths[positionInUnsortedFolder], validTags, squeezedInAs, replacingPortrayal});
        ++positionInUnsortedFolder;
      }

      if (!aboutToBeSortedPortrayalsQueue.empty()) {
        console << SUBLINE << "Done and dusted. You've reached the end.";
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

      console << "Placing " << aboutToBeSortedPortrayalsQueue.size() << " files into the Anti36 ecosystem";


      while (!aboutToBeSortedPortrayalsQueue.empty()) {

        aboutToBeSortedPortrayal& selectedUnsortedPortrayal = aboutToBeSortedPortrayalsQueue.front();

        console << SUBLINE << cslib::shorten_str_if_necessary(selectedUnsortedPortrayal.currentPath.path) << " -> ";


        if (selectedUnsortedPortrayal.replacementFor != NOT_MEANT_TO_REPLACE_CODE) {
          console << selectedUnsortedPortrayal.replacementFor->where->filename() << " (replaced)";
          if (DEBUGGING) {
            selectedUnsortedPortrayal.currentPath.pretend_to_move_to(selectedUnsortedPortrayal.replacementFor->where->path);
          } else {
            selectedUnsortedPortrayal.currentPath.move_to(selectedUnsortedPortrayal.replacementFor->where->path);
          }
          aboutToBeSortedPortrayalsQueue.pop_front();
          continue;
        }

        else if (selectedUnsortedPortrayal.squeezeInAs != INDEX_AUTO_INCREMENT_CODE) {
          // Shift every following portrayal down by one
          for (Portrayal* portrayal : portrayalsByPersona[currentPersona]) {
            if (portrayal->index >= selectedUnsortedPortrayal.squeezeInAs) {
              change_portrayal_index(portrayal, portrayal->index + 1);
            }
          }
        }

        else {
          selectedUnsortedPortrayal.squeezeInAs = portrayalsByPersona[currentPersona].size() + 1;
        }


        // Integrate into the Anti36 ecosystem
        files.push_back(selectedUnsortedPortrayal.currentPath); // Copy current (wrong) path into the files deque
        unsortedPortrayalsPaths.erase(std::remove(unsortedPortrayalsPaths.begin(), unsortedPortrayalsPaths.end(), selectedUnsortedPortrayal.currentPath), unsortedPortrayalsPaths.end());


        portrayals.push_back({selectedUnsortedPortrayal.squeezeInAs, currentPersona, selectedUnsortedPortrayal.assignedTags, &files.back()});
        portrayalsByPersona[currentPersona].push_back(&portrayals.back());
        portrayalsByOrigin[origin_exists(currentPersona->origin->name)].push_back(&portrayals.back());
        for (char tag : portrayals.back().tags) {
          portrayalsByTag[tag].push_back(&portrayals.back());
        }
        portrayalsByType[EXTENSION_TO_MEDIA.at(portrayals.back().where->extension())].push_back(&portrayals.back());


        // Move file to the new path
        std::string newPath = ANTI36_FOLDER;
        newPath += '\\';
        newPath += currentPersona->origin->name;
        newPath += '\\';
        newPath += currentPersona->name;
        newPath += '\\';
        newPath += std::to_string(selectedUnsortedPortrayal.squeezeInAs);
        newPath += '_';
        for (char tag : selectedUnsortedPortrayal.assignedTags) {
          newPath += tag;
        }
        newPath += '_';
        newPath += selectedUnsortedPortrayal.currentPath.extension();

        if (DEBUGGING) {
          files.back().pretend_to_move_to(newPath);
        } else {
          files.back().move_to(newPath);
        }

        console << portrayals.back().where->filename();


        aboutToBeSortedPortrayalsQueue.pop_front();
      }
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


      // In case the byOriginsFilter is empty, only tags and media type are considered
      if (byOriginsFilter.empty()) {
        for (Portrayal& portrayal : portrayals) {

          bool fitsFilters = true;

          if (!byTagsFilter.empty()) {
            // If the portrayal doesn't have a tag from the byTagsFilter deque, it doesn't fit the filters
            for (char tag : byTagsFilter) {
              if (!cslib::does_this_exist_in_deque(portrayal.tags, tag)) {
                fitsFilters = false;
                break;
              }
            }
          }

          if (byTypeFilter != BOTH) {
            if (EXTENSION_TO_MEDIA.at(portrayal.where->extension()) != byTypeFilter) {
              fitsFilters = false;
            }
          }

          if (fitsFilters) {
            collection.push_back(&portrayal);
          }
        }
      }


      for (const auto& [origin, personas] : byOriginsFilter) {
        for (Persona* persona : personas) {
          for (Portrayal* portrayal : portrayalsByPersona[persona]) {

            bool fitsFilters = true;

            if (!byTagsFilter.empty()) {
              // If the portrayal doesn't have a tag from the byTagsFilter deque, it doesn't fit the filters
              for (char tag : byTagsFilter) {
                if (!cslib::does_this_exist_in_deque(portrayal->tags, tag)) {
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
        char choiceAsChar = cslib::question()[0];

        if (tag_exists(choiceAsChar)) {
          if (!cslib::does_this_exist_in_deque(byTagsFilter, choiceAsChar)) {
            console << WSUBLINE << "Added \"" << TAGS_LOOKUP.at(choiceAsChar) << '"';
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
      char choice = cslib::question()[0];


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

        std::string userInput = cslib::question();

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
          if (cslib::does_this_exist_in_deque(byOriginsFilter[selectedOrigin], selectedPersona)) {
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

        std::string userInput = cslib::question();

        if (userInput.empty()) {
          return;
        }

        Origin* originChoice = origin_exists(userInput);

        if (originChoice == &ORIGIN_ERROR_TYPE) {
          std::cerr << "?> ";
          continue;
        }

        if (personasByOrigin[originChoice].empty()) {
          console << "This origin has no personas > ";
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
      console << SUBSUBLINE << "'clear' -> reset all filters";
      console << SUBSUBLINE << "'exit' or *enter* -> exit without saving";
      console << SUBSUBLINE << "'save' -> save and exit";
      console << SUBSUBLINE << "'reveal' -> show the current filters and how many portrayals fit them";


      while (true) {

        console << SUBLINE; std::string userInput = cslib::question();


        if (userInput == "save") {
          console << WSUBSUBLINE << "Saved (not cleared) and exited";
          return;
        }

        else if (userInput == "exit" or userInput == "clear" or userInput.empty()) {
          byOriginsFilter.clear();
          byTagsFilter.clear();
          byTypeFilter = BOTH;
          if (userInput == "exit" or userInput.empty()) {
            console << WSUBSUBLINE << "Cleared and exited";
            return;
          }
          console << WSUBSUBLINE << "All cleared";
        }


        else if (userInput == "reveal") {
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

          if (!byOriginsFilter.empty() and !byTagsFilter.empty()) { // Avoiding a full collection if no filters are set
            console << SUBSUBLINE << "So all in all, ";
            set_collection_based_on_filters();
            console << collection.size() << " portrayals fit those criteria.";
          }

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
          std::cerr << WSUBLINE << "Nuh uh!";
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
      cslib::cmd(HTML_OUTPUT_FILE);
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
        console << NEXT;
        localServer.currentOutput = summarize_json();
        localServer.start();

        std::cin.get();


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
              break;
            }

            case WELCOME_SCREEN_VIEWING_OPTION: {
              console << WHEAD;
              user_choose_filters();
              // Quick check
              if (byOriginsFilter.empty() and !byTagsFilter.empty()) {
                byOriginsFilter = personasByOrigin;
                console << NEXT << "Putting together collection.";
                set_collection_based_on_filters();
                console << NEXT;
                generate_HTML_file();
              }
              break;
            }


            case WELCOME_SCREEN_SUMMARY_OPTION: {
              summarize();
              break;
            }

            case WELCOME_SCREEN_LEAVING_OPTION: {
              console << "Goodbye!";
              std::flush(std::cout);
              std::exit(0);
            }

            default: {
              return;
            }
          }

        }
      }
  };
};
