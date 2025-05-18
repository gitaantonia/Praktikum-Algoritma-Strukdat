#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Node
{
    char judul[100];
    char penulis[100];
    Node *next;
    Node *prev;
};

struct Node *buatnode(char judul[], char penulis[])
{
    Node *newNode = new Node;
    strcpy(newNode->judul, judul);
    strcpy(newNode->penulis, penulis);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
};

void sisipNodeDepan(Node **head, char judul[], char penulis[])
{
    Node *newNode = buatnode(judul, penulis);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
    cout << "Buku berhasil ditambahkan di depan.\n";
}

void sisipNodeBelakang(Node **head, char judul[], char penulis[])
{
    Node *newNode = buatnode(judul, penulis);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *bantu = *head;
    while (bantu->next != NULL)
    {
        bantu = bantu->next;
    }
    bantu->next = newNode;
    newNode->prev = bantu;
    cout << "Buku berhasil ditambahkan di belakang.\n";
}

void hapusNodeTengah(Node **head, char key[])
{
    if (*head == NULL)
    {
        cout << "List Kosong" << endl;
        return;
    }

    Node *bantu = *head;
    while (bantu != NULL && strcmp(bantu->judul, key) != 0)
    {
        bantu = bantu->next;
    }

    if (bantu == NULL)
    {
        cout << "Buku tidak ketemu!" << endl;
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

    cout << "Data berhasil dihapus\n";
}

void printDepan(Node *head)
{
    if (head == NULL)
    {
        cout << "Bukunya tidak ada!" << endl;
    }
    cout << setfill('=') << setw(75) << "=" << endl;
    cout << setfill(' ')
         << "| " << setw(45) << left << "Judul Buku"
         << "| " << setw(25) << left << "Penulis"
         << "|" << endl;
    cout << setfill('=') << setw(75) << "=" << endl;
    Node *bantu = head;
    while (bantu != NULL)
    {
        cout << setfill(' ')
             << "| " << setw(45) << left << bantu->judul
             << "| " << setw(25) << left << bantu->penulis
             << "|" << endl;

        bantu = bantu->next;
    }
    cout << setfill('=') << setw(75) << "=" << endl;
}

int main()
{
    Node *head = NULL;
    int pilihan;
    char judul[100], penulis[100];

    do
    {
        cout << endl;
        cout << "=== MENU MANAJEMEN DAFTAR BUKU ===\n"
             << "1. Tambah Buku di Depan\n"
             << "2. Tambah Buku di Belakang\n"
             << "3. Hapus Buku Berdasarkan Judul\n"
             << "4. Tampilkan Daftar Buku\n"
             << "5. Keluar\n"
             << "Pilih Menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan Judul Buku   : ";
            cin.getline(judul, 100);
            cout << "Masukkan Penulis Buku : ";
            cin.getline(penulis, 100);
            sisipNodeDepan(&head, judul, penulis);
            break;

        case 2:
            cout << "Masukkan Judul Buku   : ";
            cin.getline(judul, 100);
            cout << "Masukkan Penulis Buku : ";
            cin.getline(penulis, 100);
            sisipNodeBelakang(&head, judul, penulis);
            break;

        case 3:
            cout << "Masukkan Judul Buku yang ingin dihapus: ";
            cin.getline(judul, 100);
            hapusNodeTengah(&head, judul);
            break;

        case 4:
            printDepan(head);
            break;

        case 5:
            cout << "Keluar dari program.\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}