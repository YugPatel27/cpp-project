// Project
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define NUM_HOSPITALS 2
#define NUM_PATIENTS 2
#define NUM_DOCTORS 2
#define MAX_APPOINTMENTS 100

using namespace std;

class Patient;
class PatientMedicalRecord;
class Hospital;
class OPD;
class Doctor;

class PatientMedicalRecord {
public:
    string medicalHistory;
    string previousTreatments;
    string prescribedMedications;

    void printMedicalRecord() const {
        cout << "Medical Record\n";
        cout << "-------------------------\n";
        cout << "Medical History: " << medicalHistory << "\n";
        cout << "Previous Treatments: " << previousTreatments << "\n";
        cout << "Prescribed Medications: " << prescribedMedications << "\n";
        cout << "-------------------------\n";
    }

    friend class Patient;  
    friend class OPD;     
    friend class Doctor;   
    friend class Hospital; 
};

class Patient : public PatientMedicalRecord {
public:
    string name;
    int age;
    int preferredHospital;
    string appointmentDate;

    void printDetails() const {
        cout << "Patient Details\n";
        cout << "-------------------------\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Preferred Hospital: " << preferredHospital + 1 << "\n";
        printMedicalRecord();
        cout << "-------------------------\n";
    }

    void appointment(const Doctor& doctor);
};

class Doctor {
public:
    string name;
    int age;
    string specialty;
    string hospitalAffiliation;
    string slots[MAX_APPOINTMENTS];
    string appointments[MAX_APPOINTMENTS];

    void printDetails() const {
        cout << "Doctor Details\n";
        cout << "-------------------------\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Specialty: " << specialty << "\n";
        cout << "Hospital Affiliation: " << hospitalAffiliation << "\n";
        cout << "-------------------------\n";
    }

    void accessPatientDetails(const Patient& patient) const {
        cout << "Accessing Patient Details\n";
        patient.printDetails();
    }

    void addSlots();
    void viewAppointments() const;
    void viewPatientDetails(const Patient patients[], int numPatients) const; // Allow Doctor to access all patient details
};

class OPD {
public:
    int appointments;
    Patient patients[MAX_APPOINTMENTS];
    Doctor doctors[MAX_APPOINTMENTS];

    void bookAppointment(const Patient& patient, const Doctor& doctor);
    void scheduleAppointment();
    void checkAvailability(const Hospital hospitals[], int numHospitals);
    

    friend class Patient; // Allow Patient to access OPD
};

class Hospital {
public:
    string name;
    string city;
    int beds;
    float price;
    float rating;

    void printDetails() const {
        cout << "Hospital Details\n";
        cout << "-------------------------\n";
        cout << "Name: " << name << "\n";
        cout << "City: " << city << "\n";
        cout << "Beds: " << beds << "\n";
        cout << "Price: " << price << "\n";
        cout << "Rating: " << rating << "\n";
        cout << "-------------------------\n";
    }

    friend class Patient; // Allow Patient to access Hospital
};


void sortByPrice(Hospital hospitals[], int numHospitals);
void sortByRating(Hospital hospitals[], int numHospitals);
void hospitalManagement(Hospital* hospitals, int numHospitals);
void readHospitalData(Hospital* hospitals, int n, const string& filename);
int findBestPreferredDoctor(const Patient patients[], const Doctor doctors[], int numPatients, int numDoctors);


void sortByPrice(Hospital* hospitals, int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (hospitals[j].price > hospitals[j + 1].price)
            {
                Hospital temp = hospitals[j];
                hospitals[j] = hospitals[j + 1];
                hospitals[j + 1] = temp;
            }
        }
    }
}

void sortByRating(Hospital* hospitals, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (hospitals[j].rating < hospitals[j + 1].rating) {
                swap(hospitals[j], hospitals[j + 1]);
            }
        }
    }
}

void checkAvailability(Hospital hospitals[], int numHospitals) {
    int n;
    cout << "Hospital Bed Availability\n";
    cout << "-------------------------\n";
    for (int i = 0; i < numHospitals; i++) {
        cout << "Hospital " << i + 1 << " (" << hospitals[i].name << ") has " << hospitals[i].beds << " beds available.\n";
    }
    cout << "-------------------------\n";
}
void Patient::appointment(const Doctor& doctor) {
    cout << "Schedule an Appointment\n";
    cout << "-------------------------\n";
    cout << "Enter the appointment date (MM/DD/YYYY): ";
    cin >> appointmentDate;
  
    cout << "Appointment scheduled successfully.\n";
    cout << "-------------------------\n";
}

