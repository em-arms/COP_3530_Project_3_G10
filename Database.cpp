
#include "Database.h"

void Database:: addHotel(string address_, string hotelName_, float averageRate_){
    Hotel* newHotel=new Hotel(address_, hotelName_, averageRate_);
    hotels[hotelName_]=newHotel;
}
void Database::addHotel(Hotel* hotel) {
    hotels[hotel->getName()]=hotel;
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

map <string, Hotel*> Database:: getHotels(){
    return hotels;
}