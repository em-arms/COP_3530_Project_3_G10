#include <iostream>
#include <map>
#include <unordered_map>
#include "Hotel.h"
using namespace std;
class Database {
private:
    //map object?
    unordered_map<string, Hotel*> hotels;    //name, hotel
    int numLocations;
    unordered_map<string, vector<Hotel*>> hotelsByCountry;
    unordered_map <string, vector<Hotel*>> hotelsByCity;

public:
    void addHotel(string address_, string hotelName_, float averageRate_);
    void addHotel(Hotel* hotel);
    void addReview(string hotelName, string date_, float rating_, string nReview_, string pReview_);
    Hotel* findHotel(string hotelName);
    bool hotelExists(string hotelName);
    unordered_map<string, Hotel*> getHotels();
    void printByCountry(string countryName);
    void printByCity(string cityName);


};



