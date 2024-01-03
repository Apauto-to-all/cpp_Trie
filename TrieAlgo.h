#include"TrieDef.h"



// charת��Ϊint
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

// ���뵥��
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

// ��ȷ���ҵ����Ƿ����
bool isIn(Trie T, string word) {
    for (char ch : word) {
        int index = charToint(ch);
        if (T->abc[index] == nullptr) {
            // ���ʲ�����
            return false;
        }
        T = T->abc[index];
    }
    if (T->data.zh.empty()) return false; //����Ϊ�գ�Ҳ������
    cout << word << "��" << T->data.zh << endl;
    return true;
}

// ɾ�����ʵķ���
bool deleteWord(Trie& T, string word) {
    TrieNode* p = T;
    // �������ʵ���ĸ
    for (char ch : word) {
        int index = charToint(ch);
        if (p->abc[index] == nullptr) {
            // ���ʲ�����
            return false;
        }
        p = p->abc[index];
    }
    if (p->data.zh.empty()) return false; //����Ϊ�գ�Ҳ������
    cout << word << "��" << p->data.zh << endl;
    p->data.zh = "";
    return true;
}

// ��ӵ��ʵķ���
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


static int wordN = 0; // ���浥�ʸ���
static bool isEnough = false; // ��־�����ж��Ƿ��㹻
static bool isAll = false; // ��ʶ�����ж��Ƿ�������е���
static int maxShow = 25;  // ����ÿ����ʾ��һ�鵥���������
static int shown = 0;  // �Ѿ���ʾ�ĵ�������

// ��������������ռ����е���
void deepSearchWord(Trie T, string Prefix) {
    if (isEnough || T == nullptr) {
        return;
    }
    if (!T->data.zh.empty()) {
        // �����ǰ�ڵ�洢��һ�����ʣ��������+����
        cout << Prefix << "��" << T->data.zh << endl;
        wordN++;
        shown++;
        if (!isAll && shown % maxShow == 0) {
            cout << "-------------------------------" << endl;
            string s;
            cout << "�س��鿴��һ��" << maxShow << "�����ʣ����룺q--�˳���all--�鿴ʣ�µ�ȫ��������--������һ�鵥�ʵ���������";
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
    // ���������������
    for (int i = 0; i < 52; i++) {
        if (T->abc[i] != nullptr) {
            deepSearchWord(T->abc[i], Prefix + T->abc[i]->data.c);
        }
    }
}

// ���Ҿ�����ͬǰ׺�����е���
void searchWords(Trie T , string prefix) {
    wordN = 0;
    isEnough = false;
    isAll = false;
    shown = 0;
    for (char ch : prefix) {
        int index = charToint(ch);
        if (index == -1 || T->abc[index] == nullptr) {
            // ���ʲ�����
            cout << "����ʧ��" << endl;
            return;
        }
        T = T->abc[index];
    }
    // ����ǰ׺�������������������������е���
    deepSearchWord(T, prefix);
    // ͳ�Ƶ��ʸ���
    cout << "\nһ����" << wordN << "������\n" << endl;
}

void inTrie(Trie& T, string path) {
    // ��csv��txt�ļ�
    ifstream file(path);

    // ����ļ��Ƿ�ɹ���
    if (!file.is_open()) {
        cout << "�޷��򿪣�" << path << "�ļ�" << endl;
        return;
    }
    // ���ж�ȡ�ļ�
    string line;
    while (getline(file, line)) {
        // ʹ���ַ���������ÿһ��
        istringstream ss(line);
        string word;
        string translation;

        // ���ŷָ�������
        if (getline(ss, word, ',') && getline(ss, translation, ',')) {
            if (!insert(T, word, translation)) cout << word << " \t������������ʧ��" << endl;
        }
        else {
            // ����ʧ�ܣ����������Ϣ
            cout << "����ʧ�ܣ�" << line << endl;
        }
    }
    // �ر��ļ�
    file.close();
}



// �����ֵ������ı��ļ�
void saveTrie(Trie T, ofstream& out, string word = "") {
    if (T == nullptr) {
        return;
    }
    if (!T->data.zh.empty()) {
        // �����ǰ�ڵ�洢��һ�����ʣ����浥��+����
        out << word << "," << T->data.zh << "\n";
    }
    // ���������������
    for (int i = 0; i < 52; i++) {
        if (T->abc[i] != nullptr) {
            saveTrie(T->abc[i], out, word + T->abc[i]->data.c);
        }
    }
}

// ���ı��ļ������ֵ���
TrieNode* loadTrie(ifstream& in) {
    Trie T = new TrieNode;
    // ����ļ��Ƿ�ɹ���
    if (!in.is_open()) {
        cout << "�޷��򿪣�" << "" << "�ļ���Ĭ��Ϊ�½��ֵ���" << endl;
        return T;
    }
    // ���ж�ȡ�ļ�
    string line;
    while (getline(in, line)) {
        // ʹ���ַ���������ÿһ��
        istringstream ss(line);
        string word;
        string translation;

        // ���ŷָ�������
        if (getline(ss, word, ',') && getline(ss, translation, ',')) {

            if (!insert(T, word, translation)) cout << word << "��" << translation << " \t������������ʧ��" << endl;
        }
        else {
            // ����ʧ�ܣ����������Ϣ
            cout << "����ʧ�ܣ�" << line << endl;
        }
    }
    // �ر��ļ�
    in.close();
    return T;
}


// ����
int saveT(Trie T, string filename) {
    try {
        // �����ֵ������ļ�
        ofstream out(filename);
        saveTrie(T, out); // ���ñ��溯��
        out.close(); // �ر�����ļ���
        return 1;
    }
    catch (exception e) {
        cout << "�޷�����" << filename << "�ֵ���" << endl;
        cout << "������ϢΪ��" << e.what() << endl;
        return 0;
    }
}

// ����
int loadT(Trie& T, string filename) {
    try {
        ifstream in(filename);
        T = loadTrie(in); // ���ü��غ���
        in.close(); // �ر������ļ���
        return 1;
    }
    catch (exception e) {
        cout << "�޷�����"<< filename <<"�ֵ���" << endl;
        cout << "������ϢΪ��" << e.what() << endl;
        return 0;
    }
}

// �Զ�����
int auto_loadT(Trie& T, string filename) {
    try {
        ifstream in(filename);
        // ����ļ��Ƿ�ɹ���
        if (!in.is_open()) {
            return 0;
        }
        // ���ж�ȡ�ļ�
        string line;
        while (getline(in, line)) {
            // ʹ���ַ���������ÿһ��
            istringstream ss(line);
            string word;
            string translation;
            // ����ÿ������-����
            if (getline(ss, word, ',') && getline(ss, translation, ',')) insert(T, word, translation);
        }
        in.close();
        return 1;
    }
    catch (exception e) {
        return 0;
    }
}