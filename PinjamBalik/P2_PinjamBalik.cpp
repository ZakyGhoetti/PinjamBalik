#include <bits/stdc++.h>
#include <ctype.h>
using namespace std;

//class untuk menyimpan data sebuah judul buku
class Buku{
    private:
        string judul; //judul buku
        string jenis; //jenis buku
        int banyak; //jumlah buku
        int dipinjam; //banyak buku yang dipinjam
        queue < pair<string, string> > daftar_peminjam; //kumpulan nama yang sedang meminjam
        queue <string> daftar_booking; //daftar nama yang sedang booking/antri
    public:
        //constructor
        Buku (string a, string c, int d){
            judul = a;
            jenis = c;
            banyak = d;
            dipinjam = 0;
        }

        //getter
        string get_judul(){
            return judul;
        }
        string get_jenis(){
            return jenis;
        }
        int get_banyak(){
            return banyak;
        }
        int get_dipinjam(){
            return dipinjam;
        }

        //setter
        void set_judul(string a){
            judul = a;
        }
        void set_jenis(string a){
            jenis = a;
        }
        void set_banyak(int a){
            banyak = a;
        }
        void set_dipinjam(int a){
            dipinjam = a;
        }

        //kelola peminjam
        void tambah_peminjam(string nama, string tanggal){
            daftar_peminjam.push(make_pair(nama, tanggal));
        }
        queue <pair<string, string>> get_daftar_peminjam(){
            return daftar_peminjam;
        }
        void set_daftar_peminjam(queue <pair<string, string>> a){
            daftar_peminjam = a;
        }

        //kelola pemesan / booking
        void tambah_booking(string nama){
            daftar_booking.push(nama);
        }
        queue <string> get_daftar_booking(){
            return daftar_booking;
        }
        void set_daftar_booking(queue <string> a){
            daftar_booking = a;
        }
};

struct Riwayat{
    string peminjam;
    string tgl_pinjam;
    string tgl_kembali;
    Buku* buku_dipinjam;
};


//sumber data
vector <Buku> databuku;
vector <Riwayat> histori_peminjaman;

//format tampilan data
int max_judul = 7;
int max_jenis = 7;
int max_nama = 6;
int max_total_buku = 12;
int max_jumlah_buku_tersedia = 22;


