/*Для реализации программы автодополнения слов по заданному словарю, 
мы можем использовать структуру данных, называемую "Trie" (префиксное дерево). 
Trie позволяет эффективно хранить и искать слова по их префиксам. */

#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace std;

// Структура узла Trie
struct TrieNode {
    TrieNode* children[26]; // Дети узла (по количеству букв в английском алфавите)
    bool isEndOfWord; // Флаг, указывающий, является ли узел концом слова

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr; // Инициализируем детей узла как nullptr
        }
    }
};

// Класс Trie
class Trie {
private:
    TrieNode* root; // Корень дерева

public:
    Trie() {
        root = new TrieNode(); // Создаем корень
    }

    // Метод для вставки слова в Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a'; // Находим индекс буквы
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode(); // Создаем новый узел, если его нет
            }
            node = node->children[index]; // Переходим к следующему узлу
        }
        node->isEndOfWord = true; // Устанавливаем флаг конца слова
    }

    // Метод для поиска всех слов с заданным префиксом
    void searchWords(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord) {
            results.push_back(prefix); // Если узел является концом слова, добавляем его в результаты
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                searchWords(node->children[i], prefix + char(i + 'a'), results); // Рекурсивно ищем слова
            }
        }
    }

    // Метод для получения слов по префиксу
    vector<string> autocomplete(const string& prefix) {
        TrieNode* node = root;
        vector<string> results;

        // Находим узел, соответствующий префиксу
        for (char ch : prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                return results; // Если узел не найден, возвращаем пустой вектор
            }
            node = node->children[index];
        }

        // Ищем все слова, начинающиеся с префикса
        searchWords(node, prefix, results);
        return results;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    Trie trie;
    // Вставляем слова в Trie
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bandana");
    trie.insert("cat");
    trie.insert("caterpillar");

    string input;
    cout << "Введите префикс для автодополнения (или 'exit' для выхода): " << endl;

    while (true) {
        cout << "> ";
        cin >> input;
        if (input == "exit") {
            break; // Выход из программы
        }

        vector<string> suggestions = trie.autocomplete(input);
        if (suggestions.empty()) {
            cout << "Нет предложений для префикса: " << input << endl;
        }
        else {
            cout << "Предложения: ";
            for (const string& word : suggestions) {
                cout << word << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
/*Пояснения к коду:

Структура TrieNode: Каждый узел содержит массив детей (по количеству букв в алфавите) и флаг, указывающий, является ли узел концом слова.

Класс Trie: Содержит методы для вставки слов и поиска слов по префиксу.

Метод insert: Вставляет слово в Trie, создавая необходимые узлы.

Метод searchWords: Рекурсивно ищет все слова, начинающиеся с заданного префикса.

Метод autocomplete: Находит узел, соответствующий префик*/