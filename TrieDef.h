#include"pu.h"

const int cn = 52 + 3; // ָ�����������
typedef struct {
	char c; //��ĸ
	string zh; //������˼
}TrieElem;

typedef struct TrieNode {
	TrieElem data;
	struct TrieNode* abc[cn] = {nullptr};
}TrieNode, * Trie;