#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <string>

using namespace std;

struct sceneElementConfiguration
{
  string name;
  string size;
  string color;
};

class Configuration {
public:
  vector<string> libsConfiguration{};
  vector<sceneElementConfiguration> sceneConfiguration{};
};

#endif
