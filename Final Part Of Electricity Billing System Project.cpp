#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
struct Bill;
struct Receipt;
struct Customer;
enum Interface { MAIN__MENU, CUSTOMER__MENU, BILLING__MENU, REPORT__MENU};
struct Receipt { int receipt_no; string payment_date;float amount_paid;};
struct Bill { float fixed_charge = 100.0;  float energy_charge; float tax = 0.15;float total_amount;
string bill_date;string due_date; bool is_paid = false; Receipt receipt; };
struct Customer { string name; int meter_no; float units_consumed; Bill bill; };
struct PaymentHistory { int meter_no; string date; float amount; };
struct Statistics { int total_customers; float total_revenue;  int paid_bills;  int unpaid_bills;};
void displayUnpaidBills(Customer customers[], int n);
void displayPaymentHistory(Customer customers[], int n);
void displayCustomerStatistics(Customer customers[], int n);
void displayCustomers(Customer customers[], int n);
void displayCustomer(const Customer &customer);
void displayBill(const Customer &customer);
void calculateTotalBill(Customer &customer);
float calculateBill(float units);
void makePayment(Customer &customer);
void displayReceipt(const Customer &customer);
void displayMainMenu() {
    cout << "\n+------------------------------------+";
    cout << "\n|         MAIN MENU                  |";
    cout << "\n+------------------------------------+";
    cout << "\n| 1. Customer Management             |";
    cout << "\n| 2. Billing Operations              |";
    cout << "\n| 3. Reports                         |";
    cout << "\n| 4. Exit                            |";
    cout << "\n+------------------------------------+";
    cout<<endl;
}
void displayCustomerMenu() {
    cout << "\n+------------------------------------+";
    cout << "\n|      CUSTOMER MANAGEMENT           |";
    cout << "\n+------------------------------------+";
    cout << "\n| 1. Add New Customer                |";
    cout << "\n| 2. View All Customers              |";
    cout << "\n| 3. Search Customer                 |";
    cout << "\n| 4. Back to Main Menu               |";
    cout << "\n+------------------------------------+";
    cout<<endl;
}
void displayBillingMenu() {
    cout << "\n+------------------------------------+";
    cout << "\n|      BILLING OPERATIONS            |";
    cout << "\n+------------------------------------+";
    cout << "\n| 1. Make Payment                    |";
    cout << "\n| 2. Generate Receipt                |";
    cout << "\n| 3. View Bill Details               |";
    cout << "\n| 4. Back to Main Menu               |";
    cout << "\n+------------------------------------+";
    cout<<endl;
}
void displayReportMenu() {
    cout << "\n+------------------------------------+";
    cout << "\n|           REPORTS                  |";
    cout << "\n+------------------------------------+";
    cout << "\n| 1. Unpaid Bills Report             |";
    cout << "\n| 2. Payment History                 |";
    cout << "\n| 3. Customer Statistics             |";
    cout << "\n| 4. Back to Main Menu               |";
    cout << "\n+------------------------------------+";
    cout<<endl;
}
void displayUnpaidBills(Customer customers[], int n) {
    cout << "\n--- UNPAID BILLS REPORT ---\n";
    bool found = false;
    cout << setw(15) << "Meter No" << setw(20) << "Customer Name"  << setw(15) << "Amount" << endl;
    cout << string(50, '-') << endl;
    for(int i = 0; i < n; i++) {
        if(!customers[i].bill.is_paid) {
cout << setw(15) << customers[i].meter_no << setw(20) << customers[i].name
<< setw(15) << fixed << setprecision(2) << customers[i].bill.total_amount << endl;
            found = true;
        }
    }
    if(!found) { cout << "\nNo unpaid bills found!\n";}
}
void displayPaymentHistory(Customer customers[], int n) {
    cout << "\n----PAYMENT HISTORY -----\n";
    bool found = false;
    cout << setw(15) << "Receipt No" << setw(15) << "Meter No" << setw(20) << "Customer Name" << setw(15) << "Amount" 
    << setw(15) << "Date" << endl;
    cout << string(40, '-') << endl;
    for(int i = 0; i < n; i++) {
        if(customers[i].bill.is_paid) {
cout << setw(15) << customers[i].bill.receipt.receipt_no  << setw(15) << customers[i].meter_no 
<< setw(20) << customers[i].name<< setw(15) << fixed << setprecision(2) << customers[i].bill.receipt.amount_paid
<< setw(15) << customers[i].bill.receipt.payment_date << endl;
            found = true;
        }
    }
    if(!found) { cout << "\nNo payment history found!\n";}
}
void displayCustomerStatistics(Customer customers[], int n) {
    Statistics stats = {0, 0.0, 0, 0};
    stats.total_customers = n;    
    for(int i = 0; i < n; i++) {
        if(customers[i].bill.is_paid) {
            stats.paid_bills++;
            stats.total_revenue += customers[i].bill.total_amount;
        } else {  stats.unpaid_bills++;}
    }
    cout << "\n--- CUSTOMER STATISTICS ---\n";
    cout << "Total Customers: " << stats.total_customers << endl;
    cout << "Paid Bills: " << stats.paid_bills << endl;
    cout << "Unpaid Bills: " << stats.unpaid_bills << endl;
    cout << "Total Revenue: Birr. " << fixed << setprecision(2) << stats.total_revenue << endl;
    cout << "Average Bill Amount: Birr. " << (n > 0 ? stats.total_revenue/n : 0) 
         << endl;
}
void displayReceipt(const Customer &customer) {
    cout << "\n--- PAYMENT RECEIPT ---";
    cout << "\nReceipt No: " << customer.bill.receipt.receipt_no;
    cout << "\nCustomer Name: " << customer.name;
    cout << "\nMeter Number: " << customer.meter_no;
    cout << "\nPayment Date: " << customer.bill.receipt.payment_date;
    cout << "\nAmount Paid: Birr. " << customer.bill.receipt.amount_paid;
    cout << "\n-----------------\n";
}
void makePayment(Customer &customer) {
    if(customer.bill.is_paid) {
        cout << "\nBill is already paid!";
        return;
    }    
    cout << "\nTotal Amount Due: Birr. " << customer.bill.total_amount;
     float payment_amount;
    do {
        cout << "\nEnter Payment Amount: Birr. "; cin >> payment_amount;
        if(payment_amount != customer.bill.total_amount) {
            cout << "\nPlease pay the exact amount!";
        }
    } while(payment_amount != customer.bill.total_amount);
    string payment_date;
    bool validDate;
    do {
        cout << "\nEnter Payment Date (DD/MM/YYYY): ";  cin >> payment_date;
        validDate = (payment_date.length() == 10 && payment_date[2] == '/' && payment_date[5] =='/');           
        if(!validDate) {
            cout << "\nInvalid date format! Use DD/MM/YYYY";
        }
    } while(!validDate);
    char confirm;
    cout << "\nConfirm payment (Y/N)? "; cin >> confirm;
    if(confirm == 'Y' || confirm == 'y') {
        customer.bill.is_paid = true;
        customer.bill.receipt.receipt_no = customer.meter_no * 1000 + (time(0) % 1000);
        customer.bill.receipt.amount_paid = payment_amount;
        customer.bill.receipt.payment_date = payment_date;
         cout << "\nPayment successful!"; displayReceipt(customer);
    } else {
        cout << "\nPayment cancelled!";
    }
}
float calculateBill(float units) {
    float energy_charge;
    if (units <= 100) {
        energy_charge = units * 1.00;} else if (units <= 200) {
        energy_charge = (100 * 1.00) + ((units - 100) * 2.00); } else if (units <= 300) {
        energy_charge = (100 * 1.00) + (100 * 2.00) + ((units - 1.00) * 3.00);} else {
        energy_charge = (100 * 1.00) + (100 * 2.00) + (100 * 3.00) + ((units - 300) * 4.00);}
    return energy_charge;
}
void calculateTotalBill(Customer &customer) {
    customer.bill.energy_charge = calculateBill(customer.units_consumed);
    float subtotal = customer.bill.fixed_charge + customer.bill.energy_charge;
    float tax_amount = subtotal * customer.bill.tax;
    customer.bill.total_amount = subtotal + tax_amount;
}
void displayBill(const Customer &customer) {
    cout << "\n----- ELECTRICITY BILL ----";
    cout << "\nCustomer Name: " << customer.name;
    cout << "\nMeter Number: " << customer.meter_no;
    cout << "\n-----------------------";
    cout << "\nUnits Consumed: " << customer.units_consumed;
    cout << "\nFixed Charge: Birr. " << customer.bill.fixed_charge;
    cout << "\nEnergy Charge: Birr. " << customer.bill.energy_charge;
    cout << "\nSub Total: Birr. " << (customer.bill.fixed_charge + customer.bill.energy_charge);
    cout << "\nTax (15%): Birr. " << ((customer.bill.fixed_charge + customer.bill.energy_charge) * customer.bill.tax);
    cout << "\n-----------------------";
    cout << "\nTotal Amount: Birr. " << customer.bill.total_amount;
    cout << "\nStatus: " << (customer.bill.is_paid ? "PAID" : "UNPAID");
    cout << "\n-------------------------\n";
}
void inputCustomer(Customer &c) {
    cout << "\nEnter Customer Name: "; cin.ignore(); getline(cin, c.name);
    cout << "Enter Meter Number: "; cin >> c.meter_no;
    cout << "Enter Units Consumed: ";cin >> c.units_consumed;calculateTotalBill(c); 
}
void displayCustomer(const Customer &customer) {
    cout << "\n--- CUSTOMER DETAILS ---";
    cout << "\nName: " << customer.name;
    cout << "\nMeter Number: " << customer.meter_no;
    cout << "\nUnits Consumed: " << customer.units_consumed; displayBill(customer);
    if(customer.bill.is_paid) { displayReceipt(customer);}
}
void displayCustomers(Customer customers[], int n) {
    cout << "\n--- ALL CUSTOMERS ---\n";
    for(int i = 0; i < n; i++) {
        cout << "\nCustomer #" << (i+1); displayCustomer(customers[i]);
    }
}
int searchCustomer(Customer customers[], int n, int meter) {
    for(int i = 0; i < n; i++) {
        if(customers[i].meter_no == meter) {
            return i;
        }
    }
    return -1;
}
int main() {
    Customer customers[100]; int n = 0 , choice;
    Interface currentInterface = MAIN__MENU;
    do {
        system("cls"); 
        switch(currentInterface) {
            case MAIN__MENU:
                displayMainMenu(); cin >> choice;
                switch(choice) {
                    case 1: currentInterface = CUSTOMER__MENU; break;
                    case 2: currentInterface = BILLING__MENU; break;
                    case 3: currentInterface = REPORT__MENU; break;
                    case 4: cout << "\nExiting program..."; return 0;
                }break;
                case CUSTOMER__MENU:
                displayCustomerMenu(); cin >> choice;
                switch(choice) {
                    case 1: 
                        if(n < 100) {
                            inputCustomer(customers[n++]);
                        } else {
                            cout << "\nMaximum customer limit reached!";
                        } break;
                    case 2: 
                        if(n > 0) displayCustomers(customers, n);
                        else 
                        cout << "\nNo customers found!"; 
                        break;
                    case 3: {
                        int meter;
                        cout << "\nEnter Meter Number: "; cin >> meter;
                        int index = searchCustomer(customers, n, meter);
                        if(index != -1) displayCustomer(customers[index]);
                        else
                         cout << "\nCustomer not found!";
                          break;
                    }
                    case 4: currentInterface = MAIN__MENU; break;
                } break;
            case BILLING__MENU:
                displayBillingMenu();  cin >> choice;
                switch(choice) {
                    case 1: {
                        int meter;
                        cout << "\nEnter Meter Number: ";  cin >> meter;
                        int index = searchCustomer(customers, n, meter);
                        if(index != -1) makePayment(customers[index]);
                        else cout << "\nCustomer not found!"; 
                         break;
                    }
                    case 2: {
                        int meter;
                        cout << "\nEnter Meter Number: ";  cin >> meter;
                        int index = searchCustomer(customers, n, meter);
                        if(index != -1 && customers[index].bill.is_paid) displayReceipt(customers[index]);
                        else
                         cout << "\nCustomer not found or bill not paid!";
                          break;
                    }
                    case 3: {
                        int meter;
                        cout << "\nEnter Meter Number: ";  cin >> meter;
                     int index = searchCustomer(customers, n, meter);
                        if(index != -1) displayBill(customers[index]); else cout << "\nCustomer not found!"; break;
                    }
                    case 4: currentInterface = MAIN__MENU; break;
                } break;
               case REPORT__MENU:
    displayReportMenu();  cin >> choice;
    switch(choice) {
        case 1:  displayUnpaidBills(customers, n);break;
        case 2:displayPaymentHistory(customers, n); break;
        case 3: displayCustomerStatistics(customers, n); break;
        case 4:  currentInterface = MAIN__MENU; break;
        default: cout << "\nInvalid choice!"; break;
    }break;
        }
        cout << "\nPress Enter to continue...;)"; cin.ignore(); cin.get();  
    } while(true);
    return 0;
}
