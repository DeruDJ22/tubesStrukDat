#include "graph.h"

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Tambah Kota\n";
    cout << "2. Tambah Jalan Antar Kota" << endl;
    cout << "3. Tampilkan Graf Kota" << endl;
    cout << "4. Cari Jalur Terpendek" << endl;
    cout << "5. Cari Jalur Alternatif" << endl;
    cout << "6. Tampilkan Kota yang Paling Sering Dilewati" << endl;
    cout << "7. Keluar" << endl;
    cout << "Masukkan pilihan: ";
}

int main() {
    graph G;
    
    int pilihan;
    do {
        displayMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string kota;
                cout << "Masukkan nama kota (ketik '.' untuk selesai): " ;
                while (true) {
                    cin >> kota;
                    if (kota == ".") break;
                    addVertex(G, kota);
                    cout << "Kota " << kota << " berhasil ditambahkan" << endl;
                    cout << "Masukkan nama kota (ketik '.' untuk selesai): " ;
                }
                break;
            }
            case 2: {
                string asal, tujuan;
                int jarak;
                cout << "Masukkan jalan antar kota (ketik '.' untuk selesai): " << endl;
                while (true) {
                    cout << "Masukkan kota asal (ketik '.' untuk selesai): ";
                    cin >> asal;
                    if (asal == ".") break;

                    cout << "Masukkan kota tujuan: ";
                    cin >> tujuan;

                    cout << "Masukkan jarak: ";
                    cin >> jarak;

                    addEdge(G, asal, tujuan, jarak);
                    cout << "Jalan dari " << asal << " ke " << tujuan << " dengan jarak " << jarak << " berhasil ditambahkan." << endl;
                }
                break;
            }
            case 3: {
                cout << "\nGraf kota: \n";
                printGraph(G);
                break;
            }
            case 4: {
                string start, end;
                cout << "Masukkan kota awal: ";
                cin >> start;
                cout << "Masukkan kota tujuan: ";
                cin >> end;
                findShortestPath(G, start, end);
                break;
            }
            case 5: {
                string start, end, blocked;
                cout << "Masukkan kota awal: ";
                cin >> start;
                cout << "Masukkan kota tujuan: ";
                cin >> end;
                cout << "Masukkan kota yang diblokir: ";
                cin >> blocked;
                findAlternativePath(G, start, end, blocked);
                break;
            }
            case 6: {
                cout << "\nKota yang paling sering dilewati: " << findMostVisitedNode(G) << endl;
                break;
            }
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}
