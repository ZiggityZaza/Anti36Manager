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

#include "resources/a36mtagmap.hpp"
#include "resources/cslib.h++" // Custom library for Anti36Manager and contains all used libraries



#if __cplusplus < 202002L
#error This program requires C++20
#endif

#ifndef _WIN32
#error This program is only for Windows
#endif



namespace Anti36Manager {
// This namespace contains all the necessary classes, variables and whatnot for the A36M

// Console styling
#define NEXT_METHOD   "\n\n >> " // Entering new section
#define OCCURANCE     "\n >> "   // Standalone operation
#define SUBLINE       "\n  > "   // Next operation inside a method
#define SUBSUBLINE    "\n   > "  // Iteration inside a loop inside a method
#define SUBSUBSUBLINE "\n    > " // Another iteration in...

// Default values and Configs
cslib::DualOutput console("F:\\log.txt");
using index_t = unsigned short;

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
static constexpr const char* ANTI36_FOLDER = "F:\\Anti36Local";
static constexpr const char* UNSORTED_FOLDER_PATH = "F:\\$unsorted";
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
#define TAG_COMBINATIONS const auto& [tagAsChar, tagMeaning] : TAGS_LOOKUP


class LocalServer {
  public:
    static constexpr uint16_t LISTENING_PORT = 8080;
    static constexpr const char* CONTENT_TYPE = "application/json";
    std::string lastInput;
    httplib::Server server;

    ~LocalServer() {server.stop();}

