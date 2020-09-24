#include <iostream>
using namespace std;

class Person{
    protected:
    string name;
    string surname;
    public:
    Person(); //default constructor
    Person(string, string);// normal constructor
}; // BASE CLASS OF OWNER AND COURIER CLASS

class Owner: public Person{
    private:
    float ownership;
    public:
    Owner();
    Owner(string, string);
    void setOvnership(int n){this->ownership = n;}
    void print_owner();
}; // SUB CLASS OF PERSON CLASS

class Courier: public Person{
    private:
    string vehicle;
    int capacity;
    public:
    Courier(); // default constructor
    Courier(string, string, string); // normal constructor
    Courier(const Courier &); // copy constructor
    bool operator==(Courier &);
    void print_courier();
    int get_capacity(){return capacity;};
}; // SUB CLASS OF PERSON CLASS

class Business{
    private:
    string nameB;
    string adressB;
    Owner *owners; // a dynamic array of Owner
    Courier *couriers;
    int num_of_owners;
    static int num_of_couriers;
    public:
    Business();
    Business(string, string, Owner *&, int);
    ~Business();
    void hire_courier(Courier &);
    void fire_courier(Courier &);
    void list_couriers();
    void list_owners();
    int calculate_shipment_capacity();
    void operator()();
    Courier & operator[](int);
};

int Business::num_of_couriers = 0;

Person::Person(){ // Default constructor of Person class
    name = "noname";
    surname = "nosurname";
}

Person::Person(string in_name, string in_surname){
    name = in_name;
    surname = in_surname;
}

Owner::Owner() // default constructor of Owner class
:Person() // initialize Person
{}

Owner::Owner(string in_name, string in_surname) // normal constructor of Owner class
:Person(in_name, in_surname) // initialize Person
{}

void Owner::print_owner(){
    cout << name << " " << surname << " " << ownership << endl; 
}

Courier::Courier() // default constructor of Courier class
:Person() // initialize Person
{
    vehicle = "novehicle";
    capacity = 0;
}

Courier::Courier(string in_name, string in_surname, string in_vehicle) // normal constructor of Courier class
:Person(in_name, in_surname) // initialize Person
{
    while(in_vehicle != "car" && in_vehicle != "motorcycle" && in_vehicle != "bicycle"){
        cout << "Wrong vehicle! Please enter car, motorcycle, or bicycyle" << endl;
        cin >> in_vehicle;
    }
    vehicle = in_vehicle;
    if(in_vehicle == "car") capacity = 200;
    else if(in_vehicle == "motorcycle") capacity = 35;
    else if(in_vehicle == "bicycle") capacity = 10;
}

Courier::Courier(const Courier &c){
    name = c.name;
    surname = c.surname;
    vehicle = c.vehicle;
    capacity = c.capacity;
}

bool Courier::operator==(Courier &c){
    if(name == c.name && surname == c.surname && vehicle == c.vehicle && capacity == c.capacity) return true;
    else return false;
}

void Courier::print_courier(){
    cout << name << " " << surname << " " << vehicle << endl;
}

Business::Business(){
    nameB = "noname";
    adressB = "noadress";
}

Business::Business(string in_name, string in_adress, Owner *&o, int n){
    nameB = in_name;
    adressB = in_adress;
    num_of_owners = n;
    owners = new Owner[num_of_owners];
    for (int i = 0; i < num_of_owners; i++){
        owners[i] = o[i];
        owners[i].setOvnership(100/n);
    }
}

Business::~Business(){
    delete [] couriers;
    delete [] owners;
}

void Business::list_owners(){
    for (int i = 0; i < num_of_owners; i++) owners[i].print_owner();    
}

void Business::list_couriers(){
    for (int i = 0; i < num_of_couriers; i++) couriers[i].print_courier();
}

void Business::operator()(){
    cout << nameB << " " << adressB << " " << endl;
    list_owners();
    list_couriers();
}

Courier & Business::operator[](int index){
    while(index < 0 || index >= num_of_couriers){
        cout << "Wrong index! Please enter a valid index." << endl;
        cin >> index;
    }
    return couriers[index];
}

int Business::calculate_shipment_capacity(){
    int total = 0;
    for (int i = 0; i < num_of_couriers; i++) total += couriers[i].get_capacity();
    return total;
}

void Business::hire_courier(Courier &c){
    if(num_of_couriers == 0){
        num_of_couriers++;
        couriers = new Courier[1];
        couriers[0] = c;
        return;
    }
    else {
        int i;
        Courier *temp = new Courier[num_of_couriers];
        for (i = 0; i < num_of_couriers; i++) temp[i] = Courier(couriers[i]);
        delete [] couriers;
        num_of_couriers++;
        couriers = new Courier[num_of_couriers]; 
        for (i = 0; i < num_of_couriers-1; i++) couriers[i] = temp[i];
        couriers[i] = c;
        delete [] temp;   
    }
}

void Business::fire_courier(Courier &c){
    if(num_of_couriers == 0){
        cout << "There is no any couriers yet" << endl;
        return;
    }
    int i;
    for (i = 0; i < num_of_couriers; i++){
        if(couriers[i] == c) break;
    }
    if(i == num_of_couriers){
        cout << "Wrong courier!  No such person works in this business" << endl;
        return;
    }
    int index = i;
    Courier *temp = new Courier[num_of_couriers-1];
    for (i = 0; i < index; i++) temp[i] = couriers[i];
    if(index + 1 != num_of_couriers){
        for (; i < num_of_couriers-1; i++) temp[i] = couriers[i+1];
    }
    delete [] couriers;
    num_of_couriers--;
    couriers = new Courier[num_of_couriers];
    for ( i = 0; i < num_of_couriers; i++) couriers[i] = temp[i];
    delete [] temp;
}

int main(){
    // Create owners of the business
    //Constructor parameters: name, surname
    Owner o1 = Owner("Owner_name1", "surname1");
    Owner o2 = Owner("Owner_name2", "surname2");
    Owner* owner_arr = new Owner[2];
    owner_arr[0] = o1;
    owner_arr[1] = o2;    

    //Crete the business itself
    //Constructor parameters: name, address, owner_array, number_of_owners
    Business atlas = Business("Atlas", "Maslak Istanbul/Turkey", owner_arr, 2);
    // Print owner info to screen: name, surname, ownership
    atlas.list_owners();
    // Add new employees
    // Constructor parameters: name, surname, vehicle_type
    Courier c1 = Courier("Courier", "surname1", "car");
    Courier c2 = Courier("Courier", "surname2", "motorcycle");
    Courier c3 = Courier("Courier", "surname3", "motorcycle");    

    atlas.hire_courier(c1);
    atlas.hire_courier(c2);
    atlas.hire_courier(c3);


    // Print business info to screen
    // Name, address, owners, couriers
    atlas();

    // Get courier with index 1 and remove it from the list/array
    Courier cour = atlas[1];
    atlas.fire_courier(cour);
    
    // Print remaining couriers
    atlas.list_couriers();
    
    // Print current maximum shipment capacity
    std::cout << atlas.calculate_shipment_capacity() << std::endl;

    delete [] owner_arr;
    return 0;
}