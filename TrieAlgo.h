#include"TrieDef.h"



// char转化为int
int charToint(char ch) {
    if ('A' <= ch && ch <= 'Z') {
        return ch - 'A';
    }
    else if ('a' <= ch && ch <= 'z') {
        return ch - 'a' + 26;
    }
    else {
        return -1;
    }
}

// 插入单词
Status insert(Trie& T, string word, string meaning) {
    TrieNode* p = T;
    for (char ch : word) {
        int index = charToint(ch);
        if (index == -1) {
            return ERROR;
        }
        if (p->abc[index] == nullptr) {
            p->abc[index] = new TrieNode;
            p->abc[index]->data.c = ch;
        }
        p = p->abc[index];
    }
    p->data.zh = meaning;
    return OK;
}

// 精确查找单词是否存在
bool isIn(Trie T, string word) {
    for (char ch : word) {
        int index = charToint(ch);
        if (T->abc[index] == nullptr) {
            // 单词不存在
            return false;
        }
        T = T->abc[index];
    }
    if (T->data.zh.empty()) return false; //单词为空，也不存在
    cout << word << "：" << T->data.zh << endl;
    return true;
}

// 删除单词的翻译
bool deleteWord(Trie& T, string word) {
    TrieNode* p = T;
    // 遍历单词的字母
    for (char ch : word) {
        int index = charToint(ch);
        if (p->abc[index] == nullptr) {
            // 单词不存在
            return false;
        }
        p = p->abc[index];
    }
    if (p->data.zh.empty()) return false; //单词为空，也不存在
    cout << word << "：" << p->data.zh << endl;
    p->data.zh = "";
    return true;
}

// 添加单词的翻译
Status addZh(Trie& T, string word, string meaning) {
    TrieNode* p = T;
    for (char ch : word) {
        int index = charToint(ch);
        if (index == -1) {
            return ERROR;
        }
        if (p->abc[index] == nullptr) {
            p->abc[index] = new TrieNode;
            p->abc[index]->data.c = ch;
        }
        p = p->abc[index];
    }
    p->data.zh += meaning;
    return OK;
}


static int wordN = 0; // 储存单词个数
static bool isEnough = false; // 标志符，判断是否足够
static bool isAll = false; // 标识符，判断是否输出所有单词
static int maxShow = 25;  // 定义每次显示的一组单词最大数量
static int shown = 0;  // 已经显示的单词数量

// 深度优先搜索，收集所有单词
void deepSearchWord(Trie T, string Prefix) {
    if (isEnough || T == nullptr) {
        return;
    }
    if (!T->data.zh.empty()) {
        // 如果当前节点存储了一个单词，输出单词+翻译
        cout << Prefix << "：" << T->data.zh << endl;
        wordN++;
        shown++;
        if (!isAll && shown % maxShow == 0) {
            cout << "-------------------------------" << endl;
            string s;
            cout << "回车查看下一组" << maxShow << "个单词（输入：q--退出；all--查看剩下的全部；数字--设置下一组单词的数量）：";
            getline(cin, s);
            cout << "-------------------------------" << endl;
            if (s == "q") isEnough = true;
            else if (s == "all") isAll = true;
            else
            {
                try {
                    int new_max = stoi(s);
                    if (new_max > 0) {
                        shown = 0;
                        maxShow = new_max;
                    }
                }
                catch (exception){}
                system("cls");
            }
        }
    }
    // 继续深度优先搜索
    for (int i = 0; i < 52; i++) {
        if (T->abc[i] != nullptr) {
            deepSearchWord(T->abc[i], Prefix + T->abc[i]->data.c);
        }
    }
}

