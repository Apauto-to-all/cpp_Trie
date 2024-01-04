#include"pu.h"

const int cn = 52 + 3; // 指针数组的数量
typedef struct {
	char c; //字母
	string zh; //中文意思
}TrieElem;

typedef struct TrieNode {
	TrieElem data;
	struct TrieNode* abc[cn] = {nullptr};
}TrieNode, * Trie;