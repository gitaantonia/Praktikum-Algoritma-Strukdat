#include <iostream>
using namespace std;

struct PTBNode
{
    int data;
    PTBNode *left;
    PTBNode *right;

    PTBNode(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void input(PTBNode *&akar, int value)
{
    if (akar == nullptr)
    {
        akar = new PTBNode(value);
        return;
    }

    PTBNode *current = akar;
    while (true)
    {
        if (value < current->data)
        {
            if (current->left == nullptr)
            {
                current->left = new PTBNode(value);
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == nullptr)
            {
                current->right = new PTBNode(value);
                return;
            }
            current = current->right;
        }
    }
}

void preOrder(PTBNode *akar)
{
    if (akar == nullptr)
    {
        return;
    }
    cout << akar->data << " ";
    preOrder(akar->left);
    preOrder(akar->right);
}

void inOrder(PTBNode *akar)
{
    if (akar == nullptr)
    {
        return;
    }
    inOrder(akar->left);
    cout << akar->data << " ";
    inOrder(akar->right);
}

void postOrder(PTBNode *akar)
{
    if (akar == nullptr)
        return;
    postOrder(akar->left);
    postOrder(akar->right);
    cout << akar->data << " ";
}

PTBNode *searching(PTBNode *akar, int cari)
{
    PTBNode *current = akar;
    while (true)
    {
        if (current->data == cari)
        {
            cout << cari << "ditemukan" << endl;
            return current;
        }
        // current = (cari < current->data) ? current->left : current->right;
        if (cari < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    cout << cari << " tidak ditemukan" << endl;
    return nullptr;
}

void deleteNode(PTBNode *&akar, int hapus)

{
    if (akar == nullptr)
    {
        return;
    }
    if (hapus < akar->data)
    {
        deleteNode(akar->left, hapus);
    }
    else if (hapus > akar->data)
    {
        deleteNode(akar->right, hapus);
    }
    else
    {
        PTBNode *temp = akar;
        if (akar->left == nullptr)
        {
            akar = akar->right;
        }
        else if (akar->right == nullptr)
        {
            akar = akar->left;
        }
        else
        {
            PTBNode *successor = akar->right;
            while (successor->left != nullptr)
            {
                successor = successor->left;
            }
            akar->data = successor->data;
            deleteNode(akar->right, successor->data);
            return;
        }

        delete temp;
    }
}

main()
{
    PTBNode *akar = nullptr;
    input(akar, 15);
    input(akar, 10);
    input(akar, 12);
    input(akar, 11);
    input(akar, 8);
    input(akar, 1);
    input(akar, 5);

    preOrder(akar);
    cout << endl;
    inOrder(akar);
    cout << endl;
    postOrder(akar);
    cout << endl;

    deleteNode(akar, 8);
    preOrder(akar);
    cout << endl;
    inOrder(akar);
    cout << endl;
    postOrder(akar);
}