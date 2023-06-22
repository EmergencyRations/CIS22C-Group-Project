#ifndef GROUP_PROJECT_HASHTABLE_H_
#define GROUP_PROJECT_HASHTABLE_H_

#include <algorithm>
#include <string>

#include "HashNode.h"

template <typename T>
class HashTable {
  int size;
  int count;
  int noCollisions;
  int longestCollisionPath;
  HashNode<T>* hashAry;

  // Hash function
  [[nodiscard]] int hash(const std::string &key) const { return key.length() % size; }

 public:
  HashTable() : size(25), count(0), noCollisions(0), longestCollisionPath(0) {
    hashAry = new HashNode<T>[size];
  };

  explicit HashTable(int tableSize) : size(tableSize), count(0), noCollisions(0), longestCollisionPath(0) {
    hashAry = new HashNode<T>[size];
  }

  ~HashTable() {
    delete[] hashAry;
  }

  // Insert a key into the hash table
  void insert(const T &item) {
    std::string key = item.getModel();
    int index = hash(key);

    while(hashAry[index].getOccupied()) {
      noCollisions++;
      index = (index + 1) % size;  // Linear probing
    }

    if (noCollisions > longestCollisionPath) {
      longestCollisionPath = noCollisions;
    }

    hashAry[index].setItem(item);
    hashAry[index].setOccupied(1);
    count++;

    noCollisions = 0;  // Reset count for next operation
  }

  // Delete a key from the hash table
  void remove(const std::string &key) {
    int index = hash(key);

    while (hashAry[index].getOccupied()) {
      if (hashAry[index].getItem().getModel() == key) {
        hashAry[index].setOccupied(-1);  // Deleted
        count--;
        return;
      }
      index = (index + 1) % size;  // Linear probing
    }
  }

  // Search for a key in the hash table
  bool search(const std::string &key) {
    int index = hash(key);

    while (hashAry[index].getOccupied()) {
      if (hashAry[index].getItem().getModel() == key) {
        return true;
      }
      index = (index + 1) % size;  // Linear probing
    }
    return false;
  }

  // Return the load factor of the hash table
  double loadFactor() { return static_cast<double>(count) / size; }

  // Return the total number of collisions
  int totalCollisions() { return longestCollisionPath; }

  // Return the longest collision path
  int longestCollisionPathLength() { return longestCollisionPath; }
};

#endif  //GROUP_PROJECT_HASHTABLE_H_
