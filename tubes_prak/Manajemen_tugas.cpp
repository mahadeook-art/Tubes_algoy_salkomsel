#include <iostream>
#include <fstream>
using namespace std;

struct Tugas {
    string nama;
    int deadline;
    int kesulitan;
    int prioritas;
    Tugas* next;
};

Tugas* head = NULL;

int hitungPrioritas(int deadline, int kesulitan) {
    return (100 - deadline) + (kesulitan * 10);
}

void tambahTugas() {
    Tugas* baru = new Tugas;

    cout << "Nama Tugas    : ";
    cin.ignore();
    getline(cin, baru->nama);
    cout << "Deadline      : ";
    cin >> baru->deadline;
    cout << "Kesulitan(1-5): ";
    cin >> baru->kesulitan;

    if (baru->kesulitan < 1) baru->kesulitan = 1;
    if (baru->kesulitan > 5) baru->kesulitan = 5;

    baru->prioritas = hitungPrioritas(baru->deadline, baru->kesulitan);
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Tugas* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    cout << "Tugas ditambahkan!\n";
}

void tampilTugas() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }

    Tugas* temp = head;
    int no = 1;
    while (temp != NULL) {
        cout << "\n Data ke-"  << no++;
        cout << "\n Nama      : " << temp->nama;
        cout << "\n Deadline  : " << temp->deadline;
        cout << "\n Kesulitan : " << temp->kesulitan;
        cout << "\n Prioritas : " << temp->prioritas << endl;
        temp = temp->next;
    }
}

void cariTugas() {
    string cari;
    cout << "Cari nama tugas: ";
    cin.ignore();
    getline(cin, cari);

    Tugas* temp = head;
    bool ketemu = false;

    while (temp != NULL) {
        if (temp->nama == cari) {
            cout << "Ditemukan\n";
            cout << "Nama      : " << temp->nama << endl;
            cout << "Deadline  : " << temp->deadline << endl;
            cout << "Kesulitan : " << temp->kesulitan << endl;
            cout << "Prioritas : " << temp->prioritas << endl;
            ketemu = true;
            break;
        }
        temp = temp->next;
    }

    if (!ketemu) cout << "Data tidak ditemukan!\n";
}

void sortingTugas() {
    if (head == NULL || head->next == NULL) {
        cout << "Data terlalu sedikit untuk diurutkan.\n";
        return;
    }

    bool adaTukar;
    do {
        adaTukar = false;
        Tugas* temp = head;
        while (temp->next != NULL) {
            if (temp->prioritas < temp->next->prioritas) {
                swap(temp->nama,      temp->next->nama);
                swap(temp->deadline,  temp->next->deadline);
                swap(temp->kesulitan, temp->next->kesulitan);
                swap(temp->prioritas, temp->next->prioritas);
                adaTukar = true;
            }
            temp = temp->next;
        }
    } while (adaTukar);

    cout << "Tugas berhasil diurutkan berdasarkan prioritas!\n";
    tampilTugas();
}

void hapusTugas() {
    if (head == NULL) {
        cout << "Data kosong, tidak ada yang bisa dihapus.\n";
        return;
    }

    string hapus;
    cout << "Nama tugas yang dihapus: ";
    cin.ignore();
    getline(cin, hapus);

    if (head->nama == hapus) {
        Tugas* buang = head;
        head = head->next;
        delete buang;
        cout << "Tugas berhasil dihapus!\n";
        return;
    }

    Tugas* temp = head;
    while (temp->next != NULL) {
        if (temp->next->nama == hapus) {
            Tugas* buang = temp->next;
            temp->next = buang->next;
            delete buang;
            cout << "Tugas berhasil dihapus!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n";
}

void rekomendasiTugas() {
    if (head == NULL) {
        cout << "Data kosong.\n";
        return;
    }

    Tugas* temp = head;
    Tugas* terbaik = head;

    while (temp != NULL) {
        if (temp->prioritas > terbaik->prioritas) {
            terbaik = temp;
        }
        temp = temp->next;
    }

    cout << "\n=== REKOMENDASI TUGAS ===\n";
    cout << "Kerjakan ini dulu!\n";
    cout << "Nama      : " << terbaik->nama << "\n";
    cout << "Deadline  : " << terbaik->deadline << "\n";
    cout << "Kesulitan : " << terbaik->kesulitan << "\n";
    cout << "Prioritas : " << terbaik->prioritas << "\n";
}

void simpanFile() {
    ofstream file("data.txt");

    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    Tugas* temp = head;
    while (temp != NULL) {
        file << temp->nama << "\n";
        file << temp->deadline << "\n";
        file << temp->kesulitan << "\n";
        temp = temp->next;
    }

    file.close();
    cout << "Data berhasil disimpan ke data.txt!\n";
}

void bacaFile() {
    ifstream file("data.txt");

    if (!file) return;

    string namaSementara;
    while (getline(file, namaSementara)) {
        if (namaSementara.empty()) continue;

        Tugas* baru = new Tugas;
        baru->nama = namaSementara;
        file >> baru->deadline;
        file >> baru->kesulitan;
        file.ignore();
        baru->prioritas = hitungPrioritas(baru->deadline, baru->kesulitan);
        baru->next = NULL;

        if (head == NULL) {
            head = baru;
        } else {
            Tugas* temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = baru;
        }
    }

    file.close();
}

int main() {
    int pilih;
    bacaFile();

    do {
        cout << "\n=== MANAJEMEN TUGAS ===\n";
        cout << "1. Tambah\n";
        cout << "2. Tampil\n";
        cout << "3. Cari\n";
        cout << "4. Sorting\n";
        cout << "5. Hapus\n";
        cout << "6. Rekomendasi\n";
        cout << "7. Simpan\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                tambahTugas();
                break;
            case 2:
                tampilTugas();
                break;
            case 3:
                cariTugas();
                break;
            case 4:
                sortingTugas();
                break;
            case 5:
                hapusTugas();
                break;
            case 6:
                rekomendasiTugas();
                break;
            case 7:
                simpanFile();
                break;
            case 8:
                simpanFile();
                cout << "Sampai jumpa!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 8);

    return 0;
}
