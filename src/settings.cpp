#include <fstream>
#include <iostream>
#include <string>

#include "settings.h"

int
settings::finder(std::string key) {
  std::lock_guard<std::mutex> locker(mu);
  return store.find(key)->second;
}

int
settings::get(std::string key) {
  return self().finder(key);
}

settings::settings() {
  std::lock_guard<std::mutex> locker(mu);
  std::ifstream cin ("settings.conf", std::ifstream::in);
  do{
    std::string key;
    int value;

    getline(cin, key, ':');
    cin>>value;
    store[key]=value;
  }
  while(!cin.eof() and cin.get());
  cin.close();
}

settings&
settings::self() {
  static settings instance;
  return instance;
}
