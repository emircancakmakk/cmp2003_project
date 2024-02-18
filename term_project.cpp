#include "term_project.h"

void dataSet::setFileName()
{
    std::cout << "Dosya adi girin: " << "\n";
    std::cin >> fileName;
}

std::string dataSet::getFileName()
{
    return fileName;
}

dataSet::dataSet()
{
    userCount = 0;
    movieCount = 0;
    rowCount = 0;
    fileName = "";
}

void dataSet::import_and_save()
{
    std::ifstream fin;
    std::string firstCellPurge;

    std::string getUser;
    std::string getMovie;
    std::string getRating;
    
    this->setFileName();
    fin.open(fileName);
    
    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';

    getline(fin,firstCellPurge,'\n');

    while(fin.peek()!=EOF)
        {
        getline(fin, getUser, ',');
        getline(fin, getMovie, ',');
        getline(fin, getRating, '\n');

        if(dataUserMap.count(std::stoi(getUser)) != 1 && dataMovieMap.count(std::stoi(getMovie)) != 1)
        {
            userNode *node;
            node = new userNode;
            std::vector<int> *movieVector;
            movieVector = new std::vector<int>;
            movieVector->push_back(std::stoi(getUser));
            node->ratedMovies.push_back(std::stoi(getMovie));
            node->ratings.push_back(std::stof(getRating));
            dataUserMap.insert(std::pair<int,userNode*>(std::stoi(getUser),node));
            dataMovieMap.insert(std::pair<int,std::vector<int>*>(std::stoi(getMovie),movieVector));
        } 
        else if(dataUserMap.count(std::stoi(getUser)) != 1 && dataMovieMap.count(std::stoi(getMovie)) == 1)
        {

            userNode *node;
            node = new userNode;
            node->ratedMovies.push_back(std::stoi(getMovie));
            node->ratings.push_back(std::stof(getRating));
            dataUserMap.insert(std::pair<int,userNode*>(std::stoi(getUser),node));
            dataMovieMap.find(std::stoi(getMovie))->second->push_back(std::stoi(getUser));

        } 
        else if(dataUserMap.count(std::stoi(getUser)) == 1 && dataMovieMap.count(std::stoi(getMovie)) != 1)
        {
            std::vector<int> *movieVector;
            movieVector = new std::vector<int>;
            movieVector->push_back(std::stoi(getUser));
            dataMovieMap.insert(std::pair<int,std::vector<int>*>(std::stoi(getMovie),movieVector));
            dataUserMap.find(std::stoi(getUser))->second->ratedMovies.push_back(std::stoi(getMovie));
            dataUserMap.find(std::stoi(getUser))->second->ratings.push_back(std::stof(getRating));
        } 
        else if (dataUserMap.count(std::stoi(getUser)) == 1 && dataMovieMap.count(std::stoi(getMovie)) == 1)
        {
            dataMovieMap.find(std::stoi(getMovie))->second->push_back(std::stoi(getUser));
            dataUserMap.find(std::stoi(getUser))->second->ratedMovies.push_back(std::stoi(getMovie));
            dataUserMap.find(std::stoi(getUser))->second->ratings.push_back(std::stof(getRating));
        }
    }
    
    fin.close();
}

void dataSet::printSaved()
{
    std::map <int,userNode*>::const_iterator it;
    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
        std::cout << "USERID: "<< it->first <<'\n';
        for (int i = 0; i < it->second->ratedMovies.size(); ++i)
        {
            std::cout << "/////////////" << '\n';
            std::cout << "ITEMID: "<< it->second->ratedMovies[i] << '\n';
            std::cout << "RATING: "<< it->second->ratings[i] << '\n';
            std::cout << "/////////////" << '\n';
        }
        
        std::cout << "~~~~~~~~~~~~~~~~" << '\n';
    }
}

void dataSet::printTop10Users()
{
    std::map <int,userNode*>::const_iterator it;
    int topUserID[10] = {0,0,0,0,0,0,0,0,0,0};
    int topUserCount[10] = {0,0,0,0,0,0,0,0,0,0};

    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
            if(it->second->ratedMovies.size() > topUserCount[0])
            {
                topUserID[0] = it->first;
                topUserCount[0] = it->second->ratedMovies.size();
                selectionSort(topUserCount,topUserID, 10);
            }
    }
    
    for (int i = 0; i < 10; ++i) 
    {
        std::cout << "[" << topUserID[i] << "," << topUserCount[i] << "]";
    }
    
    std::cout << "\n";
}

void dataSet::printTop10Movies()
{
    std::map <int,std::vector<int>*>::const_iterator it;
    int topMovieID[10] = {0,0,0,0,0,0,0,0,0,0};
    int topMovieCount[10] = {0,0,0,0,0,0,0,0,0,0};

    for (it = dataMovieMap.begin(); it != dataMovieMap.end(); ++it)
    {
        if(it->second->size() > topMovieCount[0])
        {
            topMovieID[0] = it->first;
            topMovieCount[0] = it->second->size();
            selectionSort(topMovieCount,topMovieID, 10);
        }
    }
    
    for (int i = 0; i < 10; ++i) 
    {
        std::cout << "[" << topMovieID[i] << "," << topMovieCount[i] << "]";
    }
    std::cout << "\n";
}

int dataSet::getUserCount()
{
    return dataUserMap.size();
}

int dataSet::getMovieCount() 
{
    return dataMovieMap.size();
}

/*void dataSet::calcSimilarityIndex() {
    std::map <int,userNode*>::const_iterator it;
    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
        cosine_similarity(it->second->ratedMovies,it->second->ratings,it->second->ratedMovies.size());
    }
}*/

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int arr2[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        
        for (j = i+1; j < n; j++) 
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        
        if(min_idx!=i) {
            swap(&arr[min_idx], &arr[i]);
            swap(&arr2[min_idx], &arr2[i]);
        }
    }
}

double cosine_similarity(double *A, double *B, unsigned int Vector_Length)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
    
    for(unsigned int i = 0u; i < Vector_Length; ++i)
        {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
}
