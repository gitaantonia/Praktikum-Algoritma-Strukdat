#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define MAX 100

struct Lagu
{
    char judul[30];
    char penyanyi[30];
    string genre;
    int tahun;
};

int TambahLagu(Lagu LaguBaru[], int &total)
{
    int i;
    int jlhbaru;
    cout << "Masukkan total lagu yang ingin diinput: ";
    cin >> jlhbaru;
    cout << endl;
    cin.ignore();

    if (total + jlhbaru >= MAX)
    {
        cout << "Playlist penuh! Tidak bisa menambah lagu lagi.\n";
        return total;
    }
    for (i = 0; i < jlhbaru; i++)
    {
        cout << "Masukkan Judul lagu\t : ";
        cin.getline(LaguBaru[total].judul, 30);
        cout << "\nMasukkan Penyanyi\t : ";
        cin.getline(LaguBaru[total].penyanyi, 30);
        cout << "\nMasukkan Genre lagu\t : ";
        cin >> LaguBaru[total].genre;
        cout << "\nMasukkan Tahun lagu\t : ";
        cin >> LaguBaru[total].tahun;
        cin.ignore();
        total++;
    }
    return total;
}

void TampilkanLagu(Lagu LaguBaru[], int total)
{
    if (total == 0)
    {
        cout << "Tidak ada lagu";
        return;
    }
    for (int i = 0; i < total; i++)
    {
        cout << LaguBaru[i].judul << " - " << LaguBaru[i].penyanyi << endl;
    }
}

int CariLagu(Lagu LaguBaru[], int total, string cari)
{
    bool ditemukan = false;
    for (int i = 0; i < total; i++)
    {
        if (LaguBaru[i].judul == cari)
        {
            cout << "\nData ditemukan!" << endl;
            cout << "Judul lagu\t: " << LaguBaru[i].judul << endl;
            cout << "Penyanyi\t: " << LaguBaru[i].penyanyi << endl;
            cout << "Genre\t\t: " << LaguBaru[i].genre << endl;
            cout << "Tahun\t\t: " << LaguBaru[i].tahun << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Data tidak ditemukan!\n";
    }
    return ditemukan;
}

void quicksort(Lagu LaguBaru[], int awal, int akhir)
{
    string pivot = LaguBaru[(awal + akhir) / 2].judul;
    int low = awal;
    int high = akhir;

    do
    {
        while (LaguBaru[low].judul < pivot)
        {
            low++;
        }
        while (LaguBaru[high].judul > pivot)
        {
            high--;
        }
        if (low <= high)
        {
            swap(LaguBaru[low], LaguBaru[high]);
            low++;
            high--;
        }
    } while (low <= high);

    if (awal < high)
    {
        quicksort(LaguBaru, awal, high);
    }

    if (low < akhir)
    {
        quicksort(LaguBaru, low, akhir);
    }
}

void menu()
{

    Lagu LaguBaru[MAX];
    int total = 0;
    int pil;
    string cari;

    while (true)
    {
        cout << "Playlist Lagu\n"
             << setw(15) << setfill('=') << "=" << "\n1. Tambah Lagu\n"
             << "2. Cari Lagu\n"
             << "3. Keluar\n"
             << "Pilih Menu : ";
        cin >> pil;
        cin.ignore();

        switch (pil)
        {
        case 1:
            TambahLagu(LaguBaru, total);
            quicksort(LaguBaru, 0, total - 1);
            cout << "Quick Sort: \n";
            TampilkanLagu(LaguBaru, total);
            cout << endl;
            break;
        case 2:
            cout << "Masukkan Judul lagu yang ingin dicari: ";
            getline(cin, cari);
            CariLagu(LaguBaru, total, cari);

            char kembali;
            cout << "Apakah ingin kembali ke menu? ( y / n )" << endl;
            cin >> kembali;
            if (kembali == 'y' || kembali == 'Y')
            {
                break;
            }
            else
            {
                exit(0);
            }
            break;
        case 3:
            exit(0);
        default:
            cout << "Kode Salah!!\n";
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}