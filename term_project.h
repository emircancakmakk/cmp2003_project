#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <cmath>
double cosine_similarity(double *A, double *B, unsigned int Vector_Length);
void selectionSort(int arr[], int arr2[], int n);
void swap(int *xp, int *yp);
struct userNode
{
    std::vector<int> ratedMovies;
    std::vector<float> ratings;
    double similarityIndex;
};

class dataSet{
public:
    void import_and_save();
    void printSaved();
    void setFileName();
    void printTop10Users();
    void printTop10Movies();
    int getMovieCount();
    int getUserCount();
    void calcSimilarityIndex();
    std::string getFileName();
    dataSet();
    //private al test icin konuldu

private:
    int userCount;
    int movieCount;
    int rowCount;
    std::map<int,std::vector<int>*> dataMovieMap;
    std::map<int,userNode*> dataUserMap;
    std::string fileName;
};
