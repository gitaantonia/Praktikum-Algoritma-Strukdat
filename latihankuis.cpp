//sebelum di run, tolong sediakan folder bernama "lagu" di direktori yang sama dengan file ini
//kemudian sediakan file bernama "listlagu.dat" di direktori yang sama dengan file ini
//jika tidak ada file dan folder tersebut, program tidak akan berjalan dengan baik

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

struct Lagu {
    char judul[100], penyanyi[100], genre[50];
    int tahun;
};

Lagu DaftarLagu[100]; 
int jumlahLagu = 0;  

void TambahLagu() {
    Lagu lagu;
    cout << "Judul Lagu: ";
    cin.ignore();
    cin.getline(lagu.judul, 100);

    cout << "Penyanyi: ";
    cin.getline(lagu.penyanyi, 100);

    cout << "Genre Lagu: ";
    cin.getline(lagu.genre, 50);

    cout << "Tahun Lagu: ";
    cin >> lagu.tahun;
    cin.ignore();

    string namaFile = "lagu/" + string(lagu.judul) + ".dat";
    FILE *file = fopen(namaFile.c_str(), "wb");
    if (file != nullptr) {
        fwrite(&lagu, sizeof(Lagu), 1, file);
        fclose(file);
        cout << "Data berhasil disimpan ke file " << namaFile << ".\n";
    } else {
        cout << "Gagal membuka file.\n";
    }

    FILE *listFile = fopen("listlagu.dat", "ab");
    if (listFile != nullptr) {
        fwrite(&lagu, sizeof(Lagu), 1, listFile);
        fclose(listFile);
        cout << "\n";
    } else {
        cout << "Gagal membuka file listlagu.dat.\n";
    }

    if (jumlahLagu < 100) {
        DaftarLagu[jumlahLagu++] = lagu;
    }
}

void TampilkanLagu() {
    if (jumlahLagu == 0) {
        cout << "Tidak ada lagu!\n";
        return;
    }

    cout << "\nDaftar Lagu:\n";
    for (int i = 0; i < jumlahLagu; ++i) {
        cout << "Judul: " << DaftarLagu[i].judul << endl;
        cout << "Penyanyi: " << DaftarLagu[i].penyanyi << endl;
        cout << "Genre: " << DaftarLagu[i].genre << endl;
        cout << "Tahun: " << DaftarLagu[i].tahun << endl;
        cout << "---------------------------\n";
    }
}

void CariLagu() {
    char cari[100];
    cout << "Judul Lagu yang ingin dicari: ";
    cin.ignore();
    cin.getline(cari, 100);

    for (int i = 0; i < jumlahLagu; ++i) {
        if (strcmp(DaftarLagu[i].judul, cari) == 0) {
            cout << "\nLagu Ditemukan:\n";
            cout << "Judul: " << DaftarLagu[i].judul << endl;
            cout << "Penyanyi: " << DaftarLagu[i].penyanyi << endl;
            cout << "Genre: " << DaftarLagu[i].genre << endl;
            cout << "Tahun: " << DaftarLagu[i].tahun << endl;
            return;
        }
    }
    cout << "Lagu tidak ditemukan!\n";
}

void EditLagu() {
    char cari[100];
    cout << "Judul Lagu yang ingin diedit: ";
    cin.ignore();
    cin.getline(cari, 100);

    FILE *file = fopen("listlagu.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    if (file != nullptr && tempFile != nullptr) {
        Lagu lagu;
        bool ditemukan = false;

        while (fread(&lagu, sizeof(Lagu), 1, file)) {
            if (strcmp(lagu.judul, cari) == 0) {
                cout << "Masukkan Informasi Baru:\n";
                cout << "Judul Baru: ";
                char judulLama[100];
                strcpy(judulLama, lagu.judul);
                cin.getline(lagu.judul, 100);
                cout << "Penyanyi Baru: ";
                cin.getline(lagu.penyanyi, 100);
                cout << "Genre Baru: ";
                cin.getline(lagu.genre, 50);
                cout << "Tahun Baru: ";
                cin >> lagu.tahun;
                cin.ignore();
                ditemukan = true;

                string fileLama = "lagu/" + string(judulLama) + ".dat";
                if (remove(fileLama.c_str()) == 0) {
                    cout << "File lama " << fileLama << " berhasil dihapus.\n";
                } else {
                    cout << "Gagal menghapus file lama " << fileLama << ".\n";
                }

                string fileBaru = "lagu/" + string(lagu.judul) + ".dat";
                FILE *judulFile = fopen(fileBaru.c_str(), "wb");
                if (judulFile != nullptr) {
                    fwrite(&lagu, sizeof(Lagu), 1, judulFile);
                    fclose(judulFile);
                    cout << "Data lagu berhasil diperbarui di file " << fileBaru << ".\n";
                } else {
                    cout << "Gagal membuka file.\n";
                }

                for (int i = 0; i < jumlahLagu; ++i) {
                    if (strcmp(DaftarLagu[i].judul, judulLama) == 0) {
                        DaftarLagu[i] = lagu;
                        break;
                    }
                }
            }
            fwrite(&lagu, sizeof(Lagu), 1, tempFile);
        }

        fclose(file);
        fclose(tempFile);

        remove("listlagu.dat");
        rename("temp.dat", "listlagu.dat");

        if (ditemukan) {
            cout << "\n";
        } else {
            cout << "Lagu tidak ditemukan!\n";
        }
    } else {
        cout << "Gagal membuka file.\n";
    }
}
void menu() {
    int pilihan;
    while (true) {
        cout << "\nPlaylist Lagu\n"
             << "1. Tambah Lagu\n"
             << "2. Tampilkan Lagu\n"
             << "3. Cari Lagu\n"
             << "4. Edit Lagu\n"
             << "5. Keluar\n"
             << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            TambahLagu();
            break;
        case 2:
            TampilkanLagu();
            break;
        case 3:
            CariLagu();
            break;
        case 4:
            EditLagu();
            break;
        case 5:
            cout << "Keluar.\n";
            return;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    }
}

int main() {
    menu();
    return 0;
}