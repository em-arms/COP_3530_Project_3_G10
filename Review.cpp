using namespace std;
#include <iostream>
class Review {
private:
    string date;
    float rating;   //float or double?
    string negReview; //string going to be able to hold it all?
    string posReview;

public:
    Review(string date_, float rating_, string nReview_,string pReview_){
        date=date_;
        rating=rating_;
        negReview=nReview_;
        posReview=pReview_;
    }

    float getRating(){
        return rating;
    }

    void printReview(){
        cout<<date<<"\t"<<rating<<"\t"<<negReview<<" "<<posReview<<endl;
        cout<<"printing"<<endl;
    }
};