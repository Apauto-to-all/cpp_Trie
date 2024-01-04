#include"TrieAlgo.h"

static string trieN = "�½��ֵ���";
const string trieDir = "saveTrie"; // �ֵ����ļ�λ��
const string dataDir = "loadData"; // ���ݼ����ļ���
const string loadPath = "autoLoad.txt"; // �Զ������ֵ������ļ�·��

// ��ȡ�ļ�·��
string GetAutoLoad(string loadPath) {
    ifstream f(loadPath);
    if (f.is_open()) {
        string s;
        getline(f, s);
        return s;
    }
    else {
        return "";
    }
}

// �Զ������ֵ���
void AutoLoad(Trie& T, string r = GetAutoLoad(loadPath)) {
    if (r == "") return;
    else
    {
        if (auto_loadT(T, trieDir + "/" + r)) {
            trieN = r;
        }
        else {
            T = new TrieNode;
        }
    }
}

// ����·��
void SavePath(string path) {
    ofstream out(loadPath, ios::trunc);
    if (out.is_open()) {
        out << path;
        out.close();
    }
}


void Show1() {
    cout << "========= �����ֵ��� =========" << endl;
    cout << "1. ʹ���½����ֵ���" << endl;
    cout << "2. ʹ���Ѵ�����ֵ���" << endl;
    cout << "0. ȡ������" << endl;
    cout << "���������ѡ��";
}
// �����ֵ���
void changeTrie(Trie &T) {
    system("cls");
    Show1();
    int choice;
    cin >> choice;
    while (choice < 0 || choice > 2 || cin.fail())
    {
        system("cls");
        cin.clear();
        cin.ignore();
        Show1();
        cin >> choice;
    }
    switch (choice) {
    case 1: {
        system("cls");
        T = new TrieNode;
        cout << "��ʹ���½����ֵ���" << endl;
        trieN = "�½��ֵ���";
        break;
    }
    case 2: {
        system("cls");
        cin.ignore();
        cin.clear();
        if (!exists(trieDir)) {
            try {
                create_directory(trieDir);
                cout << "����saveTrie�ֵ����ļ��гɹ������ȴ�������ֵ�������ʹ�ñ�����" << endl;
            }
            catch (exception e) {
                cout << "����saveTrie�ļ���ʧ��" << endl;
                cout << "������ϢΪ��" << e.what() << endl;
            }
        }
        else {
            try {
                int f = distance(directory_iterator(trieDir), directory_iterator{});
                if (f) {
                    vector<string> f_all(f);
                    int choice;
                    int i = 0;
                    for (auto& f : directory_iterator(trieDir)) {
                        // ����Ƿ�Ϊ�ļ�
                        if (is_regular_file(f)) {
                            f_all[i] = f.path().filename().string();
                            i++;
                            cout << i << "��" << f.path().filename().string() << endl;
                        }
                    }
                    cout << "�����ֵ�������ţ�0Ϊ��ѡ�񣩣�";
                    cin >> choice;
                    while (choice < 0 || choice > i || cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "�������������������ֵ�������ţ�";
                        cin >> choice;
                    }
                    if (choice) {
                        cout << "�ֵ�����" << f_all[choice - 1] << " \t���ڼ����С������Ե�" << endl;
                        if (loadT(T, trieDir + "/" + f_all[choice - 1])) {
                            cout << "�ֵ�����" << f_all[choice - 1] << "�����سɹ�" << endl;
                            trieN = f_all[choice - 1];
                            SavePath(trieN);
                        }
                    }
                    else cout << "��ȡ�������ֵ���" << endl;
                }
                else
                {
                    cout << "saveTrie�ֵ����ļ��������ļ������ȴ�������ֵ�������ʹ�ñ�����" << endl;
                }
            }
            catch (exception e) {
                cout << "�޷���saveTrie�ļ���" << endl;
                cout << "������ϢΪ��" << e.what() << endl;
            }
        }
        break;
    }
    case 0: {
        cout << "��ȡ�������ֵ���" << endl;
        break;
    }
    }
}

