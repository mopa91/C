/**********************************************************************
Matr.-Nr:                     3091685
Nachname/Surname:             Parandeh
Vorname/Given name:           Mohammad
Uni-Email:                    mohammad.parandeh@stud.uni-due.de
Studiengang/Course of studis: 3
**********************************************************************/
#include<cstdlib>
#include<iostream>
#include <iomanip>
#include<string>
using namespace std;

class DayOfYear
{
  private:
  //year starting from January 1st to December 31
  short unsigned int dayOfYear,year;
  //a static constant for storing the number of the days 
  static const int days[13];
  public:
  DayOfYear(int dayOfYear = 1,int year = 365):dayOfYear(dayOfYear),year(year){};
   // a public constructor to initialise attributes 
  DayOfYear(int day, int month, int year):dayOfYear(day + days[month - 1]),year(year){};
  //returning the value of dayOfYear
  int get_dayOfYear()
  {
    return dayOfYear;
  }
  // a public member increment a date exactly one day and we use postfix for our method
  DayOfYear operator++(int) 
  {
		DayOfYear dayofyear1(*this);
		if (dayofyear1.dayOfYear == 365)
    {
			dayofyear1.dayOfYear = 1; 
			dayofyear1.year += 1; 
		}else
    {
			dayofyear1.dayOfYear += 1;
		}
		return dayofyear1;
	}
  //inputting a date in ISO format
  // doy = dayOfYear
  friend istream& operator>>(istream& i, DayOfYear &doy)
  {
    int day,month,year;
    char ch; // to read and skip the minus sign in input of the date
    i >> year >> ch >> month >> ch >> day;
    doy.dayOfYear = day+doy.days[month-1];
    doy.year = year;
    return i;
  }
  //outputting a date in ISO format
  friend ostream& operator<<(ostream& o, DayOfYear &doy)
  {
    int day,month,year;
    year = doy.year;  
    // we try to find month from dayofyear, if we do not use this integer than we can not print month appropriately     
    int extra = -1;
    // calculate month and day in ISO form
    for(int i = 0; i<=12; i++) 
      {
        extra++;
        if(doy.dayOfYear > doy.days[i] && doy.dayOfYear <= doy.days[i+1])
        break;    
      }
      day = doy.dayOfYear - doy.days[extra];
      month = extra + 1; 
      return o     << setw(4) << setfill('0') << year
            << '-' << setw(2) << setfill('0') << month
            << '-' << setw(2) << setfill('0') << day;
  }
};
// initialised days array outside of the class
const int DayOfYear::days[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

class Vehicle
{
  private:
  // attribute for an identification number of the vehicle
  const int no;
  string model;
  // attribute for the rental price of one day of the vehicle
  float price24h;
  public:
  Vehicle(int no,string model,float price24h):no(no),model(model),price24h(price24h){};
  virtual ~ Vehicle()
  {
    cout << "destructor called";
  }
  int get_no()
  {
    return no;
  }
  string get_model()
  {
    return model;
  }
  float get_price(int rentalDays)
  {
    return rentalDays * price24h;
  }
  virtual void print(){};
};

class Bike:public Vehicle
{
  public:
  // a public constructor to initialise attributes and the daily rental price shall always be 9,99 EUR
  Bike(int no,string model):Vehicle(no,model,9.99){};
  virtual void print()
  {
    cout << get_no() << " : " << get_model() << " (Bike) " << endl;
  }
};

class EMotorVehicle: public Vehicle
{
  public:
  // a public constructor to initialise the three attributes
  EMotorVehicle(int no,string model,float price24h):
  Vehicle(no,model,price24h){};

  virtual bool is_streetLegal()
  {
    if(false)
    {
      return false;
    }else
    {
      return true;
    }
  }
  virtual void print()
  {
    cout << get_no() << " : " << get_model();
    if(is_streetLegal() == false)
    {
      cout << "(not street legal)";
    } 
  } 
};

class EBike:public EMotorVehicle
{
  public:
  // a public constructor to initialise the three attributes with default value 29.99 EUR for price
  EBike(int no,string model,float price24h = 29.99):
  EMotorVehicle(no,model,price24h){};

  virtual bool is_streetLegal()
  {
    return true;
  }
  // a public method print calling the same name method
  virtual void print ()
  {
    EMotorVehicle::print();
    cout << " (EBike) "  << endl;
  }
};

class EScooter:public EMotorVehicle
{
  private:
  // a Boolean for showing us that the E-scooter is street legal or not
  bool streetLegal;
  public:
  // a public constructor to initialise the four attributes
  EScooter(int no,string model,float price24h = 19.99,bool streetLegal = false):EMotorVehicle(no,model,price24h), streetLegal(streetLegal){};

  virtual bool is_streetLegal()
  {
    return streetLegal;
  }
  virtual void print ()
  {
    EMotorVehicle::print();
    cout << "(EScooter)"   << endl;
  }
};

class Rental
{
  private:
  //storing a unique reservation number for the rental
  const int no;
  // storing the starting day of a rental
  DayOfYear from;
  // storing the number of rental days
  int days;
  //  storing the renting person
  string customer;
  static int last_no;
  public:
  // a public constructor to initialise the three attributes
  Rental(string customer,DayOfYear from,int days = 1):customer(customer),from(from),days(days),no(last_no +=1){};
  // a method for returning number of rental days
  int get_days()
  {
    return days;
  }
  // the following two method returning the start and end/return date of the rental of type DayOfYear
  DayOfYear get_from()
  {
    return from;
  }
  DayOfYear get_until()
  {
    DayOfYear increment = get_from();
    // we get the last date of rental and using a loop for increase first day of rental
    for(int i = 0; i < get_days(); i++)
      {
        increment++;
      }
      // return the last day of rental
    return increment;
  }
  void print()
  {
    DayOfYear doy = get_until();
    cout << from << " to " << doy << ", rental no " << no << " for " << customer;
  }
};
 int Rental::last_no = 0;
// class for a rental reservation schedule for a vehicle with a maximum of one year 
class Schedule
{
  private:
  // an attribute type pointer to Vehicle this schedule belongs to
  Vehicle *vehicle;
  // store a pointer to an object
  Rental *year[365];
  // an attribute set up a list of several to rent vehicles
  Schedule *next;
  public:
  // a public constructor to initialise the attributes
  Schedule(Vehicle* vehicle):vehicle(vehicle)
  {
    next = nullptr;
    for(int i = 0 ; i<=365 ; i++)
    {
      year[i] = nullptr;
    }
  }
  Vehicle* get_vehicle()
  {
    return vehicle;
  }
  Schedule* get_next()
  {
    return next;
  }
  void set_next(Schedule *schedule)
  {
    next = schedule;
  }
  // this boolean check whether the whole time period will be free or not
  bool isFree(DayOfYear doy,int t) 
    {
      bool check = false;
      // use for loop to check  rentals in array of year
      for(int i = 0; i < t; i++)   
        {
          // check whether the Vehicle is free in the wanted period or no if it is nullptr we dont have free node and we can not reserv that
          if(year[doy.get_dayOfYear() - 1 + i] == nullptr)
          check = true;    
        }
      return check;
    }
    // a public constructor to initialise the three attributes
    float book(string customer,DayOfYear doy,int t)   
    {
      Rental* rental = new Rental(customer, doy, t);
      // tring to figure out how long the rental is planned and the index into the array for the start day of the rental can be calculated by sending a message get_dayOfYear() to the date object  
      int howLong = doy.get_dayOfYear() - 1;
      // a new object of type Rental on the heap shall be generated and its address being stored in array year for each rental day in a loop
      for(int i = howLong; i < doy.get_dayOfYear() + t; i++)
      {
        year[i]  = rental;    
      }
      // a floating point return value and our return value shall be the price for this rental determined by a message get_price sent to the vehicle
      return  vehicle->get_price(t);
    }
    void print(DayOfYear doy)  
    {
      vehicle->print();
      // send a message print to the reservation object - if it exists, i.e. it is not a null pointer - for this day in the respective array element
      for(int i = 0; i < 365; i++)
        {
          // year hat a type of Rental so we have access to Rental and get_from hat type of DayofYear so now we can return our days and now we saying if this two is equal print that from heap
          if( year[i] != nullptr && year[i]->get_from().get_dayOfYear() == doy.get_dayOfYear())
            {
              year[i]->print();
              cout << endl;
              break;
            }
        }
    }
    // printing all rentals for the vehicle stored in array year together with their prices
    void print()  
      {
        // we use that in loop and we want to increase the loop variable with this method we can print that once not again and again.
        int temp;
        cout << "SCHEDULE FOR ";
        // sending a message print to the vehicle after that print all of them
        vehicle->print();
        for(int i = 0; i < 365; i++)
        {
          if(year[i] != nullptr)
            {
              // printing all rentals for the vehicle stored in array year together with their prices
              temp = year[i]->get_days();
              year[i]->print();
              cout << " total: " << vehicle->get_price(year[i]->get_days()); 
              cout << endl;
              i += temp;
            }
        }
      }
};

class Agency 
{
  private:
  // an attribute for the profit percentage of the agency for each rental.
  float profitPercent;
  // an attribute for the summed up profit of the agency
  float profit;
  // two pointer of type Schedule as pointers to the first and the last element of a list of schedules for all the vehicles of the agency
  Schedule *head,*last;
  public:
  Agency():profitPercent(20),profit(0),head(nullptr),last(nullptr){}
  float get_profit()
  {
    return profit;
  }
  void set_profitPercentage(float a)
  {
    profitPercent = a;
  }
  void add(Vehicle* vehicle)
    {
      // our schedule constructor had a pointer type of vehicle so we can give our parameter to schedule
      Schedule* schedule1 = new Schedule(vehicle);
      // tring to allocate a new object of type Schedule on heap for this vehicle and appending it at the end of the list
      if(head == nullptr)
      {
        head = schedule1;
      }else{
        last = head;
        while(last->get_next() != nullptr)                     
          {
            last = last->get_next();  
          }
        last->set_next(schedule1);  
        }
    }
    protected:
  // a protected method with an integer parameter
  Schedule* searchFor(int a)
  {
    Schedule* schedule1 = head;
    // we using loop because we searching in the list of schedules for the vehicle with the number given by the parameter and tring to returning that
    while(schedule1 != nullptr)
      {
        if(schedule1->get_vehicle()->get_no() == a)   
        break;   
        else{
        schedule1 = schedule1->get_next();      
        }        
      }
    return schedule1;
  }
  public:
  // a public method with name isFree with a first integer parameter for a vehicle number, a date of type DayOfYear as second parameter as start day of a planned rental, an integer number of days as third parameter, how long the rental is planned, and a Boolen return type. The method 
  bool isFree(int number, DayOfYear d, int days)
  {
    // we check that whether the vehicle will be free at the desired time period or not. Therefore send to the object of type Schedule, which is returned by the search function in the previous item, a message isFree and return its value.
    return searchFor(number)->isFree(d,days);
  }
  float book(int number, string customer, DayOfYear d, int days)
  {
    // our method shall book the vehicle for the customer. Therefore send to the object of type Schedule, which is returned by the search function in the previous item, a message book. Calculate the profit by the profit percentage and the returned price value and add it to profit. Afterwards return the price
    // vehicle Book Price = vbp
    float vbp = searchFor(number)->book(customer,d,days);
    profit = profit + ((vbp * profitPercent)/100);
    return vbp; 
  }
  int chooseVehicle()    
  {
    // a list of the vehicles of all schedules shall be written onto standard character
    int number;
    Schedule* scheduale1 = head;
    while(scheduale1 != nullptr)
    {
      scheduale1->get_vehicle()->print();      
      scheduale1 = scheduale1->get_next();        
    }
    cout << "choose vehicle no: ";
    // a vehicle number read from input and returned
    cin >> number;
    return number;
  }
  void print(DayOfYear doy)
  {
    // our function shall output all reservations of all schedules at this date
    Schedule* scheduale1 = head;
    while(scheduale1 != nullptr)
    {
      scheduale1->print(doy);  
      scheduale1 = scheduale1->get_next();
    }
  }
  void print()
  {
    // our function shall output all reservations of all schedules in the list as well as the value of profit
    Schedule* scheduale1 = head;
    while(scheduale1 != nullptr)
    {
      scheduale1->print();
      scheduale1 = scheduale1->get_next();
    }
    cout << "profit: " << fixed << setprecision(2) << profit << " EUR" << endl;
  }
};

int main(void)
{ 
	char charKey;
  Agency agency1;
  DayOfYear today(01, 01, 2021);
	DayOfYear tomorrow = today++; 
  // we define all just once and use these varialbels separately in every case of switch
	float profit;
  int vCounter = 0, bCounter = 0;
  Vehicle* vehicle;
	int n;
	int eBCounter = 0, eSCounter = 0; 

	do {
    cout << "--------------------------------" << endl;
    cout << "MENU" << endl;
    cout << "A end of simulatio" << endl;
    cout << "B set new simulation date" << endl;
    cout << "C new rental manually" << endl;
    cout << "D print rental of today " << today << endl;
    cout << "E print rental of tomorrow " << tomorrow << endl;
    cout << "F print all rentals" << endl;
    cout << "G print agency profit" << endl;
    cout << "H set agency profit percent" << endl;
    cout << "I add bikes" << endl;
    cout << "J add E-bikes" << endl;
    cout << "K add E-scooters" << endl;
    cout << "L new rental simulation" << endl;
    cout << "your choice: ";
		cin >> charKey;

		switch (charKey) {
		case 'a': 
    {
			cout << " End of simulation ";
			break;
		}
		case 'b': 
    {
			cout << "Input date of today: ";
			cin >> today;
			tomorrow = today++;
			break;
		}
		case 'c': 
    {
      DayOfYear doy;
			int vNum = agency1.chooseVehicle();
			string name;
			int t;
			cout << "day of rental: ";
			cin >> doy;
			cout << "number of days: ";
			cin >> t;

			if (agency1.isFree(vNum, doy, t))
			{
				cout << "input data vehicle renter name: ";
				cin >> name;
				cout << "booked, price for this rental: " << agency1.book(vNum, name, doy, t) << endl;
			}
			else {
				cout << "sorry your choice is already booked." << endl;
			}
			break;
		}
		case 'd': 
    {
			cout << "SCHEDULE FOR " << today << endl;
			agency1.print(today);
			break;
		}
		case 'e': 
    {
			cout << "SCHEDULE FOR " << tomorrow << endl;
			agency1.print(tomorrow);
			break;
		}
		case 'f': 
    {
			agency1.print();
			break;
		}
		case 'g': 
    {
			cout << "agency profit: " << agency1.get_profit() << " EUR"  << endl;
			break;
		}
		case 'h': 
    {
			cout << "agency profit percent: ";
			cin >> profit;
			agency1.set_profitPercentage(profit);
			break;
		}
		case 'i': 
    {
			cout << "How many Bikes in this simulation? ";
			cin >> n;

			for (int i = 0; i < n; i++) 
      {
        // for address, increase the counter by 1 to keep track of vehicle numbers
				vCounter++;
        // bCounter+1 menas that this 1 helping us to have the vehicles in order
				string s = "City " + to_string(bCounter + 1); 
				vehicle = new Bike(vCounter, s);
				agency1.add(vehicle);
        // we increase that to get the right name of model
				bCounter++; 
			}
			break;
		}
		case 'j': 
    {
			cout << "How many EBike in this simulation? ";
			cin >> n;
			for (int i = 0; i < n; i++) 
      {
				vCounter++;
				string s = "Trekky " + to_string(eBCounter + 1);
				vehicle = new EBike(vCounter, s);
				agency1.add(vehicle);
				eBCounter++;
			}
			break;
		}
		case 'k':
    {
			cout << "How many EScooter in this simulation? ";
			cin >> n;

			for (int i = 0; i < n; i++) 
      {
				vCounter++;
				string s = "Scooty " + to_string(eSCounter + 1);
				vehicle = new EScooter(vCounter, s);
				agency1.add(vehicle);
				eSCounter++;
			}
			break;
		}
		default:
			cout << "we do not have a such a character";
		} 
	} while (charKey != 'a');
  
    return 0;
}