// 查找具有相同前缀的所有单词
void searchWords(Trie T , string prefix) {
    wordN = 0;
    isEnough = false;
    isAll = false;
    shown = 0;
    for (char ch : prefix) {
        int index = charToint(ch);
        if (index == -1 || T->abc[index] == nullptr) {
            // 单词不存在
            cout << "查找失败" << endl;
            return;
        }
        T = T->abc[index];
    }
    // 给定前缀，进行深度优先搜索，输出所有单词
    deepSearchWord(T, prefix);
    // 统计单词个数
    cout << "\n一共：" << wordN << "个单词\n" << endl;
}

void inTrie(Trie& T, string path) {
    // 打开csv、txt文件
    ifstream file(path);

    // 检查文件是否成功打开
    if (!file.is_open()) {
        cout << "无法打开：" << path << "文件" << endl;
        return;
    }
    // 逐行读取文件
    string line;
    while (getline(file, line)) {
        // 使用字符串流解析每一行
        istringstream ss(line);
        string word;
        string translation;

        // 逗号分隔符解析
        if (getline(ss, word, ',') && getline(ss, translation, ',')) {
            if (!insert(T, word, translation)) cout << word << " \t————插入失败" << endl;
        }
        else {
            // 解析失败，输出错误信息
            cout << "解析失败：" << line << endl;
        }
    }
    // 关闭文件
    file.close();
}



// 保存字典树到文本文件
void saveTrie(Trie T, ofstream& out, string word = "") {
    if (T == nullptr) {
        return;
    }
    if (!T->data.zh.empty()) {
        // 如果当前节点存储了一个单词，储存单词+翻译
        out << word << "," << T->data.zh << "\n";
    }
    // 继续深度优先搜索
    for (int i = 0; i < 52; i++) {
        if (T->abc[i] != nullptr) {
            saveTrie(T->abc[i], out, word + T->abc[i]->data.c);
        }
    }
}

// 从文本文件加载字典树
TrieNode* loadTrie(ifstream& in) {
    Trie T = new TrieNode;
    // 检查文件是否成功打开
    if (!in.is_open()) {
        cout << "无法打开：" << "" << "文件，默认为新建字典树" << endl;
        return T;
    }
    // 逐行读取文件
    string line;
    while (getline(in, line)) {
        // 使用字符串流解析每一行
        istringstream ss(line);
        string word;
        string translation;

        // 逗号分隔符解析
        if (getline(ss, word, ',') && getline(ss, translation, ',')) {

            if (!insert(T, word, translation)) cout << word << "：" << translation << " \t————加载失败" << endl;
        }
        else {
            // 解析失败，输出错误信息
            cout << "解析失败：" << line << endl;
        }
    }
    // 关闭文件
    in.close();
    return T;
}


// 保存
int saveT(Trie T, string filename) {
    try {
        // 保存字典树到文件
        ofstream out(filename);
        saveTrie(T, out); // 调用保存函数
        out.close(); // 关闭输出文件流
        return 1;
    }
    catch (exception e) {
        cout << "无法保存" << filename << "字典树" << endl;
        cout << "错误信息为：" << e.what() << endl;
        return 0;
    }
}

// 加载
int loadT(Trie& T, string filename) {
    try {
        ifstream in(filename);
        T = loadTrie(in); // 调用加载函数
        in.close(); // 关闭输入文件流
        return 1;
    }
    catch (exception e) {
        cout << "无法加载"<< filename <<"字典树" << endl;
        cout << "错误信息为：" << e.what() << endl;
        return 0;
    }
}

// 自动加载
int auto_loadT(Trie& T, string filename) {
    try {
        ifstream in(filename);
        // 检查文件是否成功打开
        if (!in.is_open()) {
            return 0;
        }
        // 逐行读取文件
        string line;
        while (getline(in, line)) {
            // 使用字符串流解析每一行
            istringstream ss(line);
            string word;
            string translation;
            // 加载每个单词-翻译
            if (getline(ss, word, ',') && getline(ss, translation, ',')) insert(T, word, translation);
        }
        in.close();
        return 1;
    }
    catch (exception e) {
        return 0;
    }
}