// ����Ŀǰ���ֵ���
void saveNowTrie(Trie T) {
    if (!exists(trieDir)) {
        try {
            create_directory(trieDir);
            cout << "����saveTrie�ֵ����ļ��гɹ�" << endl;
        }
        catch (exception e) {
            cout << "����saveTrie�ļ���ʧ��" << endl;
            cout << "������ϢΪ��" << e.what() << endl;
            return;
        }
    }
    if (trieN == "�½��ֵ���") {
        string n = "";
        cout << "�����봢���ֵ��������ƣ������ʽ��csv����";
        cin.clear();
        cin.ignore();
        getline(cin, n);
        n += ".csv";
        while (exists(trieDir + "/" + n)) { //�Ѵ��ڴ��ļ�
            cout << "��������ֵ��������Ѵ��ڣ����������룺";
            getline(cin, n);
            n += ".csv";
        }
        while (true)
        {
            cout << "-------------------------------" << endl;
            cout << "���Ƿ�ȷ���ֵ�������Ϊ��" << n << endl;
            char ch;
            cout << "Yes or No ��y or n����";
            cin >> ch;
            while (!(ch == 'y' || ch == 'Y' || ch == 'n' || ch ==  'N') || cin.fail())
            {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                }
                cout << "�����������������루y or n����";
                cin >> ch;
            }
            if (ch == 'y' || ch == 'Y') {
                break;
            }
            else {
                cout << "-------------------------------" << endl;
                cout << "���������봢���ֵ��������ƣ�";
                cin.clear();
                cin.ignore();
                getline(cin, n);
                n += ".csv";
                while (exists(trieDir + "/" + n)) { //�Ѵ��ڴ��ļ�
                    cout << "��������ֵ��������Ѵ��ڣ����������룺";
                    getline(cin, n);
                    n += ".csv";
                }
                continue;
            }
        }
        cout << "�ֵ�����" << n << " \t���ڱ����С������Ե�" << endl;
        if (saveT(T, trieDir + "/" + n)) {
            cout << "�ֵ�����" << n << "������ɹ�" << endl;
            trieN = n;
            SavePath(trieN);
        }
    }
    else
    {
        cout << "�ֵ�����" << trieN << " \t���ڱ����С������Ե�" << endl;
        if (saveT(T, trieDir + "/" + trieN)) {
            cout << "�ֵ�����" << trieN << "������ɹ�" << endl;
        }
    }
    
}

void Show2() {
    cout << "========= ���뵥�� =========" << endl;
    cout << "1. �ֶ����뵥��" << endl;
    cout << "2. ��csv��txt�ļ��в��뵥��" << endl;
    cout << "0. ȡ������" << endl;
    cout << "���������ѡ��";
}
// ���뵥��
void insertTrie(Trie& T) {
    system("cls");
    Show2();
    int choice;
    cin >> choice;
    while (choice < 0 || choice > 2 || cin.fail())
    {
        system("cls");
        cin.clear();
        cin.ignore();
        Show2();
        cin >> choice;
    }
    switch (choice) {
    case 1: {
        system("cls");
        cin.clear();
        cin.ignore();
        cout << "���뵥��+���ķ�����룬����q�˳�" << endl;
        while (true) {
            cout << "---------------------" << endl;
            string word, meaning;
            cout << "���뵥�ʣ�";
            getline(cin, word);
            if (word == "q") break;
            cout << "���뵥�ʷ��룺";
            getline(cin, meaning);
            if (meaning == "q") break;
            if (insert(T, word, meaning)) cout << "����ɹ�" << endl;
            else cout << "����ʧ��" << endl;
        }
        break;
    }
    case 2: {
        system("cls");
        cout << "ע�⣺" << endl;
        cout << "1.txt��csv�ļ�����һ��ӦΪ���ʣ��ڶ���Ϊ��Ӧ�����ķ��룬����֮����ʹ�ö��Ž��зָ" << endl;
        cout << "2.ע��txt��csv�ļ�����" << endl;
        cout << "3.���ʸ�ʽ֧�֣�ֻ�д�Сд��ĸ" << endl;
        cout << "4.�����ǰ�ֵ����Ѿ�������ͬ���ĵ��ʣ�Ĭ�ϸ��ǵ��ʵķ���" << endl;
        cout << "--------------------------------------------------------" << endl;
        if (!exists(dataDir)) {
            try {
                create_directory(dataDir);
                cout << "���������ļ��гɹ����뽫csv�ļ���txt�ļ������Ŀ¼��loadData�ļ����У���ʹ�ñ�����" << endl;
            }
            catch (exception e) {
                cout << "����loadData�ļ���ʧ��" << endl;
                cout << "������ϢΪ��" << e.what() << endl;
                return;
            }
        }
        else
        {
            try {
                int f = distance(directory_iterator(dataDir), directory_iterator{});
                if (f) {
                    vector<string> f_all(f);
                    int i = 0;
                    for (auto& f : directory_iterator(dataDir)) {
                        if (is_regular_file(f)) {
                            // ��ȡ��׺
                            string hz = f.path().extension().string();
                            transform(hz.begin(), hz.end(), hz.begin(), ::tolower); // Сдת��
                            // ����ļ��Ƿ�ΪCSV��TXT�ļ�
                            if (hz == ".csv" || hz == ".txt") {
                                f_all[i] = f.path().filename().string();
                                i++;
                                cout << i << "��" << f.path().filename().string() << endl;
                            }
                        }
                    }
                    if (i == 0) {
                        cout << "��Ŀ¼�µ�loadData�ļ�������csv�ļ���txt�ļ����޷�ʹ�ñ�����" << endl;
                        return;
                    }
                    cout << "����������뵥�ʵ��ļ���ţ�0Ϊȡ��ѡ�񣩣�";
                    int choice;
                    cin >> choice;
                    while (choice < 0 || choice > i || cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "�������������������ļ���ţ�";
                        cin >> choice;
                    }
                    if (choice) {
                        inTrie(T, dataDir + "/" + f_all[choice - 1]);
                        cout << "�ѽ���" << f_all[choice - 1] << "���еĵ��ʲ��뵽�ֵ���" << endl;
                    }
                    else cout << "��ȡ��" << endl;
                }
                else
                {
                    cout << "��Ŀ¼�µ�loadData�ļ�������csv�ļ���txt�ļ����޷�ʹ�ñ�����" << endl;
                }
            }
            catch (exception e) {
                cout << "�޷��򿪸�Ŀ¼�µ�loadData�ļ���" << endl;
                cout << "������ϢΪ��" << e.what() << endl;
            }
        }
        break;
    }
    case 0: {
        cout << "��ȡ������" << endl;
        break;
    }
    }
}



