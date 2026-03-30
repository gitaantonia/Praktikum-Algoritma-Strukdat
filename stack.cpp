#include <iostream>
using namespace std;

struct stack // bisa node atau elemen
{
    int data;
    stack *next;
};

stack *top, *bottom; // deklarasinya global

void buatStack()
{
    top = nullptr;
    bottom = nullptr;
}

bool stackKosong()
{
    return top == nullptr;
}

void push(int newData)
{
    stack *newElement = new stack{newData, nullptr};
    // newElement->data = newData;
    // newElement->next = nullptr;
    if (stackKosong())
    {
        top = bottom = newElement;
    }
    else
    {
        newElement->next = top;
        top = newElement;
    }
}

void pop()
{
    if (stackKosong())
    {
        cout << "Stack kosong\n";
    }
    else
    {
        stack *hapus = top;
        top = top->next;
        delete (hapus);
    }
}

void cetakStack()
{
    if (stackKosong())
    {
        cout << "Stack kosong\n";
    }
    else
    {
        stack *bantu = top;
        while (bantu != NULL)
        {
            cout << "| " << bantu->data << " |" << endl;
            bantu = bantu->next;
        }
        cout << "-----" << endl;
        cout << "\n";
    }
}

int main()
{
    buatStack();
    push(100);
    push(200);
    push(150);
    cetakStack();
    pop();
    cetakStack();
}