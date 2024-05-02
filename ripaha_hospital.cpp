#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Class representing a Doctor
class Doctor
{
public:
    string name;
    double charges;
    string timing;
};

// Class representing an Appointment
class Appointment
{
public:
    static int appointmentCount; // Static variable to count appointments & inilizied to '0'
    string patientName;
    string phoneNumber;
    string department;
    string doctorName;
    string day;

    Appointment()
    {
        appointmentCount++;
    }
};

int Appointment::appointmentCount = 0;

// Function to load appointments from a file
void loadAppointmentsFromFile(Appointment appointments[100], int &appointmentCount, string fileName)
{
    ifstream inFile(fileName);

    if (inFile.is_open())
    {
        appointmentCount = 0;

        // Read appointments from the file
        while (!inFile.eof() && appointmentCount < 100)
        {
            Appointment appointment;
            getline(inFile, appointment.patientName, ',');
            getline(inFile, appointment.phoneNumber, ',');
            getline(inFile, appointment.department, ',');
            getline(inFile, appointment.doctorName, ',');
            getline(inFile, appointment.day);

            if (!appointment.patientName.empty())
            {
                appointments[appointmentCount++] = appointment;
            }
        }

        inFile.close();
        cout << "Appointments loaded from file successfully.\n";
    }
    else
    {
        cout << "Unable to open the file for loading.\n";
    }
}

// Function to display available doctors in a specific department
void showDoctors(Doctor doctors[3][2], int department)
{
    cout << "Available doctors:\n";
    for (int i = 0; i < 2; i++)
    {
        // Display doctor information
        cout << i + 1 << ". " << doctors[department - 1][i].name << " (Charges: " << doctors[department - 1][i].charges << ", Timing: " << doctors[department - 1][i].timing << ")\n";
    }
}

// Function to display details of a specific appointment
void displayAppointmentDetails(const Appointment appointment, int appointmentNumber)
{
    string capitalizedPatientName = appointment.patientName;
    for (char &c : capitalizedPatientName)
    {
        c = toupper(c);
    }
    // Display appointment details
    cout << "\nAppointment Number:"
         << "\t\t"
         << "Appointment#" << appointmentNumber << endl;
    cout << "-----------------------------------------------------------\n";
    cout << "| Patient Name:"
         << "\t\t\t" << capitalizedPatientName << endl;
    cout << "| Cell Number:"
         << "\t\t\t" << appointment.phoneNumber << endl;
    cout << "| Department:"
         << "\t\t\t" << appointment.department << endl;
    cout << "| Doctor:"
         << "\t\t\t" << appointment.doctorName << endl;
    cout << "| Day:"
         << "\t\t\t\t" << appointment.day << endl;
    cout << "-----------------------------------------------------------\n";
}

// Function to delete an appointment
void deleteAppointment(Appointment appointments[100], int &appointmentCount, int appointmentNumber, const string fileName)
{
    if (appointmentNumber > 0 && appointmentNumber <= appointmentCount)
    {
        // Shift appointments to remove the deleted one
        for (int i = appointmentNumber - 1; i < appointmentCount - 1; i++)
        {
            appointments[i] = appointments[i + 1];
        }
        appointmentCount--;

        cout << "Appointment " << appointmentNumber << " deleted successfully.\n";

        // Save remaining appointments to file
        ofstream outFile(fileName);
        if (outFile.is_open())
        {
            for (int i = 0; i < appointmentCount; i++)
            {
                outFile << appointments[i].patientName << "," << appointments[i].phoneNumber << "," << appointments[i].department << ","
                        << appointments[i].doctorName << "," << appointments[i].day << "\n";
            }
            outFile.close();
            cout << "Appointments saved to file successfully.\n";
        }
        else
        {
            cout << "Unable to open the file for saving.\n";
        }
    }
    else
    {
        cout << "Invalid appointment number.\n";
    }
}

// Function to save appointments to a file
void saveAppointmentsToFile(const Appointment appointments[100], int appointmentCount, const string &fileName)
{
    // Save appointments to file
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (int i = 0; i < appointmentCount; i++)
        {
            outFile << appointments[i].patientName << "," << appointments[i].phoneNumber << "," << appointments[i].department << ","
                    << appointments[i].doctorName << "," << appointments[i].day << "\n";
        }
        outFile.close();
        cout << "Appointments saved to file successfully.\n";
    }
    else
    {
        cout << "Unable to open the file for saving.\n";
    }
}

