#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Database.h"
using namespace std;
int main() {
    ifstream file;

    file.open("C:/Users/finnl/Desktop/Emu's stuff/COP 3530 project 3/Version 1/Hotel_Reviews.csv", ios::in);
    string firstVal;
    string line, val;

    getline(file, line);

    Database koopaSearch=Database();

    while(file>>line){

        getline(file, line);
        //cout<<line;
        stringstream s(line);

        string address, reviewDate, hotelName, hotelRateS, negReview, posReview, reviewRateS, latS, lngS;
        float hotelRate, reviewRate;

        //getAdress
        getline(s,address, ',');

        //not important
        getline(s, val, ',');

        //reviewDate
        getline(s, reviewDate, ',');

        //hotelRating
        getline(s,hotelRateS , ',');
        hotelRate=stof(hotelRateS);

        //hotelName
        getline(s, hotelName, ',');

        //not important, reviewer nationality
        getline(s, val, ',');

        //negative review
        getline(s, negReview, ',');

        //not important, word count
        getline(s, val, ',');

        //not important, number of reviews
        getline(s, val, ',');

        //positive review
        getline(s, posReview, ',');

        //not important, word count
        getline(s, val, ',');

        //not important, number of reviews
        getline(s, val, ',');

        //rate given
        getline(s, reviewRateS, ',');
        reviewRate=stof(reviewRateS);

        //not important, tags
        getline(s, val, ']');

        //not important, days since review (not accurate)
        getline(s, val, ',');
        getline(s, val, ',');

        //latitude of hotel
        getline(s, latS, ',');

        //longitude of hotel
        getline(s, lngS, ',');



        ///create hotel/add review with info
        Hotel* currHotel=koopaSearch.findHotel(hotelName);
        if(currHotel== nullptr){
            //create hotel
            currHotel=new Hotel(address, hotelName, hotelRate);
            //add hotel to map
            koopaSearch.addHotel(currHotel);
        }

        currHotel->addReview(reviewDate, reviewRate, negReview, posReview);

    }

/*
    //iterate through hotels to see what is in database
    for(auto it=koopaSearch.getHotels().begin(); it!=koopaSearch.getHotels().end(); it++){
        cout<<it->first<<endl;
    }
*/
    int userChoice=-1;
    while(userChoice!=4){
        cout<<"menu"<<endl;
        cin>>userChoice;

        if(userChoice==1){
            string searchName;
            cout<<"enter name to search for: ";
            cin>>searchName;
            Hotel* searchedHotel=koopaSearch.findHotel(searchName);
            searchedHotel->printReviews();
        }
        if(userChoice==2){
            string searchCountry;
            cout<<"Enter the country to search for: ";
            cin>>searchCountry;
            koopaSearch.printByCountry(searchCountry);
        }
    }



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
