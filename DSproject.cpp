#include <iostream>
using namespace std;

const int m = 2;
const int n = 2;
int A[m][n] = {0};

struct node {
    int seat_no;
    string name;
    node* next;
};

node* head = NULL;

const int k = 5;
string q[k];
int f = -1;
int r = -1;

int isempty() {
    return (f == -1 && r == -1) ? 1 : 0;
}

int isfull() {
    return ((r + 1) % k == f) ? 1 : 0;
}

void enq(string name) {
    if (isfull()) {
        cout << "Waiting queue is full! Cannot add more persons.\n";
        return;
    }
    if (isempty())
        f = r = 0;
    else
        r = (r + 1) % k;
    q[r] = name;
    cout << name << " added to the waiting list.\n";
}

string dq() {
    if (isempty()) {
        cout << "No one is in the waiting queue.\n";
        return "";
    }
    string name = q[f];
    if (f == r)
        f = r = -1;
    else
        f = (f + 1) % k;
    return name;
}

int housefull() {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] == 0)
                return 0;
    return 1;
}

void book(string name, int a, int b) {
    // Added Boundary Check
    if (a < 0 || a >= m || b < 0 || b >= n) {
        cout << "Invalid seat! Please choose row 0-" << m-1 << " and col 0-" << n-1 << ".\n";
        return;
    }

    if (A[a][b] == 0) {
        cout << "\n";
        // Fixed Memory Allocation
        node* newn = new node();
        newn->seat_no = (a * 10) + b;
        newn->name = name;
        newn->next = NULL;

        if (head == NULL)
            head = newn;
        else {
            node* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newn;
        }

        A[a][b] = 1;
        cout << "Seat booked successfully!\n";
        cout << "Name: " << name << "\nSeat No: " << (a * 10) + b << endl;
    } else {
        cout << "Seat is not available; try again\n";
    }
}

void status() {
    int num;
    cout << "Enter your seat no: ";
    cin >> num;

    node* temp = head;
    while (temp != NULL) {
        if (temp->seat_no == num) {
            cout << "The seat is booked by\n";
            cout << "Name: " << temp->name << "\nSeat No: " << temp->seat_no << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Seat is available\n";
}

void cancel() {
    if (head == NULL) {
        cout << "No bookings available to cancel.\n";
        return;
    }

    int num;
    cout << "Enter the seat number to cancel: ";
    cin >> num;

    node *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (temp->seat_no == num) {
            int a = num / 10;
            int b = num % 10;
            A[a][b] = 0;

            if (temp == head)
                head = head->next;
            else
                prev->next = temp->next;

            delete temp; // Fixed Memory Deallocation

            cout << "Seat canceled successfully!\n";

            if (!isempty()) {
                string waiting_person = dq();
                book(waiting_person, a, b);
                cout << "Seat is now allocated to " << waiting_person << " from the waiting queue.\n";
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Invalid seat number or seat is not booked.\n";
}

void view() {
    cout << "Seat Matrix (0=Empty, 1=Booked):\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void displayll() {
    if (head == NULL) {
        cout << "No bookings found.\n";
        return;
    }
    node* temp = head;
    while (temp != NULL) {
        cout << "Seat No: " << temp->seat_no << "\nName: " << temp->name << "\n" << endl;
        temp = temp->next;
    }
}

void viewWaitingList() {
    if (isempty()) {
        cout << "No one is in the waiting queue.\n";
        return;
    }

    cout << "Waiting List:\n";
    int i = f;
    while (true) {
        cout << q[i] << " ";
        if (i == r) break;
        i = (i + 1) % k;
    }
    cout << endl;
}

void clearAllBookings() {
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        delete temp;
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = 0;

    f = r = -1; // Fast way to clear the queue
    cout << "All bookings and waiting list cleared!\n";
}

int main() {
    int ch;
    while (1) {
        cout << "\n==> Movie Ticket Booking System <==\n";
        cout << "       1. View seats\n";
        cout << "       2. Book ticket\n";
        cout << "       3. View my booking status\n";
        cout << "       4. Cancel booking\n";
        cout << "       5. Display all bookings\n";
        cout << "       6. See waiting list\n";
        cout << "       7. Delete all bookings\n";
        cout << "       8. Exit\n";
        cout << "       Enter your choice: ";
        cin >> ch;
        cout << endl;

        switch (ch) {
            case 1:
                view();
                break;
            case 2: {
                if (housefull()) {
                    int k_opt;
                    cout << "All seats are booked\n";
                    cout << "Join waiting line? (If someone cancels, you get that seat)\n";
                    cout << "1. Yes\n2. No\nEnter your choice: ";
                    cin >> k_opt;
                    if (k_opt == 1) {
                        string q_name;
                        cout << "Enter your name: ";
                        cin >> q_name;
                        enq(q_name);
                    }
                    break;
                }

                int a, b;
                string name;
                cout << "Enter seat position (row & column): ";
                cin >> a >> b;
                cout << "Enter your name: ";
                cin >> name;
                book(name, a, b);
                break;
            }
            case 3: status(); break;
            case 4: cancel(); break;
            case 5: displayll(); break;
            case 6: viewWaitingList(); break;
            case 7: clearAllBookings(); break;
            case 8: return 0;
            default: cout << "Invalid choice, try again.\n";
        }
    }
}
