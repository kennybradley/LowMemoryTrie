/*
Demonstration of a low memory Trie
   In x86 compiled mode this uses :
        a 4 byte pointer to an array of TrieNodes
        1 byte for the letter being expanded
        1 byte to count the number of children

Each fresh node uses 6 bytes and only adds data to the when a new child is added, never allocating more than it needs.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#ifdef _WIN32 
    #include "windows.h"
    #include "psapi.h"
#endif

using namespace std;



struct TrieNode {
    TrieNode* children = NULL;
    char letter;
    char numChildren = 0;
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

        bool found = false;
        //loop through the available children and search for the next letter in the trie
        //if the letter is not found, it needs to be added
        for (int childCount = 0; childCount < curr->numChildren; ++childCount)
        {
            //if the letter is found, update the current path and exit the loop
            if (x == curr->children[childCount].letter)
            {
                curr = &curr->children[childCount];
                found = true;
                childCount = curr->numChildren;
            }
        }

        if (!found)
        {
            /*
            low memory trie design
                create a new block of memory
                copy over the existing children
                add the new child to the array
            Then update the current node
            */
            TrieNode* temp = new TrieNode[curr->numChildren + 1];
            memcpy(temp, curr, curr->numChildren * sizeof(TrieNode));
            if (curr->numChildren > 0)
                delete curr->children;
            temp[curr->numChildren].letter = x;
            curr->children = temp;
            curr = &temp[curr->numChildren];
        }
    }
}


/*
Read line by line from the given file.
Insert the lines into the trie

*/
void readFile(std::string FILENAME)
{
    Trie* trie = new Trie();

    std::ifstream file(FILENAME);
    if (file.is_open()) {
        std::string line;

        while (getline(file, line)) {
            //add line to trie
            trie->insert(line);
        }
        file.close();
    }

#ifdef _WIN32 
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
    cout << "finished populating trie " << physMemUsedByMe << endl;
#endif
}

//well over 10GB using the standard trie
//over 11GB using unordered map version
//using hyper optimized version



int main()
{
    //2.2GB input file
    readFile("C:\\Users\\Kenny\\Desktop\\twitter\\merge.txt");
    return 0;
}
