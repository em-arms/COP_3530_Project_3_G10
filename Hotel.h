#include <iostream>
#include <vector>
#include "Review.cpp"
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
};



