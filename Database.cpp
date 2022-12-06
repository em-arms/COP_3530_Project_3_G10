
#include "Database.h"

void Database:: addHotel(string address_, string hotelName_, float averageRate_){
    Hotel* newHotel=new Hotel(address_, hotelName_, averageRate_);
    hotels[hotelName_]=newHotel;
    hotelsByCountry[newHotel->getCountry()].push_back(newHotel);
    hotelsByCity[newHotel->getCity()].push_back(newHotel);
}
void Database::addHotel(Hotel* hotel) {
    hotels[hotel->getName()]=hotel;
    hotelsByCountry[hotel->getCountry()].push_back(hotel);
    hotelsByCity[hotel->getCity()].push_back(hotel);

}
void Database:: addReview(string hotelName, string date_, float rating_, string nReview_, string pReview_){
    hotels[hotelName]->addReview(date_, rating_, nReview_, pReview_);
}
Hotel* Database:: findHotel(string hotelName){
    if(hotelExists(hotelName) == true){
        return hotels[hotelName];
    }
    return nullptr;
}

bool Database:: hotelExists(string hotelName){
    auto it=hotels.find(hotelName);
    if(it != hotels.end()){
        return true;
    }
    return false;
}

unordered_map<string, Hotel*> Database:: getHotels(){
    return hotels;
}

void Database:: printByCountry(string countryName){
    vector<Hotel*> inCountry=hotelsByCountry[countryName];
    for(int i=0; i<inCountry.size(); i++){
        cout<<inCountry[i]->getName()<<endl;
    }
}
void Database:: printByCity(string cityName){
    vector<Hotel*> inCity=hotelsByCity[cityName];
    for(int i=0; i<inCity.size(); i++){
        cout<<inCity[i]->getName()<<endl;
    }
}