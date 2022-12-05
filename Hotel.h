#include <iostream>
#include <vector>
#include "Review.cpp"
#include <fstream>
#include <sstream>
using namespace std;

class Hotel {
private:
    string address;
    string name;
    float averageRating;
    vector <Review*> reviews;
    string country;

    int numReviews;     //might not be necessary since I am pretty sure it gives the hotels average rating already
    float points;

public:
    Hotel(string address_, string name_, float averageRate_){
        address=address_;
        name=name_;
        averageRating=averageRate_;

        //get country from address
        stringstream s(address);
        string val;
        while(getline(s, val, ' ')){}
        if(val=="Kingdom"){
            val="United Kingdom"; //to account for two word country
        }
        country=val;
    }

    void addReview(string date_, float rating_, string nReview_, string pReview_){
        Review* newReview =new Review(date_, rating_, nReview_, pReview_ );
        reviews.push_back(newReview);
    }

    void printReviews(){
        for(int i=0; i<reviews.size(); i++){
            reviews[i]->printReview();

        }
    }

    string getName(){
        return name;
    }

    string getCountry(){
        return country;
    }
};