void Doctor::addSlots() {
    int numSlots;
    cout << "Enter the number of slots to add: ";
    cin >> numSlots;

    for (int i = 0; i < numSlots; ++i) {
        string slot;
        cout << "Enter slot " << i + 1 << " (e.g., 09:00 AM - 10:00 AM): ";
        cin.ignore();  // Clear the newline character from the input buffer
        getline(cin, slot);
        slots[i] = slot;
    }
    cout << "Slots added successfully.\n";
}

void Doctor::viewAppointments() const {
    if (appointments[0].empty()) {
        cout << "No appointments booked yet.\n";
    } else {
        cout << "Booked Appointments\n";
        cout << "-------------------------\n";
        for (int i = 0; appointments[i].empty(); ++i) {
            cout << appointments[i] << "\n";
        }
        cout << "-------------------------\n";
    }
}

void Doctor::viewPatientDetails(const Patient patients[], int numPatients) const {
    int patientIndex;
    cout << "Enter the index of the patient to view details (1-" << numPatients << "): ";
    cin >> patientIndex;

    if (patientIndex >= 1 && patientIndex <= numPatients) {
        accessPatientDetails(patients[patientIndex - 1]);
    } else {
        cout << "Invalid index.\n";
    }
}

void hospitalManagement(Hospital* hospitals, int numHospitals) 
{
    int choice;

    while (true) {
        system("cls");
        cout << "HealthCare Management\n";
        cout << "-------------------------\n";
        cout << "1 - Display Hospital Details\n";
        cout << "2 - Edit Hospital Details (for simplicity, beds only)\n";
        cout << "3 - Sort Hospitals by Price\n";
        cout << "4 - Sort Hospitals by Rating\n";
        cout << "5 - Check Bed Availability\n";
        cout << "6 - Exit\n";
        cout << "-------------------------\n";
        cout << "Select an option by typing the numeric code: ";
        cin >> choice;

        switch (choice) {
        case 1:
            for (int i = 0; i < numHospitals; ++i) {
                hospitals[i].printDetails();
            }
            break;
        case 2:
            int hospitalIndex;
            cout << "Enter the index of the hospital to edit (1-" << numHospitals << "): ";
            cin >> hospitalIndex;

            if (hospitalIndex >= 1 && hospitalIndex <= numHospitals) {
                cout << "Enter the new number of beds for hospital " << hospitalIndex << ": ";
                cin >> hospitals[hospitalIndex - 1].beds;
                cout << "Hospital details updated.\n";
            } else {
                cout << "Invalid index.\n";
            }
            break;
        case 3:
            sortByPrice(hospitals, numHospitals);
            break;
        case 4:
            sortByRating(hospitals, numHospitals);
            break;
        case 5:
            checkAvailability(hospitals, numHospitals);
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void readHospitalData(Hospital* hospitals, int n, const string& filename) 
{
    ifstream file(filename.c_str());
    if (file.is_open()) 
    {
        for (int i = 0; i < n; ++i) 
        {
            file >> hospitals[i].name >> hospitals[i].city >> hospitals[i].beds >> hospitals[i].price >> hospitals[i].rating;
        }
        file.close();
    } 
    else 
    {
        cout << "Error opening file: " << filename << endl;
    }
}

int main() {
    Hospital hospitals[NUM_HOSPITALS];
    readHospitalData(hospitals, NUM_HOSPITALS, "hospital_data.txt");

   Doctor doctor;
    cout << "Enter details for doctor:\n";
    cout << "Name: ";
    cin >> doctor.name;
    cout << "Specialty: ";
    cin >> doctor.specialty;
    cout << "Hospital Affiliation: ";
    cin >> doctor.hospitalAffiliation;

    Patient patients[NUM_PATIENTS];

    for (int i = 0; i < NUM_PATIENTS; ++i) {
    Patient& currentPatient = patients[i];
    system("cls");
    cout << "-------------------------\n";
    cout << "HealthCare Management\n";
    cout << "-------------------------\n";
    cout << "Enter details for patient: " << i + 1 << "\n";
    cout << "Name: ";
    cin >> currentPatient.name;
    cout << "Age: ";
    cin >> currentPatient.age;
    cout << "Preferred Hospital (1-" << NUM_HOSPITALS << "): ";
    cin >> currentPatient.preferredHospital;

    cin.ignore();

    cout << "Medical History: ";
    getline(cin, currentPatient.medicalHistory);

    currentPatient.appointment(doctor);

    doctor.addSlots();
    doctor.viewAppointments();
}
    return 0;
}
