#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

struct Node* buatnode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(data)); // pakai new node sebagai pengganti malloc bisaa: Node* newNode = new Node{data, NULL, NULL}; (minesnya, kalau datanya banyak, harus dimasukin satu-satu)
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
};

void sisipNodeDepan(Node** head, int data)
{
    Node* newNode = buatnode(data);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void sisipNodeBelakang(Node** head, int data)
{
    Node* newNode = buatnode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node* bantu = *head;
    while (bantu->next != NULL)
    {
        bantu = bantu->next;
    }
    bantu->next = newNode;
    newNode->prev = bantu;
}

Node* searching(Node* head, int key)
{
    Node* bantu = head;
    while (bantu != NULL)
    {
        if (bantu->data == key)
        {
            return bantu;
        }
        bantu = bantu->next;
    }
    return NULL;
}

void sisipNodeTengah(Node* nodekiri, int data)
{
    if (nodekiri == NULL)
    {
        cout << "Node tidak ada" << endl;
    }
    Node* newNode = buatnode(data);
    newNode->next = nodekiri->next;
    newNode->prev = nodekiri;

    if (nodekiri->next != NULL)
    {
        nodekiri->next->prev = newNode;
    }
    nodekiri->next = newNode;
}

void hapusNodeDepan(Node** head)
{
    if (*head == NULL)
    {
        cout << "List Kosong" << endl;
        return;
    }
    Node* bantu = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free(bantu);
}

void hapusNodeBelakang(Node** head)
{
    if (*head == NULL)
    {
        cout << "List Kosong" << endl;
        return;
    }

    Node* bantu = *head;
    while (bantu->next != NULL)
    {
        bantu = bantu->next;
    }
    if (bantu->prev != NULL)
    {
        bantu->prev->next = NULL;
    }
    else
    {
        *head = NULL;
    }
    free(bantu);
}

void hapusNodeTengah(Node** head, int key)
{
    if (*head == NULL)
    {
        cout << "List Kosong" << endl;
        return;
    }

    Node* bantu = *head;
    while (bantu != NULL && bantu->data != key)
    {
        bantu = bantu->next;
    }

    if (bantu == NULL)
    {
        cout << "Node ga ketemu!" << endl;
        return;
    }

    if (bantu->prev != NULL)
    {
        bantu->prev->next = bantu->next;
    }
    else
    {
        *head = bantu->next;
    }
    if (bantu->next != NULL)
    {
        bantu->next->prev = bantu->prev;
    }
    free(bantu);
}

void printDepan(Node* head){
    if(head == NULL){
        cout << "Nodenya ga ada!" << endl;
    }
    Node* bantu = head;
    while (bantu != NULL)
    {
        cout << bantu->data << " ";
        bantu = bantu-> next;
    }    
}

void printBelakang(Node* head){
    if(head == NULL){
        cout << "Nodenya ga ada!" << endl;
    }
    Node* bantu = head;
    while (bantu->next != NULL) // ini buat jalan ke ujung list
    {
        bantu = bantu-> next;
    }    
    while (bantu != NULL) //buat jalan dari belakang ke depan
    {
        cout << bantu->data << " ";
        bantu = bantu->prev;
    }
    cout << endl;    
}

main()
{
    buatnode(10);
    Node* head = NULL;

    sisipNodeDepan(&head, 5);
    sisipNodeDepan(&head, 4);

    sisipNodeTengah(searching(head, 4), 3);

    sisipNodeDepan(&head, 2);
    sisipNodeDepan(&head, 1);

    hapusNodeBelakang(&head);
    hapusNodeTengah(&head, 2);

    printDepan(head);

    cout << endl;

    printBelakang(head);
}