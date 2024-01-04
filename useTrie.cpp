#include"TrieMenu.h"

void ShowMenu() {
    cout << "========= 字典树，前缀查找单词 =========" << endl;
    cout << "            （李腾飞制作）             " << endl;
    cout << "当前选择字典树：" << trieN << endl;
    cout << "1. 更换字典树" << endl;
    cout << "---------------------" << endl;
    cout << "2. 插入单词" << endl;
    cout << "3. 修改单词及其翻译" << endl;
    cout << "4. 查找单词" << endl;
    cout << "---------------------" << endl;
    cout << "5. 储存当前字典树" << endl;
    cout << "0. 退出" << endl;
    cout << "请输入你的选择：";
}


int main()
{
    Trie T = new TrieNode;
    AutoLoad(T);
    int numF = 7; //菜单选项数量
    int choice;
    do {
        ShowMenu();
        cin >> choice;
        while (choice < 0 || choice>numF || cin.fail())
        {
            system("cls");
            cin.clear();
            cin.ignore();
            ShowMenu();
            cin >> choice;
        }

        switch (choice) {
        case 1: {
            // 更换字典树
            system("cls");
            changeTrie(T);
            ExitEnter();
            break;
        }
        case 2: {
            // 插入单词
            system("cls");
            insertTrie(T);
            ExitEnter();
            break;
        }
        case 3: {
            // 修改单词及其翻译
            system("cls");
            changeWord(T);
            ExitEnter();
            break;
        }
        case 4: {
            // 查找单词
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "ps：可直接回车查看所有单词" << endl;;
            while (true) {
                string word;
                cout << "输入需要查找的单词的前缀：";
                getline(cin, word);
                cout << "-------------------------------" << endl;
                searchWords(T, word);
                cout << "-------------------------------" << endl;
                cout << "输入q退出，直接回车继续：";
                string c;
                getline(cin, c);
                if (c == "q") break;
                else system("cls");
            }
            ExitEnter();
            break;
        }
        case 5: {
            // 储存当前字典树
            system("cls");
            saveNowTrie(T);
            ExitEnter();
            break;
        }
        case 0: {
            cout << "-------------------------------" << endl;
            cout << "感谢使用，再见！" << endl;
            break;
        }
        default:
            system("cls");
            cout << "输入无效，请重新选择！" << endl;
            break;
        }
    } while (choice != 0);
    return 0;
}