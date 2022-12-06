
#include "mapDatabase.h"

void mapDatabase:: addHotel(string address_, string hotelName_, float averageRate_){
    Hotel* newHotel=new Hotel(address_, hotelName_, averageRate_);
    hotels[hotelName_]=newHotel;
    hotelsByCountry[newHotel->getCountry()].push_back(newHotel);
    hotelsByCity[newHotel->getCity()].push_back(newHotel);
}
void mapDatabase::addHotel(Hotel* hotel) {
    hotels[hotel->getName()]=hotel;
    hotelsByCountry[hotel->getCountry()].push_back(hotel);
    hotelsByCity[hotel->getCity()].push_back(hotel);

}
void mapDatabase:: addReview(string hotelName, string date_, float rating_, string nReview_, string pReview_){
    hotels[hotelName]->addReview(date_, rating_, nReview_, pReview_);
}
Hotel* mapDatabase:: findHotel(string hotelName){
    if(hotelExists(hotelName) == true){
        return hotels[hotelName];
    }
    return nullptr;
}

bool mapDatabase:: hotelExists(string hotelName){
    auto it=hotels.find(hotelName);
    if(it != hotels.end()){
        return true;
    }
    return false;
}

unordered_map<string, Hotel*> mapDatabase:: getHotels(){
    return hotels;
}

void mapDatabase:: printByCountry(string countryName){
    for(int i=0; i<hotelsByCountry[countryName].size(); i++){
        cout<<hotelsByCountry[countryName][i]->getName()<<endl;
    }
}
void mapDatabase:: printByCity(string cityName){
    for(int i=0; i<hotelsByCity[cityName].size(); i++){
        cout<<hotelsByCity[cityName][i]->getName()<<endl;
    }
}