#ifndef GROUP_PROJECT_HASHTABLE_H_
#define GROUP_PROJECT_HASHTABLE_H_

#include <algorithm>
#include <string>

#include "HashNode.h"

template <typename T>
class HashTable {
  int size;
  int count;
  int collisions;
  int longestCollisionPath;
  HashNode<T>* hashAry;

  // Hash function
  [[nodiscard]] int hash(const std::string &key) const { return key.length() % size; }

 public:
  HashTable() : size(25), count(0), collisions(0), longestCollisionPath(0) {
    hashAry = new HashNode<T>[size];
  };

  explicit HashTable(int tableSize) : size(tableSize), count(0), collisions(0), longestCollisionPath(0) {
    hashAry = new HashNode<T>[size];
  }

  ~HashTable() {
    delete[] hashAry;
  }

  // Insert a key into the hash table
  void insert(const T &item) {
    std::string key = item.getMake();  // Assuming the "make" attribute is our key
    int index = hash(key);

    while(hashAry[index].getOccupied()) {
      collisions++;
      index = (index + 1) % size;  // Linear probing
    }

    if (collisions > longestCollisionPath) {
      longestCollisionPath = collisions;
    }

    hashAry[index].setItem(item);
    hashAry[index].setOccupied(1);
    count++;

    collisions = 0;  // Reset collisions count for next insert operation
  }

  // Delete a key from the hash table
  void remove(const std::string &key) {
    int index = hash(key);

    while (hashAry[index].getOccupied()) {
      if (hashAry[index].getItem().getMake() == key) {
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
      if (hashAry[index].getItem().getMake() == key) {
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
