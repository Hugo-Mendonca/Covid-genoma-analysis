#include <iostream>
#include <fstream> // necessário para usar ifstream
#include <string>
using namespace std;

class node {
public:
    string name;
    int data;
    node *next;

    node(string n, node *nextval = nullptr) {
        name = n;
        data = 1;
        next = nextval;
    }
};

class LinkedList {
private:
    node *head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        node *temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(string n) {
        node *temp = head;
        while (temp) {
            if (temp->name == n) {
                temp->data++;
                return;
            }
            temp = temp->next;
        }

        node *newNode = new node(n);
        newNode->next = head;
        head = newNode;
    }

    void output(ofstream& out) {
        node *temp = head;
        while (temp) {
            out << temp->name << " " << temp->data << endl;
            temp = temp->next;
        }
    }

    bool listaVazia() {
        return head == nullptr;
    }
};

class hashtable {
private:
    static const int table_Size = 4096;
    LinkedList table[table_Size];

public:
    int hashFunction(const string &seq) {
        int hashValor = 0;
        for (char c : seq) {
            int val;
            if (c == 'A') val = 0;
            else if (c == 'T') val = 1;
            else if (c == 'C') val = 2;
            else val = 3;

            hashValor = hashValor * 4 + val;
        }
        return hashValor % table_Size;
    }

    void insert(string chave) {
        int index = hashFunction(chave);
        table[index].insert(chave);
    }

    void output(ofstream& out) {
        for (int i = 0; i < table_Size; i++) {
            if (!table[i].listaVazia()) {
                table[i].output(out);
            }
        }
    }
};

int main() {
    hashtable tabela;
    string linha;

    ifstream inputFile("genoma.txt");
    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo genoma.txt!" << endl;
        return 1;
    }

    while (getline(inputFile, linha)) {
        if (linha.length() < 60) continue;

        for (int i = 0; i < 60; i += 6) {
            string bloco = linha.substr(i, 6);
            tabela.insert(bloco);
        }
    }

    inputFile.close();

    // Salvar resultado em um arquivo
    ofstream outputFile("resultado.txt");
    if (!outputFile.is_open()) {
        cout << "Erro ao criar o arquivo resultado.txt!" << endl;
        return 1;
    }

    tabela.output(outputFile);
    outputFile.close();

    return 0;
}
