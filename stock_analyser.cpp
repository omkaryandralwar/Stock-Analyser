#include<iostream>
#include<vector>
#include<cstdlib> //We have used this library to access the rand() & srand() 
#include<ctime> 
#include<cmath> //We have used this to access the sqrt() function.
#include<string>
#include<algorithm>
#include<iomanip> //We have used this to access the setw() function.
using namespace std;

struct DayData { //Creating new structure so that, 
    int day;     //one element in vector will show  
    double open; //all info about stock on that day.
    double close;
    double high;
    double low;
};

struct StockSummary { //Creating new structure so that, we can store name and and return % both in one str.
    string name;
    double returnPct;
};

vector<DayData> generateRandomStockData(int no_of_days, double currentPrice){
    vector<DayData> data;
    for(int a=0;a<no_of_days;a++){
        double change = (rand() % 401 - 200) / 100.0;           //In this function see How you have generated the random data.
        //can generate the random no. between -2.00 to +2.00.   //at the time of calculating change, high & low price.
        double openPrice = currentPrice;
        double closePrice = currentPrice + change;
        double highPrice = max(openPrice, closePrice) + (rand() % 100) / 100.0;
        double lowPrice  = min(openPrice, closePrice) - (rand() % 100) / 100.0;
         //Here we are calculating the high and low price randomly.
        DayData today;
        today.day = a+1;
        today.open = openPrice;
        today.close = closePrice;
        today.high = highPrice;
        today.low = lowPrice;
        data.push_back(today);
        currentPrice = closePrice;
    }
    return data;
}

void printData(vector<DayData> data, string name){         //Here We have used the data type size_t instead of int in loops to reduce the errors.
    cout<<"\n\n"<<name<<" STOCK HISTORY\n\n";
    cout<<setw(6) << "day"<<setw(10)<<"open"<<setw(10)<<"close"<<setw(10)<<"high"<<setw(10)<<"low"<<"\n";
    for(size_t i=0;i<data.size();i++){
        cout<<setw(6)<<data[i].day<<setw(10)<<data[i].open<<setw(10)<<data[i].close<<setw(10)<<data[i].high<<setw(10)<<data[i].low<<"\n"; 
    }
}

vector<double> computeMovingAverage(vector<DayData> data,size_t windowSize){
    vector<double> averages;
    double windowSum = 0.0;
    for(size_t i=0; i<data.size();i++){
        windowSum += data[i].close;       //Here to calculate the Moving Average we have used the Sliding Window concept.
        if(i < windowSize - 1){
            averages.push_back(-1);
        }
        else{
            double avg = windowSum / windowSize;
            averages.push_back(avg);
            windowSum -= data[i - windowSize + 1].close;
        }
    }
    return averages;
}

vector<double> computeVolatility(vector<DayData> data, size_t windowSize){
    vector<double> volatility;                                          // Volatility means change.
    for(size_t i=0; i<data.size();i++){
        if(i < windowSize - 1){
            volatility.push_back(-1);
        }
        else{
           double sum = 0.0;
           for(size_t j = i - windowSize + 1; j <= i; j++){
               sum += data[j].close;
            }
           double avg = sum / windowSize;
           double squaredDiffSum = 0.0;
           for(size_t j = i - windowSize + 1; j <= i; j++){
               double diff = data[j].close - avg;
               squaredDiffSum += diff * diff;
            }
            double stdDev = sqrt(squaredDiffSum / windowSize);
            volatility.push_back(stdDev);
        }
    }  
    return volatility; 
}

vector<string> generateSignals(vector<double> ma5, vector<double> ma20){
    vector<string> signals;
    for(size_t i=0;i<ma5.size();i++){
        if(ma5[i] == -1 || ma20[i] == -1){
            signals.push_back("--");
        }
        else if(ma5[i] > ma20[i]){
            signals.push_back("BUY");
        }
        else if(ma5[i] < ma20[i]){
            signals.push_back("SELL");
        }
        else{
            signals.push_back("HOLD");
        }
    }
    return signals;
}

double computeReturn(vector<DayData> data){
    return (data[data.size()-1].close - data[0].close) / data[0].close * 100;
}

bool compareReturns(StockSummary a, StockSummary b){
    return a.returnPct > b.returnPct;
}

void analyzeStockData(vector<DayData> data, string name){
    vector<double> ma5 = computeMovingAverage(data, 5);
    vector<double> ma20 = computeMovingAverage(data, 20);
    vector<double> vol5 = computeVolatility(data, 5);
    vector<string> signals = generateSignals(ma5, ma20);
    cout<<"\n\n"<<name<<" ANALYZED STOCK DATA\n\n";
    cout << "DAY" << setw(10) << "CLOSE" << setw(10) << "MA5" << setw(10) << "MA20" << setw(10) << "VOL5" << setw(10) << "SIGNALS\n";
    for(size_t i = 0; i < data.size(); i++){
        cout << data[i].day << setw(10) << data[i].close << setw(10);
        if(ma5[i] == -1) cout << "--" << setw(10); else cout << ma5[i] << setw(10);
        if(ma20[i] == -1) cout << "--" << setw(10); else cout << ma20[i] << setw(10);
        if(vol5[i] == -1) cout << "--" << setw(10); else cout << vol5[i] << setw(10);
        cout<< signals[i] << setw(10);
        cout<<"\n";
    }
}

int main(){
    srand(time(0));
    vector<DayData> tcs     = generateRandomStockData(50, 100.0);
    vector<DayData> infosys = generateRandomStockData(50, 150.0);
    vector<DayData> wipro   = generateRandomStockData(50, 80.0);
    printData(tcs, "TCS");
    printData(infosys, "INFOSYS");
    printData(wipro, "WIPRO");
    analyzeStockData(tcs, "TCS");
    analyzeStockData(infosys, "INFOSYS");
    analyzeStockData(wipro, "WIPRO");
    vector<StockSummary> stocks;
    StockSummary TCS;
    StockSummary INFOSYS;
    StockSummary WIPRO;
    TCS.name = "TCS";
    INFOSYS.name = "INFOSYS";
    WIPRO.name = "WIPRO";
    TCS.returnPct = computeReturn(tcs);
    INFOSYS.returnPct = computeReturn(infosys);
    WIPRO.returnPct = computeReturn(wipro);
    stocks.push_back(TCS);
    stocks.push_back(INFOSYS);
    stocks.push_back(WIPRO);
    sort(stocks.begin(), stocks.end(), compareReturns);
    cout<<"\n\n\nTHE STOCK WITH THE MOST RETURN or PROFIT & RETURN % ACCORDING TO GIVEN HISTORY :-\n";
    for(size_t a=0;a<stocks.size();a++){
        cout<< "\n" << a+1 << "] " << stocks[a].name << setw(10) << stocks[a].returnPct << "\n";
    }
    return 0;
}