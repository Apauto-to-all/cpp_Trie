#include"pu.h"

typedef struct {
	char c; //��ĸ
	string zh; //������˼
}TrieElem;

typedef struct TrieNode {
	TrieElem data;
	struct TrieNode* abc[52] = {nullptr};
}TrieNode, * Trie;