void ExitEnter() {
    cout << "-------------------------------" << endl;
    system("pause");
    system("cls");
}
void Show3() {
    cout << "========= �޸ĵ��ʼ��䷭�� =========" << endl;
    cout << "1. �޸ĵ��ʷ���" << endl;
    cout << "2. ��ӵ��ʷ���" << endl;
    cout << "3. ɾ������" << endl;
    cout << "0. ȡ������" << endl;
    cout << "���������ѡ��";
}
// �޸ĵ��ʼ��䷭��
void changeWord(Trie& T) {
    int choice;
    do {
        system("cls");
        Show3();
        cin >> choice;
        while (choice < 0 || choice > 3 || cin.fail())
        {
            system("cls");
            cin.clear();
            cin.ignore();
            Show3();
            cin >> choice;
        }
        switch (choice) {
        case 1: {
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "������Ҫ�޸ķ���ĵ���" << endl;
            cout << "---------------------" << endl;
            string word, meaning;
            cout << "���뵥�ʣ�";
            getline(cin, word);
            if (!isIn(T, word)) {
                cout << "���ҵ��õ��ʲ����ڣ��Ƿ���������������������µ���+����" << endl;
                cout << "����y���������������˳���";
                string c;
                getline(cin, c);
                if (c != "y") {
                    cout << "�Ѿ��˳�" << endl;
                    break;
                }
            }
            cout << "---------------------" << endl;
            cout << "���뵥�ʷ��룺";
            getline(cin, meaning);
            if (insert(T, word, meaning)) cout << "�ɹ�" << endl;
            else cout << "ʧ��" << endl;
            ExitEnter();
            break;
        }
        case 2: {
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "������Ҫ��Ӹķ���ĵ���" << endl;
            cout << "---------------------" << endl;
            string word, meaning;
            cout << "���뵥�ʣ�";
            getline(cin, word);
            if (!isIn(T, word)) {
                cout << "���ҵ��õ��ʲ����ڣ��Ƿ���������������������µ���+����" << endl;
                cout << "����y������ֱ�ӻس��˳���";
                string c;
                getline(cin, c);
                if (c != "y") {
                    cout << "�Ѿ��˳�" << endl;
                    break;
                }
            }
            cout << "---------------------" << endl;
            cout << "���뵥�ʷ��룺";
            getline(cin, meaning);
            if (addZh(T, word, meaning)) cout << "�ɹ�" << endl;
            else cout << "ʧ��" << endl;
            ExitEnter();
            break;
        }
        case 3: {
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "������Ҫɾ���ĵ���" << endl;
            cout << "---------------------" << endl;
            string word;
            cout << "���뵥�ʣ�";
            getline(cin, word);
            if (deleteWord(T, word)) cout << "ɾ���ɹ�" << endl;
            else cout << "��ȡ��" << endl;
            ExitEnter();
            break;
        }
        case 0: {
            cout << "��ȡ������" << endl;
            break;
        }
        }
    } while (choice != 0);
}