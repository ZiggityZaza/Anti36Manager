// :::..................:..........:::-=-:::::.........:.:-:::::=:--+=---
// ::::.................:.........:##%#%%%#-::.:::::::::::-::::-=-=-=-::-
// ::::.....:..........::.......:#%%%%%%%%%%=:::::::::::::-::::-+=-===+**
// ::::.....:..........::.......+%%@%@@@@@%%%*::::::::::::--:::-+--=*+=+*
// :::::....:..........::......:+%##%%%%%@@%@%-:::::::::::--:::=*-=+===+*
// :::::....:.........:::.....::*#%%%#*****#@*::::::::::::---:-=*-=+++=+*
// :::::....:.........::::..:::-##%%%%%@@@%%+:::::::::::::-----+*-=++==+*
// :::::....:......:##*+-:::::::+***##*%@@%%*:::::::::::::-----+*-=*===+*
// :::::....:.....#%%@@%%%%@@@@@%#***###*##+:::::::::::::------+*-+*===+*
// :::::....:...:%@@@@@@@@@@@@@@%########*:::::::::::::::------*+-+*===+*
// :::::....:..=%@@@@@@@@@@@@@@@%#######-::::::::::::::::------*+-+*===+*
// :::::...::.=@@@@@@@@@@@@@@@@@@@%%%%@@%%=::::::::::::::-=----*+-+*===+*
// :--::...::+@@@@@@@@@@@@@@@@@@@@%%@@%@%%%%=:----:::::::-=----*=-+*+=++*
// ----::.::=@@@@@@@@@@@@@@@@@@@@@@%%#@@@@%%%#---:::::::--=----*=-**+=++*
// ----:::::@@@@@@@@@@@@@@@@@@@@@@@%#%%@@@@@@%------:::---=---=*=-*#++++*
// -----:::#@@@@@@@@@@@@@*==+%%@@@@##@@@@@@@@+------------=---=#==*#+++=*
// -----::=@%@#.:@@@+::@@@+****#--*@@@+*+#@@**%+----------==--=#=-**++++*
// ===--=.#.-#:#@%@@:@@@@@=#%+#*+*%@@@=@+#*%+@+#+%--------==--+#==**+++++
// ===-::-.:@.+:@:@@@+-@@@@@@@%#%###@@=+@##%*#%+#---------==--+#==**+++++
// ==+#+-@..*#%@%@@@@@@@@@@@@@@@@@@@@@@@@@@%+-*+%#%@@%%*--==--+#==#+++++*
// **##+-@@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@@%%@@@#==-=*#==#+++++*
// ++**+-@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%@@%===*#=+#+++++*
// ++#%+-#@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@%%%%%@@@@@@@%==##=+#=*+++*
// ++%%+--@@@@@@@@@@@@@@@@@@@@@@@%@@@#@@@@@@@%%%%%%%@@@@%#%@*=#*=*#=*+++*
// ++%%+--*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%##%%==%*=*#=*++++
// +*%%+--%@@@@@@@@@@@@@@@@@@@@@@%%@@@%%%@%%%%%%%%#%%%##*#+===%*=##=*++++
// +*%#+-*@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%##%%%%%%%***#====+%+=%#=***++
// +*@#+=@@@@@@@@@@@@@@@@@@%%######%%%%%#########%%#*+*#=====+#+=%#=*=+**
// +*@*+%@@@@@@@@@@@@@@@%%%%%%%%%##%%#############**+*#======+%+*%*=***++
// +*@**@@@@@@@@@@@@@@@@@%%%%%%%%%%%#%#####%%%%##++=**=======*#==%+=+++**
// +*@*@@@@@@@@@@@@@@@@@@@#%%%%%%%%############**=*#*=====+==*#==%+==+=++
// +#@*@@@@@@@@@@@@@@@@@@@#**#*#%%##%%%@@@@%%%*++##*======+++**=+%+==+==+
// +#@%@@@@@@@@@@@@@@@@@@%%####+*#%@@@%%%%%%%########*====+++#*=+#+==+=+=
// +#@%%%%%%%%%%%@@%@%@@@%%%%####%@%%%%%%%%%%############++++#*+**===+=+=
// -++=++++******####%%%%########%#%%%%#####%%%%%%######+=+++#*+**=++=++=
// -=::::::::::::::------=*%%@%%%%%%%%%%%#%%#%%%%%%##*====+++#*+#*++**++*
// -=+#*----:::::::::::::::-=*%%%%#%%%%%%%%%%%%%%%%%%=====+++#*+#*++****#
// --------------------------==+*%%%%####%%%%%%#%%%%%+====++*%++##++*+**#
// AAAAAAÂÂÂÂÂÂÁÁÁÀÄÄÄHHHHH! Around 50 years ago, when I started my first
// education, Mike Mizwalksi introduced me to these paintings. The one of
// the top over there, viewer discretion is advised, Mike Kowalski would
// puncturate one special sound as I exited my mother's front.
// Stay silent if you would like to hear...


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

  // Default values and Configs
  cslib::DualOutput console("E:\\log.txt");
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
  static constexpr const char* PORTRAYAL_DUMP_PATH = "E:\\$portrayal_dump"; // Instead of deleting, the file is moved here to prevent data loss
  static constexpr index_t INDEX_AUTO_INCREMENT_CODE = ~index_t(0);


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
  static const std::map<std::string_view, char> AS_LOOKUP = {};




  class LocalServer {
    public:
      static constexpr uint16_t LISTENING_PORT = 8080;
      static constexpr const char* CONTENT_TYPE = "application/json";
      std::string currentOutput;
      std::string lastInput;
      httplib::Server server;

      ~LocalServer() {server.stop();}

      void start() {

        // Run the server
        console << "Server is running on http://localhost:" << LISTENING_PORT << '\n';
        server.listen("localhost", LISTENING_PORT);
    };
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
    std::deque<cslib::VirtualPath> unsortedPortrayalsPaths;

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


    // Other variables
    LocalServer localServer;


    // Helper methods (usually silent methods)
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



    void move_and_integrate_portrayal(size_t& currentLocationInUnsortedByIndex, Persona *const persona, const std::deque<char>& tags, index_t index) {
      // Important note: Method takes care of moving file and fully integrating. Only this method should be used for this purpose.

      if (index == INDEX_AUTO_INCREMENT_CODE) {
        index = portrayalsByPersona[persona].size() + 1;
      } else {
        for (Portrayal* portrayal : portrayalsByPersona[persona]) {
          if (portrayal->index >= index) {
            portrayal->index++;
          }
        }
      }

      std::string newPath = ANTI36_FOLDER;
      newPath += '\\';
      newPath += persona->origin->name;
      newPath += '\\';
      newPath += persona->name;
      newPath += '\\';
      newPath += std::to_string(index);
      newPath += '_';
      for (char tag : tags) {
        newPath += tag;
      }
      newPath += '_';
      newPath += unsortedPortrayalsPaths[currentLocationInUnsortedByIndex].extension();

      if (!DEBUGGING) {
        unsortedPortrayalsPaths[currentLocationInUnsortedByIndex].move_to(newPath);
      } else {
        unsortedPortrayalsPaths[currentLocationInUnsortedByIndex].pretend_to_move_to(newPath);
      }

      files.push_back(unsortedPortrayalsPaths[currentLocationInUnsortedByIndex]);
      unsortedPortrayalsPaths.erase(unsortedPortrayalsPaths.begin() + currentLocationInUnsortedByIndex);

      portrayals.push_back({index, persona, tags, &files.back()});
      portrayalsByPersona[persona].push_back(&portrayals.back());
      portrayalsByOrigin[origin_exists(persona->origin->name)].push_back(&portrayals.back());
      for (char tag : tags) {
        portrayalsByTag[tag].push_back(&portrayals.back());
      }
      portrayalsByType[EXTENSION_TO_MEDIA.at(files.back().extension())].push_back(&portrayals.back());
    }
    void move_and_replace_portrayal(size_t& currentLocationInUnsortedByIndex, Portrayal *const portrayalInQuestion) {
      // Using std::rename to move the file so files deque is not updated.

      std::filesystem::rename(portrayalInQuestion->where->path, PORTRAYAL_DUMP_PATH + '\\' + portrayalInQuestion->where->filename());
      std::filesystem::rename(unsortedPortrayalsPaths[currentLocationInUnsortedByIndex].path, portrayalInQuestion->where->path);

      unsortedPortrayalsPaths.erase(unsortedPortrayalsPaths.begin() + currentLocationInUnsortedByIndex);
    }



    // Setup methods
    void read_ANTI36_FOLDER() {

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

        if (entry.type == cslib::VirtualPath::DICT) {
          return;
        }
        unsortedPortrayalsPaths.push_back(entry);

        console << SUBLINE << cslib::shorten_str_if_necessary_reverse(entry.path) << " @ " << entry.lastInteraction;
      }


      std::sort(unsortedPortrayalsPaths.begin(), unsortedPortrayalsPaths.end(), // Since no pointers are used, the deque can be rearranged
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
        comply with the naming convention.

        Rules:
          - No subfolders are allowed

        No changes are made here. The folders are just checked.
      */

      console << "Checking folders for compliance with the naming convention";

      for (const cslib::VirtualPath& folder : folders) {
        if (folder.depth() > 4) {
          throw std::runtime_error("The folder \"" + folder.path + "\" is in too deep.");
        }
      }
    }



    void check_files() {
      /*
        This function iterates though the files deque and check if they
        comply with the naming convention.

        Rules (within this function):
          - The file should be in a persona folder
          - The file should have a supported extension
          - The file should have the correct naming convention
            - The index should be a number between 1 and the second largest number index_t can hold
            - The tags should be valid and unique

        No changes are made here. The files are just checked.
      */


      console << "Checking files for compliance with the naming convention";


      for (const cslib::VirtualPath& file : files) {

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


        int translatingIndex = cslib::stoi(splitFilename[0]);
        if (translatingIndex <= 0 or translatingIndex >= INDEX_AUTO_INCREMENT_CODE) {
          throw std::runtime_error("The index \"" + splitFilename[0] + "\" of the file \"" + file.path + "\" is not valid.");
        }


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
            personas.push_back({&origins.back(), folder[3], &folder}); // This is the place where I learned that std::vectors don't support pointers
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

        // Split the path into parts: index_tags_.extension
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


      console << SUBLINE << "Configuring portrayals/personas by origin";
      for (Origin& origin : origins) {
        portrayalsByOrigin[&origin] = {};
        personasByOrigin[&origin] = {};
      }


      console << SUBLINE << "Configuring portrayals/origins by persona";
      for (Persona& persona : personas) {
        portrayalsByPersona[&persona] = {};
        personasByOrigin[origin_exists(persona.origin->name)].push_back(&persona);
      }


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

        if (itsPortrayals.empty()) {
          continue;
        }

        std::deque<Portrayal*> sortedByIndexPortrayals = itsPortrayals;
        std::sort(sortedByIndexPortrayals.begin(), sortedByIndexPortrayals.end(), [](Portrayal* a, Portrayal* b) {
          return a->index < b->index;
        });


        index_t nextExpectedIndex = 1;
        for (Portrayal* portrayal : sortedByIndexPortrayals) {

          if (portrayal->index != nextExpectedIndex) {
            console << SUBSUBLINE << "Gap between " << nextExpectedIndex << " and " << portrayal->index;
          }

          ++nextExpectedIndex;
        }


        index_t nextExceptedIndex = 1;
        while (nextExceptedIndex <= itsPortrayals.size()) {

          if (sortedByIndexPortrayals[nextExceptedIndex - 1]->index != nextExceptedIndex) {

            console << SUBSUBLINE << "Changing index of " << sortedByIndexPortrayals.back()->where->filename() << " from " << sortedByIndexPortrayals.back()->index << " to " << nextExceptedIndex;
            change_portrayal_index(sortedByIndexPortrayals.back(), nextExceptedIndex);

            std::sort(sortedByIndexPortrayals.begin(), sortedByIndexPortrayals.end(), [](Portrayal* a, Portrayal* b) {
              return a->index < b->index;
            });
          }

          ++nextExceptedIndex;
        }
      }
    }



    void refresh() {
      /*
        This function refreshes the program by clearing all the containers
        and re-adding the content. This is useful when the order of the
        portrayals is disrupted.
      */

      console << NEXT << "Refreshing the program";

      folders.clear();
      files.clear();
      origins.clear();
      personas.clear();
      portrayals.clear();
      unsortedPortrayalsPaths.clear();

      portrayalsByOrigin.clear();
      portrayalsByPersona.clear();
      portrayalsByTag.clear();
      portrayalsByType.clear();
      personasByOrigin.clear();

      // Setup
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


        // Display data on the server
        localServer.server.Get("/updateplease", [this](const httplib::Request&, httplib::Response& res) {
          res.set_header("Access-Control-Allow-Origin", "*");
          res.set_content("Updating...", localServer.CONTENT_TYPE);
          refresh();
        });

        localServer.server.Get("/", [this](const httplib::Request&, httplib::Response& res) {
          res.set_header("Access-Control-Allow-Origin", "*");
          res.set_content(localServer.currentOutput, localServer.CONTENT_TYPE);
          console << "Sent: " << localServer.currentOutput << '\n';
        });

        // Add a route that receives a POST request
        localServer.server.Post("/post", [&](const httplib::Request& req, httplib::Response& res) {
          res.set_header("Access-Control-Allow-Origin", "*");
          res.set_content(req.body, localServer.CONTENT_TYPE);
          localServer.lastInput = req.body;
          console << "Received: " << localServer.lastInput << '\n';
        });

        // Start the local server
        localServer.start();
      }
  };
};
