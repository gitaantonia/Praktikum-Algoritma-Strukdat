#include <iostream>
using namespace std;

struct queue
{
    int data; // bisa char atau yg lain
    queue *next;
};

queue *depan, *belakang;

bool queueKosong()
{
    return depan == nullptr;
}

void buatQueue()
{
    depan = nullptr;
    belakang = nullptr;
}

void enqueue(int newData)
{
    queue *newElement = new queue{newData, nullptr};
    if (queueKosong())
    {
        depan = belakang = newElement;
    }
    else
    {
        belakang->next = newElement;
    }
    belakang = newElement;
}

void dequeue()
{
    if (queueKosong())
    {
        cout << "Queue kosong\n";
    }
    else
    {
        queue *hapus = depan;
        depan = depan->next;
        delete hapus;
    }
}

void cetakQueue()
{
    if (queueKosong())
    {
        cout << "Queue kosong\n";
    }
    else
    {
        queue *bantu = depan;
        while (bantu != nullptr)
        {
            cout << bantu->data << " ";
            bantu = bantu->next;
        }
        cout << endl;
    }
}

int main()
{
    buatQueue();
    enqueue(10);
    enqueue(5);
    enqueue(50);
    cetakQueue();
    dequeue();
    cetakQueue();

    // Hapus semua elemen queue
    while (!queueKosong())
    {
        dequeue();
    }
    cetakQueue(); // Akan menampilkan "Queue kosong"
}