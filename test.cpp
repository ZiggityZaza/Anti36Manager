#include <iostream>

static constexpr const char* cmd = R"(
 >> Based on your filters, a collection of portrayals will be put together. Have fun!
  > How to set filters:
   > 'persona' -> select a persona from a specific origin. You can also use '*' for all personas from that origin.
   > 'tag' -> select a tag(s)
   > 'type' -> select a portrayal type (image or video)
  > Other commands:
   > 'clear' -> reset all filters
   > 'exit' or *enter* -> exit without saving
   > 'save' -> save and exit
   > 'reveal' -> show the current filters and how many portrayals fit them
  > persona

Available origins (with each's amount of personas):
---------------------------------------------------------------------------------------------------
O1 (2) O2 (2) O3 (2)
Pick an origin to reveal it's personas >