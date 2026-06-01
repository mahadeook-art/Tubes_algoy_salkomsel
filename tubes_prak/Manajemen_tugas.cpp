#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Tugas {
    char nama[100];
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
    cin.getline(baru->nama, 100);

    cout << "Deadline      : ";
    cin >> baru->deadline;

    cout << "Kesulitan(1-5): ";
    cin >> baru->kesulitan;

    if (baru->kesulitan < 1) baru->kesulitan = 1;
    if (baru->kesulitan > 5) baru->kesulitan = 5;

    baru->prioritas = hitungPrioritas(
        baru->deadline,
        baru->kesulitan
    );

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
        cout << "\nData ke-" << no++;
        cout << "\nNama      : " << temp->nama;
        cout << "\nDeadline  : " << temp->deadline;
        cout << "\nKesulitan : " << temp->kesulitan;
        cout << "\nPrioritas : " << temp->prioritas << endl;

        temp = temp->next;
    }
}

void cariTugas() {
    char cari[100];

    cout << "Cari nama tugas: ";
    cin.ignore();
    cin.getline(cari, 100);

    Tugas* temp = head;
    bool ketemu = false;

    while (temp != NULL) {
        if (strcmp(temp->nama, cari) == 0) {

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

    if (!ketemu) {
        cout << "Data tidak ditemukan!\n";
    }
}

void sortingTugas() {
    if (head == NULL || head->next == NULL) {
        cout << "Data terlalu sedikit.\n";
        return;
    }

    bool tukar;

    do {
        tukar = false;

        Tugas* temp = head;

        while (temp->next != NULL) {

            if (temp->prioritas < temp->next->prioritas) {

                char namaTemp[100];

                strcpy(namaTemp, temp->nama);
                strcpy(temp->nama, temp->next->nama);
                strcpy(temp->next->nama, namaTemp);

                swap(temp->deadline,
                     temp->next->deadline);

                swap(temp->kesulitan,
                     temp->next->kesulitan);

                swap(temp->prioritas,
                     temp->next->prioritas);

                tukar = true;
            }

            temp = temp->next;
        }

    } while (tukar);

    cout << "Berhasil diurutkan!\n";
}

void hapusTugas() {

    if (head == NULL) {
        cout << "Data kosong.\n";
        return;
    }

    char hapus[100];

    cout << "Nama tugas yang dihapus: ";
    cin.ignore();
    cin.getline(hapus, 100);

    if (strcmp(head->nama, hapus) == 0) {

        Tugas* buang = head;
        head = head->next;

        delete buang;

        cout << "Tugas berhasil dihapus!\n";
        return;
    }

    Tugas* temp = head;

    while (temp->next != NULL) {

        if (strcmp(temp->next->nama, hapus) == 0) {

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
    cout << "Nama      : " << terbaik->nama << endl;
    cout << "Deadline  : " << terbaik->deadline << endl;
    cout << "Kesulitan : " << terbaik->kesulitan << endl;
    cout << "Prioritas : " << terbaik->prioritas << endl;
}

void simpanFile() {

    FILE* file = fopen("data.txt", "w");

    if (file == NULL) {
        cout << "Gagal membuka file!\n";
        return;
    }

    Tugas* temp = head;

    while (temp != NULL) {

        fprintf(file, "%s\n", temp->nama);
        fprintf(file, "%d\n", temp->deadline);
        fprintf(file, "%d\n", temp->kesulitan);

        temp = temp->next;
    }

    fclose(file);

    cout << "Data berhasil disimpan!\n";
}

void bacaFile() {

    FILE* file = fopen("data.txt", "r");

    if (file == NULL) {
        return;
    }

    while (!feof(file)) {

        Tugas* baru = new Tugas;

        fgets(baru->nama, 100, file);

        if (feof(file)) {
            delete baru;
            break;
        }

        baru->nama[strcspn(baru->nama, "\n")] = 0;

        fscanf(file, "%d\n", &baru->deadline);
        fscanf(file, "%d\n", &baru->kesulitan);

        baru->prioritas = hitungPrioritas(
            baru->deadline,
            baru->kesulitan
        );

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
    }

    fclose(file);
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
        cout << "Pilih : ";

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
