#include <iostream>
#include <map>
#include "Hotel.h"
using namespace std;
class Database {
private:
    //map object?
    map <string, Hotel*> hotels;    //name, hotel
    int numLocations;


public:
    void addHotel(string address_, string hotelName_, float averageRate_);
    void addHotel(Hotel* hotel);
    void addReview(string hotelName, string date_, float rating_, string nReview_, string pReview_);
    Hotel* findHotel(string hotelName);
    bool hotelExists(string hotelName);
    map <string, Hotel*> getHotels();


};