    void start() {
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
  std::unordered_map<Origin*, std::deque<Persona*>> personasByOrigin;
  std::unordered_map<Persona*, std::deque<Portrayal*>> portrayalsByPersona;
  std::unordered_map<char, std::deque<Portrayal*>> portrayalsByTag;
  std::unordered_map<MediaType, std::deque<Portrayal*>> portrayalsByType;
  /*
    Note: The order of the portrayals in the deques aren't the same
    as it is in the windows persona folder as
    std::filesystem::recursive_directory_iterator() sorts numbers
    differently than the windows explorer. f.e. "1_", "10_", "2_"
  */


  // Filter variables
  std::unordered_map<Origin*, std::deque<Persona*>> filterByPersona;
  std::deque<char> filterByTags;
  MediaType filterByType;
  std::deque<Portrayal*> filteredPortrayals;


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
  Origin* unconst_origin(const Origin *const origin) {
    for (Origin& originInQuestion : origins) {
      if (&originInQuestion == origin) {
        return &originInQuestion;
      }
    }
    throw std::runtime_error("The origin doesn't exist.");
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
  Persona* unconst_persona(const Persona *const persona) {
    for (Persona& personaInQuestion : personas) {
      if (&personaInQuestion == persona) {
        return &personaInQuestion;
      }
    }
    throw std::runtime_error("The persona doesn't exist.");
  }
  Portrayal PORTRAYAL_ERROR_TYPE = {0, &PERSONA_ERROR_TYPE, {}, nullptr};
  Portrayal* portrayal_exists(const index_t index, const Persona *const desecendingPersona) {
    for (Portrayal& portrayal : portrayals) {
      if (portrayal.index == index and portrayal.persona == desecendingPersona) {
        return &portrayal;
      }
    }
    return &PORTRAYAL_ERROR_TYPE;
  }



  bool tag_exists(const std::string_view tag) {
    for (TAG_COMBINATIONS) {
      if (TAGS_LOOKUP.at(tagAsChar) == tag) {
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

    portrayalInQuestion->where->move_to(newPath);
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

      else if (entry.type == cslib::VirtualPath::FILE) {
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
        throw std::runtime_error("The index \"" + splitFilename[0] + "\" of the file \"" + file.path + "\" ain't valid.");
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
          console << SUBSUBLINE << "with \"" << personas.back().name << '"';
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
    portrayalsByPersona.clear();
    portrayalsByTag.clear();
    portrayalsByType.clear();
    personasByOrigin.clear();

    console << SUBLINE << "Configuring personas by origin";
    for (Origin& origin : origins) {
      personasByOrigin[&origin] = {};
    }

    console << SUBLINE << "Configuring portrayals/origins by persona";
    for (Persona& persona : personas) {
      portrayalsByPersona[&persona] = {};
      personasByOrigin[unconst_origin(persona.origin)].push_back(&persona);
    }

    console << SUBLINE << "Configuring portrayals by tag";
    for (TAG_COMBINATIONS) {
      portrayalsByTag[tagAsChar] = {};
    }
    console << " (" << portrayalsByTag.size() << " tags)";

    console << SUBLINE << "Configuring portrayals by type";
    portrayalsByType[IMAGE] = {};
    portrayalsByType[VIDEO] = {};
    console << " (" << portrayalsByType.size() << " types)";

    console << SUBLINE << "Adding portrayals to the maps";
    for (Portrayal& portrayal : portrayals) {
      portrayalsByPersona[unconst_persona(portrayal.persona)].push_back(&portrayal);
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

      // TODO: Wasn't tested in a long time. std::sort might not work with the Portrayal struct
      std::deque<Portrayal*> sortedByIndexPortrayals = itsPortrayals;
      std::function<bool(Portrayal*, Portrayal*)> sortFunction = [](Portrayal* a, Portrayal* b) {
        return a->index < b->index;
      };
      std::sort(sortedByIndexPortrayals.begin(), sortedByIndexPortrayals.end(), sortFunction);


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

    console << NEXT_METHOD << "Refreshing the program";

    folders.clear();
    files.clear();
    origins.clear();
    personas.clear();
    portrayals.clear();
    unsortedPortrayalsPaths.clear();
    console << SUBLINE << "Cleared all the pillar containers";

    portrayalsByPersona.clear();
    portrayalsByTag.clear();
    portrayalsByType.clear();
    personasByOrigin.clear();
    console << SUBLINE << "Cleared all the easy-access containers";

    // Setup
    console << NEXT_METHOD;
    read_ANTI36_FOLDER();
    console << NEXT_METHOD;
    read_UNSORTED_FOLDER();
    console << NEXT_METHOD;
    check_folders();
    console << NEXT_METHOD;
    check_files();
    console << NEXT_METHOD;
    catagorize_A36L_folders();
    console << NEXT_METHOD;
    catagorize_files();
    console << NEXT_METHOD;
    sort_byXY_containers();
    console << NEXT_METHOD;
    full_duplicate_index_fix();
    console << NEXT_METHOD;
    full_index_gaps_fix();
    console << NEXT_METHOD << "Refreshed the program";
  }



  void move_and_integrate_portrayal(size_t currentLocationInUnsortedByIndex, Persona *const persona, const std::deque<char>& tags, index_t index) {
    /*
      Important note! Method takes care of:...only this method should be used for this purpose
        - Moving file from the unsorted folder to the persona folder
        - Removing the entry from the unsortedPortrayals deque
        - Integrating the new portrayals into the whole system
        - Shifting down portrayals if the index is not INDEX_AUTO_INCREMENT_CODE

      But syncing with front-end is the responsibility of the caller.
      Syncing is done by simply reloading
    */

    console << SUBLINE << "Moving and integrating " << unsortedPortrayalsPaths[currentLocationInUnsortedByIndex].filename();

    if (index == INDEX_AUTO_INCREMENT_CODE) {
      index = portrayalsByPersona[persona].size() + 1;
      console << SUBLINE << "Index is auto-incremented to " << index;
    } else {
      for (Portrayal* portrayal : portrayalsByPersona[persona]) {
        if (portrayal->index >= index) {
          portrayal->index++;
        }
      }
      console << SUBLINE << "Index is manually set to " << index;
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

    unsortedPortrayalsPaths[currentLocationInUnsortedByIndex].move_to(newPath);
    console << SUBSUBLINE << "Moved to " << newPath;

    files.push_back(unsortedPortrayalsPaths[currentLocationInUnsortedByIndex]);
    unsortedPortrayalsPaths.erase(unsortedPortrayalsPaths.begin() + currentLocationInUnsortedByIndex);
    console << SUBSUBLINE << "Moved entry from unsortedPortrayalsPaths[" << currentLocationInUnsortedByIndex << "] to files";

    portrayals.push_back({index, persona, tags, &files.back()});
    portrayalsByPersona[persona].push_back(&portrayals.back());
    for (char tag : tags) {
      portrayalsByTag[tag].push_back(&portrayals.back());
    }
    portrayalsByType[EXTENSION_TO_MEDIA.at(files.back().extension())].push_back(&portrayals.back());

    console << SUBSUBLINE << "Done. Integrated " << files.back().filename() << " as " << &portrayals.back();
  }



  void put_together_portrayal_remix_by_filter() {
    /*
      This function is used to filter the portrayals by the given parameters.
      The portrayals are then put together in a deque and returned.

      filterByType is exclusive. If it is set to MediaType::IMAGE, only images
      will be returned and vice versa.
    */

    console << "Putting together a collection of portrayals based on filterByXY variables";
    console << SUBLINE << "Filters by origin/persona:";
    for (const auto& [origin, itsPersonas] : filterByPersona) {
      console << SUBLINE << origin->name << ":";
      for (Persona* persona : itsPersonas) {
        console << SUBSUBLINE << persona->name;
      }
    }
    console << SUBLINE << "Filters by tags:";
    for (char tag : filterByTags) {
      console << SUBSUBLINE << TAGS_LOOKUP.at(tag);
    }
    console << SUBLINE << "Filter by type: ";
    switch (filterByType) {
      case MediaType::IMAGE: console << "Image"; break;
      case MediaType::VIDEO: console << "Video"; break;
      case MediaType::NONE: console << "None"; break;
      case MediaType::BOTH: console << "Both"; break;
    }

    filteredPortrayals.clear();

    for (Portrayal& portrayal : portrayals) {
      if (cslib::do_these_deques_have_something_in_similar(filterByTags, portrayal.tags)) {
        filteredPortrayals.push_back(&portrayal);
        continue;
      }

      if (!filterByPersona.empty()) {
        for (const auto& [origin, itsPersonas] : filterByPersona) {
          if (cslib::does_this_exist_in_deque(itsPersonas, unconst_persona(portrayal.persona))) {
            filteredPortrayals.push_back(&portrayal);
            break;
          }
        }
      }
    }

    // Remove the portrayals that don't match the filterByType
    if ((filterByType != MediaType::NONE or filterByType != MediaType::BOTH) and !filteredPortrayals.empty()) {
      for (size_t posInDeque; posInDeque < filteredPortrayals.size(); ++posInDeque) {
        if (EXTENSION_TO_MEDIA.at(filteredPortrayals[posInDeque]->where->extension()) != filterByType) {
          filteredPortrayals.erase(filteredPortrayals.begin() + posInDeque);
          --posInDeque;
        }
      }
    }

    // Remove the portrayals that don't match the filterByTag
    if (!filterByTags.empty() and !filteredPortrayals.empty()) {
      for (size_t posInDeque; posInDeque < filteredPortrayals.size(); ++posInDeque) {
        if (!cslib::do_these_deques_have_something_in_similar(filterByTags, filteredPortrayals[posInDeque]->tags)) {
          filteredPortrayals.erase(filteredPortrayals.begin() + posInDeque);
          --posInDeque;
        }
      }
    }
  }



  public:
    explicit Main() {

      // Setup
      console << NEXT_METHOD;
      read_ANTI36_FOLDER();
      console << NEXT_METHOD;
      read_UNSORTED_FOLDER();
      console << NEXT_METHOD;
      check_folders();
      console << NEXT_METHOD;
      check_files();
      console << NEXT_METHOD;
      catagorize_A36L_folders();
      console << NEXT_METHOD;
      catagorize_files();
      console << NEXT_METHOD;
      sort_byXY_containers();
      console << NEXT_METHOD;
      full_duplicate_index_fix();
      console << NEXT_METHOD;
      full_index_gaps_fix();


      #define CATCH_ERROR_CONTENT catch(const std::exception& e){res.set_content("{\"message\":\""+std::string(e.what())+"\"}",localServer.CONTENT_TYPE);console<<OCCURANCE<<"Error:"<<e.what();}

      localServer.server.Get("/", [this](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        try {
          refresh();
          res.set_content("{\"message\": \"Cleared and re-added data\"}", localServer.CONTENT_TYPE);
        } CATCH_ERROR_CONTENT
      });



      localServer.server.Get("/anti36local", [this](const httplib::Request&, httplib::Response& res) {
        /*{
        "Anti36Local": {
          "Origin 1": {
            "Persona 1": {
              1: {
                path: "E:\\Anti36Local\\Origin 1\\Persona 1\\1_ABCD_.jpg",
                tags: ["_A", "_B", "_C", "_D_"]
              },
              2: {
                path: "E:\\Anti36Local\\Origin 1\\Persona 1\\2_EFGH_.jpg",
                tags: ["_E", "_F", "_G", "_H_"]
              },
              ...
            },
            "Persona 2": {
              ...
            },
            ...
          },
          "Origin 2": {
            ...
          },
          ...
          }
        }*/

        res.set_header("Access-Control-Allow-Origin", "*");

        try {
          nlohmann::json output;
          output["Anti36Local"] = {};
          for (Origin& origin : origins) {
            output["Anti36Local"][origin.name] = {};
            for (Persona* persona : personasByOrigin[&origin]) {
              output["Anti36Local"][origin.name][persona->name] = {};
              for (Portrayal* portrayal : portrayalsByPersona[persona]) {
                output["Anti36Local"][origin.name][persona->name][portrayal->index]["path"] = portrayal->where->path;
                for (char tag : portrayal->tags) {
                  output["Anti36Local"][origin.name][persona->name][portrayal->index]["tags"].push_back(TAGS_LOOKUP.at(tag));
                }
              }
            }
          }
          console << OCCURANCE << "\"/anti36local\" as GET";
          res.set_content(output.dump(), localServer.CONTENT_TYPE);
        } CATCH_ERROR_CONTENT
      });



      localServer.server.Get("/existing_tags", [this](const httplib::Request&, httplib::Response& res) {
        // ["_A", "_B",..., "_Z", "_a", "_b",..., "_z", "_0", "_1",..., "_9"]

        res.set_header("Access-Control-Allow-Origin", "*");

        nlohmann::json output;
        for (TAG_COMBINATIONS) {
          output.push_back(tagMeaning);
        }

        console << OCCURANCE << "\"/existing_tags\" as GET";
        res.set_content(output.dump(), localServer.CONTENT_TYPE);
      });



      localServer.server.Get("/unsorted", [this](const httplib::Request&, httplib::Response& res) {
        /*
        ["E:\\$unsorted\\someImage.jpg","E:\\$unsorted\\someVideo.mp4",...
        "E:\\$unsorted\\someOtherImage.png","E:\\$unsorted\\someGif.mp4"]
        */

        res.set_header("Access-Control-Allow-Origin", "*");

        std::string output = "[";
        for (const cslib::VirtualPath& path : unsortedPortrayalsPaths) {
          output += '"';
          output += cslib::escape_string(path.path);
          output += "\",";
        }
        if (!unsortedPortrayalsPaths.empty()) {
          output.pop_back();
        }
        output += ']';

        console << OCCURANCE << "\"/unsorted\" as GET";
        res.set_content(output, localServer.CONTENT_TYPE);
      });



      localServer.server.Post("/sort_please", [this](const httplib::Request& req, httplib::Response& res) {
        /*
          {
            "currentLocationInUnsortedByIndex": 2, ("E:\\$unsorted\\someImage.jpg")
            "origin": "Origin 1",
            "persona": "Persona 1",
            "tags": ["_A", "_B", "_C", "_D"]
          }
        */

        res.set_header("Access-Control-Allow-Origin", "*");
        console << OCCURANCE << "\"/sort_please\" as POST";
        
        try {
          nlohmann::json input = nlohmann::json::parse(req.body);

          size_t currentLocationInUnsortedByIndex = input["currentLocationInUnsortedByIndex"].get<size_t>();
          if (currentLocationInUnsortedByIndex >= unsortedPortrayalsPaths.size()) {
            cslib::crash("The index " + std::to_string(currentLocationInUnsortedByIndex) + " is out of bounds.");
          }

          Persona* persona = persona_exists(input["persona"], origin_exists(input["origin"]));
          if (persona == &PERSONA_ERROR_TYPE) {
            cslib::crash("The persona \"" + input["persona"].get<std::string>() + "\" from the origin \"" + input["origin"].get<std::string>() + "\" doesn't exist.");
          }

          std::deque<char> tags;
          for (const std::string& tag : input["tags"]) {
            for (TAG_COMBINATIONS) { // Reverse lookup
              if (tagMeaning == tag) {
                tags.push_back(tagAsChar);
                break;
              }
            }
          }
          if (tags.empty()) {
            tags.push_back('0');
          }

          move_and_integrate_portrayal(currentLocationInUnsortedByIndex, persona, tags, INDEX_AUTO_INCREMENT_CODE);
          res.set_content("{\"message\": \"Moved and integrated the portrayal\"}", localServer.CONTENT_TYPE);
        } CATCH_ERROR_CONTENT
      });



      localServer.server.Get("/current_portrayal_remix", [this](const httplib::Request&, httplib::Response& res) {
        /*
          ["E:\\Anti36Local\\Origin 1\\Persona 1\\1_ABCD_.jpg","E:\\Anti36Local\\Origin 1\\Persona 1\\2_EFGH_.jpg",...]
        */
        res.set_header("Access-Control-Allow-Origin", "*");

        std::unordered_map<Persona*, std::deque<Portrayal*>> filteredPortrayalsSortedTempMap;
        for (Portrayal* portrayal : filteredPortrayals) {
          filteredPortrayalsSortedTempMap[unconst_persona(portrayal->persona)].push_back(portrayal);
        }

        std::deque<Portrayal*> filteredPortrayalsSortedByIndex;
        for (const auto& [persona, itsPortrayals] : filteredPortrayalsSortedTempMap) {
          size_t highestIndex = 0;
          for (Portrayal* portrayal : itsPortrayals) {
            if (portrayal->index > highestIndex) {
              highestIndex = portrayal->index;
            }
          }
          for (index_t index = 1; index <= highestIndex; ++index) {
            for (Portrayal* portrayal : itsPortrayals) {
              if (portrayal->index == index) {
                filteredPortrayalsSortedByIndex.push_back(portrayal);
              }
            }
          }
        }

        try {
          std::string output = "[";
          for (Portrayal* portrayal : filteredPortrayalsSortedByIndex) {
            output += '"';
            output += cslib::escape_string(portrayal->where->path);
            output += "\",";
          }
          if (!filteredPortrayalsSortedByIndex.empty()) {
            output.pop_back();
          }
          output += "]";
          console << OCCURANCE << "\"/current_portrayal_remix\" as GET";
          res.set_content(output, localServer.CONTENT_TYPE);
        } CATCH_ERROR_CONTENT
      });



      localServer.server.Post("/remix_please", [this](const httplib::Request& req, httplib::Response& res) {
        /*
          {
            "filterByPersonas": {
              "Origin 1": ["Persona 1", "Persona 2",...],
              "Origin 2": ["Persona 1", "Persona 2",...],
              ...
            },
            "filterByTags": ["_A", "_B", "_C", "_D",...],
            "filterByType": "Image" (or "Video" for vids, "" for both)
          }
        */

        res.set_header("Access-Control-Allow-Origin", "*");
        console << OCCURANCE << "\"/remix_please\" as POST";

        try {
          nlohmann::json input = nlohmann::json::parse(req.body);

          filterByPersona.clear();
          filterByTags.clear();
          filterByType = MediaType::BOTH;
          filteredPortrayals.clear();

          for (const auto& [origin, personas] : input["filterByPersonas"].items()) {
            for (const std::string& persona : personas) {
              filterByPersona[origin_exists(origin)].push_back(persona_exists(persona, origin_exists(origin)));
            }
          }

          for (const std::string& filterByTag : input["filterByTags"]) { // Reverse lookup
            for (TAG_COMBINATIONS) {
              if (tagMeaning == filterByTag) {
                filterByTags.push_back(tagAsChar);
                break;
              }
            }
          }

          filterByType = input["filterByType"] == "Image" ? IMAGE : input["filterByType"] == "Video" ? VIDEO : NONE;

          console << OCCURANCE;
          put_together_portrayal_remix_by_filter();
          res.set_content("{\"message\": \"Here is the remix you asked for\"}", localServer.CONTENT_TYPE);
        } CATCH_ERROR_CONTENT
      });

      

      console << NEXT_METHOD << "Starting local server";
      localServer.start();
      console << ASCII_ART;
    }
};
};



int main() {
  Anti36Manager::Main main;
}