//fungsi / fitur
    int digit (int x){
        if(x == 0){
            return 1;
        }
        int e = 0;
        while(x > 0){
            e++;
            x/=10;
        }
        return e;
    }

    //fungsi untuk mendapatkan tanggal hari ini
    string tanggal(){
        time_t now = time(0);
        tm *wkt = localtime(&now);
        int tgl = wkt->tm_mday;
        int bln = wkt->tm_mon + 1;
        int thn = wkt->tm_year + 1900;
        return to_string(tgl)+"/"+to_string(bln)+"/"+to_string(thn);
    }
    
    //sorting buku berdasarkan judul secara leksikografis
    bool comp(Buku a, Buku b){
        return a.get_judul() < b.get_judul();
    }
    
    //fungsi untuk mendapatkan alamat buku sesuai judul
    int fnd(string s){ 
        int l = 0, r = databuku.size()-1;
        int m = (l+r)/2, x = -1;

        while(l <= r){
            m = (l+r)/2;
            if(databuku[m].get_judul() == s){
                x = m;
                break;
            }
            else if(databuku[m].get_judul() > s){
                r = m-1;
            }
            else{
                l = m+1;
            }
        }
        return x;
    }
    //fungsi untuk mendapatkan alamat buku sesuai judul tanpa memerhatikan lowercase dan uppercase
    string to_low(string s){
        string hasil = "";
        for(int i = 0; i < s.length(); i++){
            hasil += tolower(s[i]);
        }
        return hasil;
    }

    //fungsi untuk searching linear dengan mengabaikan kesamaan huruf kapital
    int fnd2(string s){ 
        for(int i = 0; i < databuku.size(); i++){
            if(to_low(databuku[i].get_judul()) == to_low(s)){
                return i;
            }
        }
        return -1;
    }

    void printHeader(){
        cout << "+";
        for(int i = 0; i < max_judul; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_jenis; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_total_buku; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_jumlah_buku_tersedia; i++) cout << "-";
        cout << "+";
        cout << "\n";

        cout << "| Judul ";
        for(int i = 0; i < max(max_judul - 7, 0); i++) cout << " ";
        cout << "| Jenis ";
        for(int i = 0; i < max(max_jenis - 7, 0); i++) cout << " ";
        cout << "| Total Buku ";
        for(int i = 0; i < max(max_total_buku - 12, 0); i++) cout << " ";
        cout << "| Jumlah Buku Tersedia ";
        for(int i = 0; i < max(max_jumlah_buku_tersedia - 22, 0); i++) cout << " ";
        cout << "|";
        cout << "\n";

        cout << "+";
        for(int i = 0; i < max_judul; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_jenis; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_total_buku; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_jumlah_buku_tersedia; i++) cout << "-";
        cout << "+";
        cout << "\n";
    }

    void printData(int i){
        int tersedia = databuku[i].get_banyak() - databuku[i].get_dipinjam();
        int pjgJudul = databuku[i].get_judul().length();
        int pjgJenis = databuku[i].get_jenis().length();
        int pjgBanyak = digit(databuku[i].get_banyak());
        int pjgTersedia = digit(tersedia);
        
        cout << "| " <<  databuku[i].get_judul();
        for(int i = 0; i < max(max_judul - pjgJudul - 1, 0); i++) cout << " ";
        cout << "| " << databuku[i].get_jenis();
        for(int i = 0; i < max(max_jenis - pjgJenis - 1, 0); i++) cout << " ";
        cout << "| " << databuku[i].get_banyak();
        for(int i = 0; i < max(max_total_buku - pjgBanyak - 1, 0); i++) cout << " ";
        cout << "| " << tersedia;
        for(int i = 0; i < max(max_jumlah_buku_tersedia - pjgTersedia - 1, 0); i++) cout << " ";
        cout << "|";
        cout << "\n";

        cout << "+";
        for(int i = 0; i < max_judul; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_jenis; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_total_buku; i++) cout << "-";
        cout << "+";
        for(int i = 0; i < max_jumlah_buku_tersedia; i++) cout << "-";
        cout << "+";
        cout << "\n";
    }

    //fungsi menambahkan data judul buku pada sistem (databuku)
    void tambah(){
        string tmp_judul, tmp_jenis;
        int tmp_banyak;
        cout << "Masukkan data detail buku pada baris berikut\n";
        cout << "Judul : "; cin.ignore(256, '\n'); getline(cin, tmp_judul);
        cout << "Jenis Buku : "; getline(cin, tmp_jenis);
        cout << "Banyak Buku : "; cin >> tmp_banyak;

        int pjgJudul = tmp_judul.length();
        max_judul = max(max_judul, pjgJudul + 2);
        int pjgJenis = tmp_jenis.length();
        max_jenis = max(max_jenis, pjgJenis + 2);

        int i = fnd(tmp_judul);
        if(i == -1){ //jika buku belum ada pada sistem
            Buku buku_baru(tmp_judul, tmp_jenis, tmp_banyak);
            databuku.push_back(buku_baru);
        }
        else{ //jika buku ada pada sistem
            databuku[i].set_banyak(databuku[i].get_banyak() + tmp_banyak);
        }
        cout << "\nBuku berhasil ditambahkan\n";

    }

    //fungsi mencari sebuah buku berdasarkan judul buku
    void cari(){
        string judulCari;
        cout << "Judul buku yang ingin dicari: ";
        cin.ignore(256, '\n');
        getline(cin, judulCari);

        int i = fnd2(judulCari);
        if (i != -1)
        {
            cout << "Buku ditemukan." << endl;

            printHeader();
            printData(i);
            cout << "\n";
            cout << "Daftar Peminjam : ";
            queue < pair<string, string> > peminjam = databuku[i].get_daftar_peminjam();
            if(!peminjam.empty()){
                bool g = 0;
                while(!peminjam.empty()){
                    if(g) cout << ", ";
                    cout << peminjam.front().first;
                    g = 1;
                    peminjam.pop();
                }
            }
            else{
                cout << "-";
            }
            cout << "\n";
            cout << "Daftar Booking : ";
            queue < string > book = databuku[i].get_daftar_booking();
            if(!book.empty()){
                bool g = 0;
                while(!book.empty()){
                    if(g) cout << ", ";
                    cout << book.front();
                    g = 1;
                    book.pop();
                }
            }
            else{
                cout << "-";
            }
            cout << "\n\n";
        }
        else
        {
            cout << "Buku tidak ditemukan." << endl;
        }
    }

    //fungsi untuk user meminjam buku berdasarkan judul
    void pinjam(){
        string judulPinjam, namaPeminjam;
        cout << "Masukkan judul buku yang ingin dipinjam: ";
        cin.ignore(256, '\n');
        getline(cin, judulPinjam);

        int idx = fnd(judulPinjam);
        if (idx != -1){
            if (databuku[idx].get_banyak() - databuku[idx].get_dipinjam() > 0){ //jika buku masih ada
                cout << "Masukkan nama peminjam: ";
                getline(cin, namaPeminjam);

                if(!databuku[idx].get_daftar_booking().empty()){ //jika ada yg booking
                    queue <string> book = databuku[idx].get_daftar_booking();
                    queue <string> depan;
                    int urutan = 0;
                    int sisa = databuku[idx].get_banyak() - databuku[idx].get_dipinjam();
                    bool cek = 0;
                    while(!book.empty()){
                        urutan++;
                        if(book.front() == namaPeminjam){
                            cek = 1;
                            book.pop();
                            break;
                        }
                        depan.push(book.front());
                        book.pop();
                    }
                    while(!book.empty()){
                        depan.push(book.front());
                        book.pop();
                    }
                    if(urutan > 0 && urutan <= sisa && cek){ //jika urutan booking <= sisa stok
                        databuku[idx].tambah_peminjam(namaPeminjam, tanggal());
                        databuku[idx].set_dipinjam(databuku[idx].get_dipinjam() + 1);
                        cout << "Buku " << judulPinjam << " berhasil dipinjam oleh " << namaPeminjam << endl;
                        int pjgNama = namaPeminjam.length();
                        max_nama = max(max_nama, pjgNama + 2);
                        
                        databuku[idx].set_daftar_booking(depan);
                    }
                    else{
                        cout << "Maaf, anda harus menunggu pengguna lain yang sudah booking." << endl;
                    }
                }
                else{ //tidak ada yg booking
                    databuku[idx].tambah_peminjam(namaPeminjam, tanggal());
                    databuku[idx].set_dipinjam(databuku[idx].get_dipinjam() + 1);
                    cout << "Buku " << judulPinjam << " berhasil dipinjam oleh " << namaPeminjam << endl;
                    int pjgNama = namaPeminjam.length();
                    max_nama = max(max_nama, pjgNama + 2);
                }
            }
            else{ //stok buku habis
                cout << "Maaf, buku tidak tersedia untuk dipinjam saat ini." << endl;
            }
        }
        else{
            cout << "Buku tidak ditemukan." << endl;
            }
    }

    //fungsi untuk user mengembalikan buku
    void kembali(){
        string judulKembaliin, namaPeminjam, tanggalPinjam;
        cout << "Judul buku yang ingin dikembalikan: ";
        cin.ignore(256, '\n');
        getline(cin, judulKembaliin);
        cout << "Masukkan nama peminjam: ";
        getline(cin, namaPeminjam);

        int idx = fnd(judulKembaliin);
        if (idx != -1){
            queue<pair<string, string>> antrian = databuku[idx].get_daftar_peminjam();
            queue<pair<string, string>> depan;
            bool cek = 0;
            while (!antrian.empty()){
                if(antrian.front().first == namaPeminjam){
                    cek = 1;
                    tanggalPinjam = antrian.front().second;
                }
                depan.push({antrian.front().first, antrian.front().second});
                antrian.pop();
            }

            if(cek){
                while (!depan.empty()){
                    if(depan.front().first != namaPeminjam){
                        antrian.push({depan.front().first, depan.front().second});
                    }
                    depan.pop();
                }
                databuku[idx].set_dipinjam(databuku[idx].get_dipinjam() - 1); 
                databuku[idx].set_daftar_peminjam(antrian);

                Riwayat berhasil_kembaliin;
                berhasil_kembaliin.buku_dipinjam = &databuku[idx];
                berhasil_kembaliin.peminjam = namaPeminjam;
                berhasil_kembaliin.tgl_kembali = tanggal();
                berhasil_kembaliin.tgl_pinjam = tanggalPinjam;
                histori_peminjaman.push_back(berhasil_kembaliin);
                cout << "Buku " << judulKembaliin << " berhasil dikembalikan." << endl;
            }

            else{
                cout << "Anda belum meminjam buku ini." << endl;
            }
        }
        else{
            cout << "Buku tidak ditemukan." << endl;
        }
    }

    //menampilkan histori peminjaman, berdasarkan judul buku
    void histori(){
        int input2;
        cout << "\nHISTORI\n\n";
        cout << "1. Judul Buku\n";
        cout << "2. Nama Peminjam\n";
        cin >> input2;
        
        if(input2 == 1){
            string judulHistori;
            cout << "Masukkan judul buku yang ingin dilihat historinya: ";
            cin.ignore(256, '\n');
            getline(cin, judulHistori);

            vector <Riwayat> tmp;
            for(int i = 0; i < histori_peminjaman.size(); i++){
                if(histori_peminjaman[i].buku_dipinjam->get_judul() == judulHistori){
                    tmp.push_back(histori_peminjaman[i]);
                }
            }
            
            //print header
            cout << "+";
            for(int i = 0; i < max_nama; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 16; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 17; i++) cout << "-";
            cout << "+";
            cout << "\n";

            cout << "| Nama ";
            for(int i = 0; i < max(max_nama - 6, 0); i++) cout << " ";
            cout << "| Tanggal Pinjam ";
            cout << "| Tanggal Kembali ";
            cout << "|";
            cout << "\n";

            cout << "+";
            for(int i = 0; i < max_nama; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 16; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 17; i++) cout << "-";
            cout << "+";
            cout << "\n";

            //print data
            for(int i = 0; i < tmp.size(); i++){
                int pjgNama = tmp[i].peminjam.length();
                int pjgTgl1 = tmp[i].tgl_pinjam.length();
                int pjgTgl2 = tmp[i].tgl_kembali.length();

                cout << "| " << tmp[i].peminjam;
                for(int i = 0; i < max(max_nama - pjgNama - 1, 0); i++) cout << " ";
                cout << "| " << tmp[i].tgl_pinjam;
                for(int i = 0; i < max(16 - pjgTgl1 - 1, 0); i++) cout << " ";
                cout << "| " << tmp[i].tgl_kembali;
                for(int i = 0; i < max(17 - pjgTgl2 - 1, 0); i++) cout << " ";
                cout << "|";
                cout << '\n';

                cout << "+";
                for(int i = 0; i < max_nama; i++) cout << "-";
                cout << "+";
                for(int i = 0; i < 16; i++) cout << "-";
                cout << "+";
                for(int i = 0; i < 17; i++) cout << "-";
                cout << "+";
                cout << "\n";
            }
        }
        else{
            string namaHistori;
            cout << "Masukkan nama peminjam yang ingin dilihat historinya: ";
            cin.ignore(256, '\n');
            getline(cin, namaHistori);

            vector <Riwayat> tmp;
            for(int i = 0; i < histori_peminjaman.size(); i++){
                if(histori_peminjaman[i].peminjam == namaHistori){
                    tmp.push_back(histori_peminjaman[i]);
                }
            }
           //print header
           
            cout << "+";
            for(int i = 0; i < max_judul; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 16; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 17; i++) cout << "-";
            cout << "+";
            cout << "\n";

            cout << "| Judul ";
            for(int i = 0; i < max(max_judul - 7, 0); i++) cout << " ";
            cout << "| Tanggal Pinjam ";
            cout << "| Tanggal Kembali ";
            cout << "|";
            cout << "\n";

            cout << "+";
            for(int i = 0; i < max_judul; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 16; i++) cout << "-";
            cout << "+";
            for(int i = 0; i < 17; i++) cout << "-";
            cout << "+";
            cout << "\n";

            //print data
            for(int i = 0; i < tmp.size(); i++){
                int pjgJudul = tmp[i].buku_dipinjam->get_judul().length();
                int pjgTgl1 = tmp[i].tgl_pinjam.length();
                int pjgTgl2 = tmp[i].tgl_kembali.length();

                cout << "| " << tmp[i].buku_dipinjam->get_judul();
                for(int i = 0; i < max(max_judul - pjgJudul - 1, 0); i++) cout << " ";
                cout << "| " << tmp[i].tgl_pinjam;
                for(int i = 0; i < max(16 - pjgTgl1 - 1, 0); i++) cout << " ";
                cout << "| " << tmp[i].tgl_kembali;
                for(int i = 0; i < max(17 - pjgTgl2 - 1, 0); i++) cout << " ";
                cout << "|";
                cout << '\n';

                cout << "+";
                for(int i = 0; i < max_judul; i++) cout << "-";
                cout << "+";
                for(int i = 0; i < 16; i++) cout << "-";
                cout << "+";
                for(int i = 0; i < 17; i++) cout << "-";
                cout << "+";
                cout << "\n";
            }
        }
    }

    //fungsi untuk booking buku untuk dipinjam (jika stok habis)
    void booking(){
        string judulBuku;
        cout << "Masukkan judul buku yang ingin dibooking: ";
        cin.ignore(256, '\n');
        getline(cin, judulBuku);

        int idx = fnd(judulBuku);
        if (idx != -1){
            if (databuku[idx].get_banyak() - databuku[idx].get_dipinjam() <= 0){
                cout << "Buku sedang kosong, silahkan isi nama agar buku dapat segera dipinjam jika tersedia : " ;
                string nama_peminjam;
                cin >> nama_peminjam;
                queue <string> tmp =  databuku[idx].get_daftar_booking();
                tmp.push(nama_peminjam);
                databuku[idx].set_daftar_booking(tmp);
            }
            else{
                cout << "Buku ini masih tersedia, silahkan menuju ke opsi pinjam buku." << endl;
            }
        }
        else{
            cout << "Buku tidak ditemukan." << endl;
        }
    }
    
    //tampilkan seluruh buku yang ada
    void tampil(){
        //print header
        printHeader();

        //print data
        for(int i = 0; i < databuku.size(); i++){
            printData(i);
        }
        cout << '\n';
    }

    //splitting string 
    vector <string> split(string a, string delim){
        vector <string> tmp;
        string token;
        int pjgDelim = delim.length();
        int x;
        while((x = a.find(delim)) >= 0 && x < a.length()){
            token = a.substr(0, x);
            a.erase(0, x + pjgDelim);
            tmp.push_back(token);
            //cout << token << '\n';
        }
        token = a;
        tmp.push_back(token);
        //cout << token << '\n';
        return tmp;
    }

    //data (dummy) yang sudah tersedia
    void inputData(){
        //ambil file
        ifstream file;
        file.open("data_buku.txt");

        string input; //per baris dari file txt

        while(file.good()){
            getline(file, input); //input berisi 1 baris pada file txt
            //cout << input << '\n';
            string delimiter = ";";
            vector <string> token = split(input, delimiter);
            string x = token[0], y = token[1];
            int z = stoi(token[2]);

            int pjgJudul = x.length();
            max_judul = max(max_judul, pjgJudul + 2);
            int pjgJenis = y.length();
            max_jenis = max(max_jenis, pjgJenis + 2);

            Buku buku_baru(x, y, z);
            databuku.push_back(buku_baru);
            
        }
        file.close();
    }

