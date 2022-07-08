#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "windows.h"
#include "psapi.h"

using namespace std;

const int ALPHABET_SIZE = 128;

// trie node
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (unsigned int i = 0; i < key.length(); i++)
    {
        int index = key[i];
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

/*
Read line by line from the given file.
Insert the lines into the trie

*/
void readFile(std::string FILENAME)
{
    TrieNode* trie = new TrieNode();
    cout << "test" << endl;
    std::ifstream file(FILENAME);
    int lineCount = 0;
    if (file.is_open()) {
        std::string line;

        while (getline(file, line)) {
            //add line to trie
            insert(trie, line);
            if (lineCount % 1000 == 0)
                cout << lineCount << endl;
            lineCount += 1;
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
    return 0;
}
