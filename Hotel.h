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
    string city;


public:
    Hotel(string address_, string name_, float averageRate_){
        address=address_;
        name=name_;
        averageRating=averageRate_;

        //get country and city from address
        stringstream s(address);
        string val;
        string addA, temp1, temp2,temp3, addB;
        while(getline(s, val, ' ')){ //london addresses have postal code after city, so addB will hold that if that is the case
            addB=temp3;
            temp3=temp2;
            temp2=temp1;
            temp1=addA;
            addA=val;
        }
        if(addB=="London"){
            city="London";
        }
        else{
            city=temp1;
        }
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
        cout<<"Average rate: "<<averageRating<<" Address: "<<address<<endl;
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
    string getCity(){
        return city;
    }
};



