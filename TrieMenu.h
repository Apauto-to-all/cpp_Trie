#include"TrieAlgo.h"

static string trieN = "新建字典树";
const string trieDir = "saveTrie"; // 字典树文件位置
const string dataDir = "loadData"; // 数据加载文件夹
const string loadPath = "autoLoad.txt"; // 自动加载字典树的文件路径

// 获取文件路径
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

// 自动加载字典树
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

// 保存路径
void SavePath(string path) {
    ofstream out(loadPath, ios::trunc);
    if (out.is_open()) {
        out << path;
        out.close();
    }
}


void Show1() {
    cout << "========= 更换字典树 =========" << endl;
    cout << "1. 使用新建的字典树" << endl;
    cout << "2. 使用已储存的字典树" << endl;
    cout << "0. 取消操作" << endl;
    cout << "请输入你的选择：";
}
// 更换字典树
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
        cout << "已使用新建的字典树" << endl;
        trieN = "新建字典树";
        break;
    }
    case 2: {
        system("cls");
        cin.ignore();
        cin.clear();
        if (!exists(trieDir)) {
            try {
                create_directory(trieDir);
                cout << "创建saveTrie字典树文件夹成功，请先储存你的字典树，再使用本功能" << endl;
            }
            catch (exception e) {
                cout << "创建saveTrie文件夹失败" << endl;
                cout << "错误信息为：" << e.what() << endl;
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
                        // 检查是否为文件
                        if (is_regular_file(f)) {
                            f_all[i] = f.path().filename().string();
                            i++;
                            cout << i << "：" << f.path().filename().string() << endl;
                        }
                    }
                    cout << "输入字典树的序号（0为不选择）：";
                    cin >> choice;
                    while (choice < 0 || choice > i || cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "输入有误，请重新输入字典树的序号：";
                        cin >> choice;
                    }
                    if (choice) {
                        cout << "字典树：" << f_all[choice - 1] << " \t正在加载中……请稍等" << endl;
                        if (loadT(T, trieDir + "/" + f_all[choice - 1])) {
                            cout << "字典树：" << f_all[choice - 1] << "，加载成功" << endl;
                            trieN = f_all[choice - 1];
                            SavePath(trieN);
                        }
                    }
                    else cout << "已取消更换字典树" << endl;
                }
                else
                {
                    cout << "saveTrie字典树文件夹中无文件，请先储存你的字典树，再使用本功能" << endl;
                }
            }
            catch (exception e) {
                cout << "无法打开saveTrie文件夹" << endl;
                cout << "错误信息为：" << e.what() << endl;
            }
        }
        break;
    }
    case 0: {
        cout << "已取消更换字典树" << endl;
        break;
    }
    }
}

// 保存目前的字典树
void saveNowTrie(Trie T) {
    if (!exists(trieDir)) {
        try {
            create_directory(trieDir);
            cout << "创建saveTrie字典树文件夹成功" << endl;
        }
        catch (exception e) {
            cout << "创建saveTrie文件夹失败" << endl;
            cout << "错误信息为：" << e.what() << endl;
            return;
        }
    }
    if (trieN == "新建字典树") {
        string n = "";
        cout << "请输入储存字典树的名称（储存格式：csv）：";
        cin.clear();
        cin.ignore();
        getline(cin, n);
        n += ".csv";
        while (exists(trieDir + "/" + n)) { //已存在此文件
            cout << "你输入的字典树名称已存在，请重新输入：";
            getline(cin, n);
            n += ".csv";
        }
        while (true)
        {
            cout << "-------------------------------" << endl;
            cout << "你是否确认字典树名称为：" << n << endl;
            char ch;
            cout << "Yes or No （y or n）：";
            cin >> ch;
            while (!(ch == 'y' || ch == 'Y' || ch == 'n' || ch ==  'N') || cin.fail())
            {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                }
                cout << "输入有误，请重新输入（y or n）：";
                cin >> ch;
            }
            if (ch == 'y' || ch == 'Y') {
                break;
            }
            else {
                cout << "-------------------------------" << endl;
                cout << "请重新输入储存字典树的名称：";
                cin.clear();
                cin.ignore();
                getline(cin, n);
                n += ".csv";
                while (exists(trieDir + "/" + n)) { //已存在此文件
                    cout << "你输入的字典树名称已存在，请重新输入：";
                    getline(cin, n);
                    n += ".csv";
                }
                continue;
            }
        }
        cout << "字典树：" << n << " \t正在保存中……请稍等" << endl;
        if (saveT(T, trieDir + "/" + n)) {
            cout << "字典树：" << n << "，保存成功" << endl;
            trieN = n;
            SavePath(trieN);
        }
    }
    else
    {
        cout << "字典树：" << trieN << " \t正在保存中……请稍等" << endl;
        if (saveT(T, trieDir + "/" + trieN)) {
            cout << "字典树：" << trieN << "，保存成功" << endl;
        }
    }
    
}

