#include <iostream>
#include <fstream>
using namespace std;

struct Tugas{
    string nama;
    int deadline;
    int kesulitan;
    int prioritas;
    Tugas*next;


Tugas *head= NULL;
};

int hitungPrioritas(int deadline, int kesulitan){
    return(100-deadline) + (kesulitan*10)
    
}

//tambah
void tambahTugas(){
    Tugas* baru = new Tugas;
    
    cout<<"Nama Tugas    :";
    cin.ignore();
    getline(cin, baru->nama);

    cout<<"Deadline    :";
    cin.ignore();
    cin>>baru->deadline;

    cout<<"Kesulitan(1-5)    :";
    cin.ignore();
    cin>>baru->kesulitan;

    baru->prioritas = hitungPrioritas(baru->deadline, baru->kesulitan);
    baru->next=NULL;

    if(head == NULL){
        head=baru;
    } else{
        Tugas *temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = baru;
    }
        cout<<"Tugas ditambahkan!\n";
}

void tampilTugas() {
    if(head==NULL){
        cout<<"Data kosong\n";
        return;
    }

    Tugas *temp = head;
    int no = 1;
    while (temp != NULL){
        cout<<"\n Data ke-"<< no++;
        cout<<"\n Nama             :"<< temp->nama;
        cout<<"\n Deadline         :"<< temp->deadline;
        cout<<"\n Kesulitan        :"<< temp->kesulitan;
        cout<<"\n Prioritas        :"<< temp->prioritas<<endl;

        temp = temp->next;
    }
}

void cariTugas(){
    string cari;
    cout<<"Cari nama tugas    :";
    cin.ignore();
    getline(cin, cari);

    Tugas *temp = head;
    bool ketemu = false;

    while (temp != NULL){
        if(temp->nama==cari){
            cout<<"Ditemukan\n";
            cout<<"Nama         :"<< temp->nama<<endl;
            cout<<"Prioritas    :"<< temp->prioritas<<endl;
            ketemu=true;
            break;
        }
        temp = temp->next
    }
    if(!ketemu) cout<<"Data tidak ditemukan!";
}
void bacaFile(){
    ifstream file ("data.txt");

    while (true){
        Tugas *baru = new Tugas;

        if (!getline(file, baru->nama)) break;
        file >> baru->deadline;
        file >> baru->kesulitan;
        file.ignore();

        baru->prioritas = hitungPrioritas(baru->deadline, baru->kesulitan);

        baru->next = head;
        head = baru;
    }
}
int main(){
    int pilih;
    bacaFile();

    do{
        cout << "=== SMART STUDY PLANNER ===\n";
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

        switch(pilih) {
            case 1: tambahTugas(); break;
            case 2: tampilTugas(); break;
            case 3: cariTugas(); break;






            
        }
    } while (pilih!=8);

}

