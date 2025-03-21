#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

class trieRecursive {
private:
    static const int MAX_CHAR = 26;
    trieRecursive* child[MAX_CHAR];
    bool isLeaf{};
public:
    trieRecursive() {
        memset(child, 0, sizeof(child));
    }

    void insert(string str, int indx = 0) {
        if (indx == (int)str.size()) {
            isLeaf = 1;
        }
        else {
            int cur = str[indx] - 'a';

            if (child[cur] == 0) {
                child[cur] = new trieRecursive();
            }

            child[cur]->insert(str, indx + 1);
        }
    }

    bool wordExist(string str, int indx = 0) {
        if (indx == (int)str.size()) {
            return isLeaf;
        }

        int cur = str[indx] - 'a';

        if (!child[cur]) {
            return false;
        }

        return child[cur]->wordExist(str, indx + 1);
    }

    bool prefixExist(string str, int indx = 0) {
        if (indx == (int)str.size()) {
            return true;
        }

        int cur = str[indx] - 'a';

        if (!child[cur]) {
            return false;
        }

        return child[cur]->prefixExist(str, indx + 1);
    }
};

class trieIterative {
private:
    static const int MAX_CHAR = 26;
    trieIterative* child[MAX_CHAR];
    bool isLeaf{ };

public:
    trieIterative() {
        memset(child, 0, sizeof(child));
    }
    /* by reversing a string, we can trivially check for suffixes!
    reverse(str.begin(), str.end());
    */
    void insert(string str) {
        trieIterative* cur = this;

        for (int idx = 0; idx < (int)str.size(); ++idx) {
            int ch = str[idx] - 'a';

            if (!cur->child[ch]) {
                cur->child[ch] = new trieIterative();
            }

            cur = cur->child[ch];
        }
        cur->isLeaf = true;
    }

    bool wordExist(string str) {
        trieIterative* cur = this;

        for (int idx = 0; idx < (int)str.size(); ++idx) {
            int ch = str[idx] - 'a';

            if (!cur->child[ch]) {
                return false;
            }

            cur = cur->child[ch];
        }
        return cur->isLeaf;
    }

    string firstWordPrefix(const string& str) {
        trieIterative* cur = this;

        for (int indx = 0; indx < (int)str.size(); indx++) {
            int ch = str[indx] - 'a';

            if (!cur->child[ch]) {
                break;
            }

            if (cur->child[ch]->isLeaf) {
                return str.substr(0, indx + 1);
            }

            cur = cur->child[ch];
        }

        return str;
    }

    void getAllStrings(vector<string>&res, string currString=""){
        if(isLeaf){
            res.push_back(currString);
        }

        for(int i=0;i<CHAR_MAX;i++){
            if(child[i]){
                child[i]->getAllStrings(res, currString + (char) ( i + 'a'));
            }
        }
    }
    
    void autoComplete(const string &str ,vector<string>&res){
        trieIterative* cur = this;

        for (int idx = 0; idx < (int) str.size(); ++idx) {
			int ch = str[idx] - 'a';

			if (!cur->child[ch]){
				return;
            }
            
			cur = cur->child[ch];
		}
    }

    bool wordExistWithOneChange(string str) {
		// Brute force all possible 1-char change and search for it
		// O(L * 26 * L)
		for (int i = 0; i < (int) str.size(); ++i) {
			char cpy = str[i];

			for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == cpy){
					continue;
                }

				str[i] = ch;

				if (wordExist(str)){
					return true;}
			}
			str[i] = cpy;	// copy back
		}
		return false;
	}
};

class trieMapInt {
private:
    map<int, trieMapInt*>child;
    bool isLeaf{};
public:
    trieMapInt() {};

    void insert(string str) {
        trieMapInt* cur = this;

        for (int indx = 0; indx < (int)str.size(); indx++) {
            int ch = str[indx] - 'a';

            if (!cur->child.count(ch)) {
                cur->child[ch] = new trieMapInt();
            }

            cur = cur->child[ch];
        }

        cur->isLeaf = true;
    }

    bool word_exist(string str) {
        trieMapInt* cur = this;

        for (int idx = 0; idx < (int)str.size(); ++idx) {
            int ch = str[idx] - 'a';

            if (!cur->child.count(ch)) {
                return false;
            }

            cur = cur->child[ch];
        }
        return cur->isLeaf;
    }
};

class trieMapString {
private:
    // The major change: instead of letter on edge, it will be a string
    map<string, trieMapString*> child;

    bool isLeaf{ };

public:
    trieMapString() {
    }

    void insert(const vector<string>& path) {
        trieMapString* cur = this;

        for (int idx = 0; idx < (int)path.size(); ++idx) {

            if (!cur->child.count(path[idx])) {
                cur->child[path[idx]] = new trieMapString();
            }

            cur = cur->child[path[idx]];
        }
        cur->isLeaf = true;
    }

    bool subpath_exist(const vector<string>& path) {
        trieMapString* cur = this;

        for (int idx = 0; idx < (int)path.size(); ++idx) {
            if (!cur->child.count(path[idx])) {
                return false;
            }
            cur = cur->child[path[idx]];
        }
        return true;
    }
};

class MagicDictionary {
    public:
        trieIterative tree;
    
        MagicDictionary() {
    
        }
    
        void buildDict(vector<string> dictionary) {
            for (int i = 0; i < (int) dictionary.size(); ++i) {
                tree.insert(dictionary[i]);
            }
    
        }
    
        bool search(string str) {
            return tree.wordExistWithOneChange(str);
        }
    };
    

int main()
{
    

    return 0;
}
