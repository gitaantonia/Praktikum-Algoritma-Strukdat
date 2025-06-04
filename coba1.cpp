#include <iostream>
#include <iomanip>
using namespace std;

struct produk
{
    int kode, stok;
    string nama, jenis;

    produk *left;
    produk *right;

    produk(int k, string n, int s, string j)
    {
        kode = k;
        nama = n;
        stok = s;
        jenis = j;
        left = nullptr;
        right = nullptr;
    }
};

struct aksiUndo {
    string aksi;   
    produk *data;     
    aksiUndo *next;
};

aksiUndo *topUndo = nullptr;

void pushUndo(const string &aksi, produk *data) {
    aksiUndo *baru = new aksiUndo;
    baru->aksi = aksi;
    baru->data = new produk(*data);
    baru->next = topUndo;
    topUndo = baru;
}

aksiUndo *popUndo() {
    if (topUndo == nullptr) return nullptr;
    aksiUndo *hapus = topUndo;
    topUndo = topUndo->next;
    return hapus;
}

bool kodeSudahAda(produk *akar, int kode) {
    if (akar == nullptr) return false;
    if (akar->kode == kode) return true;
    if (kode < akar->kode)
        return kodeSudahAda(akar->left, kode);
    else
        return kodeSudahAda(akar->right, kode);
}

void tambahData(produk *&akar, int kode, string nama, int stok, string jenis)
{
    if (kodeSudahAda(akar, kode)) {
        cout << "Kode produk sudah ada, tidak boleh duplikat!\n";
        return;
    }
    if (akar == nullptr)
    {
        akar = new produk(kode, nama, stok, jenis);
        pushUndo("tambah", akar); 
        return;
    }

    produk *current = akar;
    while (true)
    {
        if (kode < current->kode)
        {
            if (current->left == nullptr)
            {
                current->left = new produk(kode, nama, stok, jenis);
                pushUndo("tambah", current->left); 
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == nullptr)
            {
                current->right = new produk(kode, nama, stok, jenis);
                pushUndo("tambah", current->right);
                return;
            }
            current = current->right;
        }
    }
}

void tampilkanData(produk *akar)
{
    if (akar == nullptr)
    {
        return;
    }

    static bool headerPrinted = false;
    if (!headerPrinted) {
        cout << left << setw(10) << "Kode"
             << setw(20) << "Nama"
             << setw(10) << "Stok"
             << setw(15) << "Jenis" << endl;
        cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
        headerPrinted = true;
    }

    tampilkanData(akar->left);
    cout << left << setw(10) << akar->kode
         << setw(20) << akar->nama
         << setw(10) << akar->stok
         << setw(15) << akar->jenis << endl;
    tampilkanData(akar->right);

    // Reset headerPrinted saat selesai (hanya untuk tampilan per panggilan)
    if (akar->left == nullptr && akar->right == nullptr) {
        headerPrinted = false;
    }
}

void searching(produk *akar, const string &cari)
{
    if (akar == nullptr)
        return;

    searching(akar->left, cari);

    if (akar->jenis == cari)
    {
        cout << left << setw(10) << akar->kode
             << setw(20) << akar->nama
             << setw(10) << akar->stok
             << setw(15) << akar->jenis << endl;
    }

    searching(akar->right, cari);
}

void filterData(produk *akar)
{
    string target;
    cout << "Masukkan jenis produk yang ingin dicari: ";
    cin.ignore();
    getline(cin, target);

    cout << "\nHasil pencarian produk dengan jenis \"" << target << "\":" << endl;
    cout << left << setw(10) << "Kode"
         << setw(20) << "Nama"
         << setw(10) << "Stok"
         << setw(15) << "Jenis" << endl;
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
    searching(akar, target);
}

void hapusData(produk *&akar, int hapus)
{
    if (akar == nullptr)
    {
        cout << "Produk dengan kode tersebut tidak ditemukan.\n";
        return;
    }
    if (hapus < akar->kode)
    {
        hapusData(akar->left, hapus);
    }
    else if (hapus > akar->kode)
    {
        hapusData(akar->right, hapus);
    }
    else
    {
        pushUndo("hapus", akar);

        produk *temp = akar;
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
            produk *successor = akar->right;
            while (successor->left != nullptr)
            {
                successor = successor->left;
            }
            akar->kode = successor->kode;
            akar->nama = successor->nama;
            akar->stok = successor->stok;
            akar->jenis = successor->jenis;
            hapusData(akar->right, successor->kode);
            return;
        }

        delete temp;
    }
}

void undoData(produk *&akar) {
    aksiUndo *aksi_terakhir = popUndo();
    if (aksi_terakhir == nullptr) {
        cout << "Tidak ada aksi yang bisa di-undo.\n";
        return;
    }

    if (aksi_terakhir->aksi == "tambah") {
        cout << "Undo penambahan produk dengan kode: " << aksi_terakhir->data->kode << endl;
        hapusData(akar, aksi_terakhir->data->kode);
    } else if (aksi_terakhir->aksi == "hapus") {
        cout << "Undo penghapusan produk dengan kode: " << aksi_terakhir->data->kode << endl;
        tambahData(akar,
                   aksi_terakhir->data->kode,
                   aksi_terakhir->data->nama,
                   aksi_terakhir->data->stok,
                   aksi_terakhir->data->jenis);
    }

    delete aksi_terakhir->data;
    delete aksi_terakhir;
}

int main()
{
    produk *akar = nullptr;
    int pilihan;

    do
    {
        cout << "========== Menu ==========\n"
             << "1. Menambahkan Data Produk\n"
             << "2. Menampilkan Daftar Produk\n"
             << "3. Filter Genre Produk\n"
             << "4. Menghapus Data Produk\n"
             << "5. Ulangi Aksi Terakhir (Undo)\n"
             << "6. Keluar\n"
             << "Masukkan Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
        {
            int kode, stok;
            string nama, jenis;
            cout << "Masukkan Kode Produk: ";
            cin >> kode;
            cin.ignore();
            cout << "Masukkan Nama Produk: ";
            getline(cin, nama);
            cout << "Masukkan Stok Produk: ";
            cin >> stok;
            cin.ignore();
            cout << "Masukkan Jenis Produk: ";
            getline(cin, jenis);
            tambahData(akar, kode, nama, stok, jenis);
            break;
        }
        case 2:
            tampilkanData(akar);
            break;
        case 3:
            filterData(akar);
            break;
        case 4:
        {
            int kode;
            cout << "Masukkan Kode Produk yang akan dihapus: ";
            cin >> kode;
            hapusData(akar, kode);
            break;
        }
        case 5:
            undoData(akar);
            break;
        case 6:
            cout << "Terima Kasih!\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }
    } while (pilihan != 6);
}