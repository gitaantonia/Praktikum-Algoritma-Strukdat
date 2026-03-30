#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

void sisipAwal(Node *&head, int newData)
{
    // Node *newNode = (Node *)malloc(sizeof(Node));
    Node *newNode = new Node{newData, head};
    head = newNode;
}

void sisipTengah(Node *&head, int newData)
{
    Node *newNode = new Node{newData, nullptr};
    Node *bantu = head;
    while (bantu->next->data < newData)
    {
        bantu = bantu->next;
    }
    newNode->next = bantu->next;
    bantu->next = newNode;
}

void sisipAkhir(Node *&head, int newData)
{
    Node *newNode = new Node{newData, nullptr}; // nullptr karena next setelah akhir adalah kosong
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    else
    {
        Node *bantu = head;
        while (bantu->next != nullptr)
        {
            bantu = bantu->next;
        }
        bantu->next = newNode;
    }
}

void cetakList(Node *head)
{
    if (head == nullptr)
    {
        cout << "Linked list kosong";
        return;
    }
    Node *bantu = head;
    while (bantu != nullptr)
    {
        cout << bantu->data << " -> ";
        bantu = bantu->next;
    }
    cout << " NULL ";
}

void deleteNode(Node *&head, int key)
{
    if (head->data == key)
    {
        Node *toDelete = head;
        head = head->next;
        delete toDelete;
        // atau pakai "free (toDelete);"
        return;
    }
    Node *bantu = head;
    while (bantu->next != nullptr && bantu->next->data != key)
    {
        bantu = bantu->next;
    }
    if (bantu->next == nullptr)
    {
        cout << "Node tidak ditemukan";
        return;
    }
    Node *toDelete = bantu->next;
    bantu->next = bantu->next->next;
    delete toDelete;
}

void searchNode(Node *&head, int key)
{
    bool found = false;
    Node *bantu = head;
    while (bantu != nullptr)
    {
        if (bantu->data == key)
        {
            cout << "Data ditemukan: " << bantu->data << endl;
            found = true;
            return;
        }
        bantu = bantu->next;
    }
    if (!found)
    {
        cout << "Data " << key << " tidak ditemukan";
    }
}

void updateNode(Node *&head, int oldData, int newData)
{
    Node *bantu = head;
    while (bantu != nullptr)
    {
        if (bantu->data == oldData)
        {
            bantu->data = newData;
            return;
        }
        bantu = bantu->next;
    }
}

int main()
{
    Node *head = nullptr; // nullptr sama aja kayak NULL, tapi khusus pointer, masih belum mengarah ke node manapun
    sisipAwal(head, 10);
    sisipAkhir(head, 30);
    sisipTengah(head, 20);
    cout << "List sebelum dihapus: ";
    cetakList(head);
    deleteNode(head, 20);
    cout << "/n";
    cout << "List sesudah dihapus: ";
    cetakList(head);
    searchNode(head, 15);
    updateNode(head, 10, 20);
    cout << "List sesudah diupdate: ";
    cetakList(head);
    return 0;
}