int main()
{
    const string fileName = "appointments.txt";
    Doctor doctors[3][2] = {
        {{"Dr. Hmaza", 2000, "4 PM to 5 PM (Monday)"}, {"Dr. Hunny", 3000, "3 PM to 4:30 PM (Tuesday)"}},
        {{"Dr. Irfan", 3000, "2 PM to 3:30 PM (Monday)"}, {"Dr. Fizan", 5000, "4 PM to 5:30 PM (Tuesday)"}},
        {{"Dr. Mahnoor", 1500, "1 PM to 3 PM (Monday)"}, {"Dr. Ibrar", 2000, "3:30 PM to 5 PM (Tuesday)"}}};

    Appointment appointments[100];
    int appointmentCount = 0;
    loadAppointmentsFromFile(appointments, appointmentCount, fileName);

    while (true)
    {
        cout << "\n\t\tOptions:\n\n1. Add new appointment\n2. View existing appointments\n3. Delete an appointment\n4. Save appointments to file\n5. Exit\n";
        int option;
        cout << "Enter your choice (1, 2, 3, 4, or 5): ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            cout << "\n\t\tWelcome to the Ripha Hospital System!\n\nDepartments:\n\n\t\t1. Cardiology\n\t\t2. Dentist\n\t\t3. Orthopedic\n\n";
            int departmentChoice;
            cout << "Enter the department number (1, 2, or 3): ";
            cin >> departmentChoice;

            if (departmentChoice < 1 || departmentChoice > 3)
            {
                cout << "\n\tInvalid department choice.\n";
                continue;
            }

            string departmentName;
            switch (departmentChoice)
            {
            case 1:
                departmentName = "Cardiology";
                break;
            case 2:
                departmentName = "Dentist";
                break;
            case 3:
                departmentName = "Orthopedic";
                break;
            }

            showDoctors(doctors, departmentChoice);

            int doctorChoice;
            cout << "Enter the doctor number: ";
            cin >> doctorChoice;

            if (doctorChoice >= 1 && doctorChoice <= 2)
            {
                Appointment newAppointment;
                cout << "Enter your name: ";
                cin.ignore(); // Clear buffer
                getline(cin, newAppointment.patientName);

                do
                {
                    cout << "Enter your cell number (11 digits): ";
                    cin >> newAppointment.phoneNumber;

                    if (newAppointment.phoneNumber.length() != 11)
                    {
                        cout << "Invalid number. Please enter exactly 11 digits.\n";
                    }

                } while (newAppointment.phoneNumber.length() != 11);

                newAppointment.department = departmentName;
                newAppointment.doctorName = doctors[departmentChoice - 1][doctorChoice - 1].name;
                newAppointment.day = doctors[departmentChoice - 1][doctorChoice - 1].timing;

                displayAppointmentDetails(newAppointment, Appointment::appointmentCount);
                char confirmation;
                cout << "\nDo you want to confirm the appointment? (Y for confirm, N for cancel): ";
                cin >> confirmation;

                if (confirmation == 'Y' || confirmation == 'y')
                {
                    appointments[appointmentCount++] = newAppointment;
                    cout << "Appointment confirmed and saved!\n";
                }
                else if (confirmation == 'N' || confirmation == 'n')
                {
                    cout << "Appointment canceled!\n";
                }
                else
                {
                    cout << "Invalid choice. Appointment canceled!\n";
                }
            }
            else
            {
                cout << "Invalid doctor choice.\n";
            }
            break;
        }
        case 2:
        {
            if (appointmentCount == 0)
            {
                cout << "\nNo appointments available.\n";
            }
            else
            {
                cout << "\nExisting Appointments:\n";
                for (int i = 0; i < appointmentCount; ++i)
                {
                    displayAppointmentDetails(appointments[i], i + 1);
                }
            }
            break;
        }
        case 3:
        {
            if (appointmentCount == 0)
            {
                cout << "\nNo appointments available to delete.\n";
            }
            else
            {
                int appointmentNumberToDelete;
                cout << "\nEnter the appointment number to delete: ";
                cin >> appointmentNumberToDelete;
                deleteAppointment(appointments, appointmentCount, appointmentNumberToDelete, fileName);
            }
            break;
        }
        case 4:
        {
            saveAppointmentsToFile(appointments, appointmentCount, fileName);
            break;
        }
        case 5:
            saveAppointmentsToFile(appointments, appointmentCount, fileName);
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid option. Please enter 1, 2, 3, 4, or 5.\n";
        }
    }
    return 0;
}