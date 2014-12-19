#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <map>
#include <string>
#include <mutex>

class settings {
public:

  //template<typename _T>
  static int get(std::string key);
private:
  int finder(std::string key);
  static settings& self();
  settings();
  settings(const settings&);
  settings& operator=(const settings&);
  std::map<std::string,int> store;
  std::mutex mu;
};

#endif