int main(){
    //data awal
    inputData();
    sort(databuku.begin(), databuku.end(), comp);

    int input;
    do{
        cout << " ___ _       _              ___       _ _ _   \n";
        cout << "| _ (_)_ _  (_)__ _ _ __   | _ ) __ _| (_) |__\n";
        cout << "|  _/ | ' \\ | / _` | '  \\  | _ \\/ _` | | | / /\n";
        cout << "|_| |_|_||_|/ \\__,_|_|_|_| |___/\\__,_|_|_|_\\_\\\n";
        cout << "          |__/                                \n";
        cout << "\nHOMEPAGE\n\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Cari Buku\n";
        cout << "3. Pinjam Buku\n";
        cout << "4. Pengembalian Buku\n";
        cout << "5. Booking Pemninjaman Buku\n";
        cout << "6. Tampilkan Daftar Buku\n";
        cout << "7. Tampilkan Histori Buku\n";
        cout << "0. Keluar\n";
        cin >> input;

        switch(input){
            case 1:
                tambah();
                sort(databuku.begin(), databuku.end(), comp);
                break;
            case 2:
                cari();
                break;
            case 3:
                pinjam();
                break;
            case 4:
                kembali();
                break;
            case 5:
                booking();
                break;
            case 6:
                tampil();
                break;
            case 7:
                histori();
                break;
            default:
                break;
        }
    }while(input != 0);
}