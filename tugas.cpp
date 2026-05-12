#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class Induk
class User {
protected:
    static int globalId; // Variabel statis untuk auto-increment ID
    int id;
    string nama;
    string email;

public:
    User(string nama, string email) {
        this->id = generateId();
        this->nama = nama;
        this->email = email;
    }

    int generateId() {
        return ++globalId;
    }

    // Getter untuk akses data di class Admin
    int getId() const { return id; }
    string getNama() const { return nama; }
    string getEmail() const { return email; }
};

// Inisialisasi static member
int User::globalId = 0;

// Class Turunan: Member
class Member : public User {
private:
    bool status; // true untuk Aktif, false untuk Non-aktif

public:
    Member(string nama, string email) : User(nama, email) {
        this->status = true; // Default aktif
    }

    void setStatus(bool status) {
        this->status = status;
    }

    bool getStatus() const {
        return status;
    }

    void showProfile() {
        cout << "=== Profile Member ===" << endl;
        cout << "ID     : " << id << endl;
        cout << "Nama   : " << nama << endl;
        cout << "Email  : " << email << endl;
        cout << "Status : " << (status ? "Aktif" : "Non-Aktif") << endl;
        cout << "----------------------" << endl;
    }
};

// Class Turunan: Admin
class Admin : public User {
public:
    Admin(string nama, string email) : User(nama, email) {}

    // Menampilkan semua member dari list
    void showAllMember(const vector<Member>& listMember) {
        cout << "\n[Admin Panel] Daftar Semua Member:" << endl;
        for (const auto& m : listMember) {
            cout << "ID: " << m.getId() << " | Nama: " << m.getNama() 
                 << " | Status: " << (m.getStatus() ? "Aktif" : "Mati") << endl;
        }
    }

    // Mengubah status aktif/non-aktif member
    void toggleActivationMember(Member& m) {
        m.setStatus(!m.getStatus());
        cout << "\n[System] Status member " << m.getNama() << " berhasil diubah." << endl;
    }
};

int main() {
    // Membuat beberapa objek Member
    vector<Member> databaseMember;
    databaseMember.push_back(Member("Almadudi", "almadudi@example.com"));
    databaseMember.push_back(Member("Budi", "budi@example.com"));
    databaseMember.push_back(Member("Fitrah", "fitrah@example.com"));

    // Membuat objek Admin
    Admin superAdmin("Admin Utama", "admin@system.com");

    // 1. Show Profile salah satu member
    databaseMember[0].showProfile();

    // 2. Admin melihat semua member
    superAdmin.showAllMember(databaseMember);

    // 3. Admin mematikan status member ke-2 (Budi)
    superAdmin.toggleActivationMember(databaseMember[1]);

    // 4. Cek hasil perubahan
    superAdmin.showAllMember(databaseMember);

    return 0;
}