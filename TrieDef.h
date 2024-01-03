#include"pu.h"

typedef struct {
	char c; //字母
	string zh; //中文意思
}TrieElem;

typedef struct TrieNode {
	TrieElem data;
	struct TrieNode* abc[52] = {nullptr};
}TrieNode, * Trie;
