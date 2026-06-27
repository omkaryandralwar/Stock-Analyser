# Stock Price Analyser

A terminal-based stock market analyser built in C++ that simulates
and analyses stock price data for multiple companies using core DSA
concepts.

## Features

- **Random Stock Data Generation** — Simulates realistic OHLC
  (Open, High, Low, Close) price data for multiple stocks
- **Moving Averages** — Computes 5-day and 20-day Simple Moving
  Averages using sliding window technique (O(n) time complexity)
- **Volatility Tracking** — Calculates rolling standard deviation
  over a 5-day window to measure price volatility
- **Buy/Sell/Hold Signals** — Generates trading signals based on
  MA5 vs MA20 crossover strategy
- **Multi-Stock Ranking** — Ranks stocks by return percentage using
  custom comparator with STL sort()
- **Formatted Console Output** — Clean tabular display using setw()

## Concepts Used

- Structs, Vectors, Strings
- Sliding Window (Moving Averages)
- Rolling Standard Deviation (Volatility)
- Sorting with Custom Comparator
- STL: vector, algorithm, iomanip

## Stocks Analysed

- TCS (starting price: ₹100)
- Infosys (starting price: ₹150)
- Wipro (starting price: ₹80)

## How to Run

```bash
g++ stock_analyser.cpp -o stock_analyser
./stock_analyser
```

## Sample Output

```
TCS ANALYZED STOCK DATA

DAY     CLOSE       MA5      MA20      VOL5   SIGNALS
1       101.23      --        --        --      --
...
21      103.45    102.10    101.85     0.91     BUY
```

## Author

Omkar Dhanu Yandralwar
Pre-final year EEE @ VNIT Nagpur
github.com/omkaryandralwar
```
