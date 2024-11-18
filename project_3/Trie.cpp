#include "Trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


Trie::Trie() {
    root = new Node();
    size = 0;
}

Trie::~Trie() {
    delete root;    // delete all nodes
}

