#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Mahasiswa {
    string nim;
    string nama;
    double tugas;
    double uts;
    double uas;
    double nilaiAkhir;
    char grade;
};

double hitungNilaiRekursi(Mahasiswa m, int nilai) {
    if (nilai == 0) {
        return (0.30 * m.tugas) + hitungNilaiRekursi(m, 1);
    } else if (nilai == 1) {
        return (0.30 * m.uts) + hitungNilaiRekursi(m, 2);
    } else if (nilai == 2) {
        return (0.40 * m.uas);
    }
    return 0;
}

int main() {
    Mahasiswa daftarMhs[3];
    int jumlahMhs = 0;

    ifstream fileInput("data_mhs.txt"); 
    if (!fileInput.is_open()) {
        cout << "Waduh, file data_mhs.txt gak ketemu, Bro!" << endl;
        return 1;
    }
    while (fileInput >> daftarMhs[jumlahMhs].nim 
                     >> daftarMhs[jumlahMhs].nama 
                     >> daftarMhs[jumlahMhs].tugas 
                     >> daftarMhs[jumlahMhs].uts 
                     >> daftarMhs[jumlahMhs].uas) {
        
        daftarMhs[jumlahMhs].nilaiAkhir = hitungNilaiRekursi(daftarMhs[jumlahMhs], 0);

        if (daftarMhs[jumlahMhs].nilaiAkhir >= 80) {
            daftarMhs[jumlahMhs].grade = 'A';
        } else if (daftarMhs[jumlahMhs].nilaiAkhir >= 70) {
            daftarMhs[jumlahMhs].grade = 'B';
        } else if (daftarMhs[jumlahMhs].nilaiAkhir >= 60) {
            daftarMhs[jumlahMhs].grade = 'C';
        } else {
            daftarMhs[jumlahMhs].grade = 'D';
        }

        jumlahMhs++;
    }
    fileInput.close();
  
    int pilihan;
    do {
        cout << "\n=== MENU RESPONSID ALPRO ===" << endl;
        cout << "1. Tampilkan Semua Data" << endl;
        cout << "2. Cari Mahasiswa Berdasarkan NIM" << endl;
        cout << "3. Cari Nilai Akhir Terendah" << endl;
        cout << "4. Hitung Rata-rata Nilai Kelas" << endl;
        cout << "5. Simpan Hasil Analisis ke File" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "\nData Mahasiswa saat ini:" << endl;
            for (int i = 0; i < jumlahMhs; i++) {
                cout << "NIM: " << daftarMhs[i].nim 
                     << " | Nama: " << daftarMhs[i].nama 
                     << " | Nilai Akhir: " << daftarMhs[i].nilaiAkhir 
                     << " | Grade: " << daftarMhs[i].grade << endl;
            }
        } 
        else if (pilihan == 2) {
            string cariNim;
            cout << "Masukkan NIM yang dicari: ";
            cin >> cariNim;
            
            bool ketemu = false;
            for (int i = 0; i < jumlahMhs; i++) {
                if (daftarMhs[i].nim == cariNim) {
                    cout << "\nData Ketemu!" << endl;
                    cout << "Nama: " << daftarMhs[i].nama << endl;
                    cout << "Nilai Akhir: " << daftarMhs[i].nilaiAkhir << endl;
                    cout << "Grade: " << daftarMhs[i].grade << endl;
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << "Mahasiswa dengan NIM tersebut gak ada, Bro." << endl;
        } 
        else if (pilihan == 3) {
            int indeksTerendah = 0;
            for (int i = 1; i < jumlahMhs; i++) {
                if (daftarMhs[i].nilaiAkhir < daftarMhs[indeksTerendah].nilaiAkhir) {
                    indeksTerendah = i;
                }
            }
            cout << "\nMahasiswa dengan Nilai Akhir Terendah:" << endl;
            cout << "NIM: " << daftarMhs[indeksTerendah].nim << endl;
            cout << "Nama: " << daftarMhs[indeksTerendah].nama << endl;
            cout << "Nilai Akhir: " << daftarMhs[indeksTerendah].nilaiAkhir << endl;
        } 
        else if (pilihan == 4) {
            double total = 0;
            for (int i = 0; i < jumlahMhs; i++) {
                total += daftarMhs[i].nilaiAkhir;
            }
            double rataRata = total / jumlahMhs;
            cout << "\nRata-rata Nilai Akhir Seluruh Mahasiswa: " << rataRata << endl;
        } 
        else if (pilihan == 5) {
            ofstream fileOutput("hasil_analisis_nilai.txt");
            
            fileOutput << "NIM Nama Tugas UTS UAS Nilai_Akhir Grade" << endl;
            for (int i = 0; i < jumlahMhs; i++) {
                fileOutput << daftarMhs[i].nim << " "
                           << daftarMhs[i].nama << " "
                           << daftarMhs[i].tugas << " "
                           << daftarMhs[i].uts << " "
                           << daftarMhs[i].uas << " "
                           << daftarMhs[i].nilaiAkhir << " "
                           << daftarMhs[i].grade << endl;
            }
            fileOutput.close();
            cout << "\nHasil analisis berhasil disimpan ke 'hasil_analisis_nilai.txt'!" << endl;
        }
    } while (pilihan != 6);
    cout << "Program selesai. Semangat responsinya!" << endl;
    return 0;
}
