#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> child;
    bool isEndofWord = false;
};

class Trie {
    TrieNode* root = new TrieNode;
public:
    void insert(const string&);
    Trie() {};
};

void Trie::insert(const string& s) {
    TrieNode* curr = root;
    if (curr == nullptr) {
        return;
    }
    for (auto x : s) {
        if (curr->child.count(x) == 0) {
            curr->child[x] = new TrieNode;
        }
        curr = curr->child[x];
    }
    curr->isEndofWord = true;
}


void readFile(std::string FILENAME)
{
    Trie *trie = new Trie();
    std::ifstream file(FILENAME);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            //add line to trie
            trie->insert(line);
        }
        file.close();
    }
    
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
    cout << "finished populating trie " << physMemUsedByMe << endl;

}


int main()
{
    readFile("LargeInputFile.txt");
}