void Show2() {
    cout << "========= 插入单词 =========" << endl;
    cout << "1. 手动插入单词" << endl;
    cout << "2. 从csv、txt文件中插入单词" << endl;
    cout << "0. 取消操作" << endl;
    cout << "请输入你的选择：";
}
// 插入单词
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
        cout << "输入单词+中文翻译插入，输入q退出" << endl;
        while (true) {
            cout << "---------------------" << endl;
            string word, meaning;
            cout << "输入单词：";
            getline(cin, word);
            if (word == "q") break;
            cout << "输入单词翻译：";
            getline(cin, meaning);
            if (meaning == "q") break;
            if (insert(T, word, meaning)) cout << "插入成功" << endl;
            else cout << "插入失败" << endl;
        }
        break;
    }
    case 2: {
        system("cls");
        cout << "注意：" << endl;
        cout << "1.txt、csv文件，第一列应为单词，第二列为对应的中文翻译，两列之间请使用逗号进行分割。" << endl;
        cout << "2.注意txt、csv文件编码" << endl;
        cout << "3.单词格式支持：只有大小写字母" << endl;
        cout << "4.如果当前字典树已经储存了同样的单词，默认覆盖单词的翻译" << endl;
        cout << "--------------------------------------------------------" << endl;
        if (!exists(dataDir)) {
            try {
                create_directory(dataDir);
                cout << "创建数据文件夹成功，请将csv文件和txt文件放入根目录下loadData文件夹中，再使用本功能" << endl;
            }
            catch (exception e) {
                cout << "创建loadData文件夹失败" << endl;
                cout << "错误信息为：" << e.what() << endl;
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
                            // 获取后缀
                            string hz = f.path().extension().string();
                            transform(hz.begin(), hz.end(), hz.begin(), ::tolower); // 小写转化
                            // 检查文件是否为CSV或TXT文件
                            if (hz == ".csv" || hz == ".txt") {
                                f_all[i] = f.path().filename().string();
                                i++;
                                cout << i << "：" << f.path().filename().string() << endl;
                            }
                        }
                    }
                    if (i == 0) {
                        cout << "根目录下的loadData文件夹中无csv文件或txt文件，无法使用本功能" << endl;
                        return;
                    }
                    cout << "请输入待插入单词的文件序号（0为取消选择）：";
                    int choice;
                    cin >> choice;
                    while (choice < 0 || choice > i || cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "输入有误，请重新输入文件序号：";
                        cin >> choice;
                    }
                    if (choice) {
                        inTrie(T, dataDir + "/" + f_all[choice - 1]);
                        cout << "已将：" << f_all[choice - 1] << "，中的单词插入到字典树" << endl;
                    }
                    else cout << "已取消" << endl;
                }
                else
                {
                    cout << "根目录下的loadData文件夹中无csv文件或txt文件，无法使用本功能" << endl;
                }
            }
            catch (exception e) {
                cout << "无法打开根目录下的loadData文件夹" << endl;
                cout << "错误信息为：" << e.what() << endl;
            }
        }
        break;
    }
    case 0: {
        cout << "已取消操作" << endl;
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
    cout << "========= 修改单词及其翻译 =========" << endl;
    cout << "1. 修改单词翻译" << endl;
    cout << "2. 添加单词翻译" << endl;
    cout << "3. 删除单词" << endl;
    cout << "0. 取消操作" << endl;
    cout << "请输入你的选择：";
}
// 修改单词及其翻译
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
            cout << "输入需要修改翻译的单词" << endl;
            cout << "---------------------" << endl;
            string word, meaning;
            cout << "输入单词：";
            getline(cin, word);
            if (!isIn(T, word)) {
                cout << "查找到该单词不存在，是否继续？如果继续，则插入新单词+翻译" << endl;
                cout << "输入y继续，输入其他退出：";
                string c;
                getline(cin, c);
                if (c != "y") {
                    cout << "已经退出" << endl;
                    break;
                }
            }
            cout << "---------------------" << endl;
            cout << "输入单词翻译：";
            getline(cin, meaning);
            if (insert(T, word, meaning)) cout << "成功" << endl;
            else cout << "失败" << endl;
            ExitEnter();
            break;
        }
        case 2: {
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "输入需要添加改翻译的单词" << endl;
            cout << "---------------------" << endl;
            string word, meaning;
            cout << "输入单词：";
            getline(cin, word);
            if (!isIn(T, word)) {
                cout << "查找到该单词不存在，是否继续？如果继续，则插入新单词+翻译" << endl;
                cout << "输入y继续，直接回车退出：";
                string c;
                getline(cin, c);
                if (c != "y") {
                    cout << "已经退出" << endl;
                    break;
                }
            }
            cout << "---------------------" << endl;
            cout << "输入单词翻译：";
            getline(cin, meaning);
            if (addZh(T, word, meaning)) cout << "成功" << endl;
            else cout << "失败" << endl;
            ExitEnter();
            break;
        }
        case 3: {
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "输入需要删除的单词" << endl;
            cout << "---------------------" << endl;
            string word;
            cout << "输入单词：";
            getline(cin, word);
            if (deleteWord(T, word)) cout << "删除成功" << endl;
            else cout << "已取消" << endl;
            ExitEnter();
            break;
        }
        case 0: {
            cout << "已取消操作" << endl;
            break;
        }
        }
    } while (choice != 0);
}