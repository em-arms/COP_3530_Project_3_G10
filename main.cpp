#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "B+ Tree.h"
#include "Database.h"

using namespace std;

int main() {
    ifstream file;

    file.open("C:/Users/finnl/Desktop/Emu's stuff/COP 3530 project 3/Version 1/Hotel_Reviews.csv", ios::in);
    string firstVal;
    string line, val;

    getline(file, line);

    Database koopaSearch=Database();
    nameBPTree koopaTree;

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
            koopaTree.insert(currHotel);
        }

        currHotel->addReview(reviewDate, reviewRate, negReview, posReview);

    }

/*
    //iterate through hotels to see what is in database
    for(auto it=koopaSearch.getHotels().begin(); it!=koopaSearch.getHotels().end(); it++){
        cout<<it->first<<endl;
    }
*/
    file.close();
    
    int userChoice=-1;
    int structureChoice=-1;
    while(userChoice!=4){
        cout<<"1. Search by Name of the Hotel and Print Reviews\n2. Search by Country \n3. Search by City\n4. Quit "<<endl;
        cin>>userChoice;
        if(userChoice==4){
            break;
        }
        cout<<"1.Use the B+ tree\n2.Use the map"<<endl;
        cin>>structureChoice;

        if(userChoice==1){
            string searchName;
            cout<<"enter name to search for: ";
            getline(cin >> ws, searchName);
            if(structureChoice == 1) {
                Hotel* searchedHotel = koopaTree.search(searchName);
                if (searchedHotel != nullptr) {
                    searchedHotel->printReviews();
                }
                else {
                    cout << "Hotel Not Found!" << endl;
                }
                
            }
            if(structureChoice==2){
                Hotel* searchedHotel=koopaSearch.findHotel(searchName);
                searchedHotel->printReviews();
            }
        }
        if(userChoice==2){
            string searchCountry;
            cout<<"Enter the country to search for: ";
            getline(cin >> ws, searchCountry);
            if(structureChoice == 1) {
                koopaTree.displayCountry(koopaTree.getRoot(), searchCountry);
            }
            if(structureChoice == 2) {
                koopaSearch.printByCountry(searchCountry);
            }
        }
        if(userChoice==3){
            string searchCity;
            cout<<"Enter city to search for: ";
            getline(cin >> ws, searchCity);
            if(structureChoice == 1) {
                koopaTree.displayCity(koopaTree.getRoot(), searchCity);
             }
             if(structureChoice == 2) {
                koopaSearch.printByCity(searchCity);
             }
        }
    }



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
